#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "listaData.h"

int VerificarMateria(int seccion, char* codigo, struct dirent* entidad);

int RecorrerRaiz(char* directorio)
{
    DIR* dir = opendir(directorio);
    char SHayado = 1, LHayado = 1;
    if (dir == NULL)
    {
        return 1;
    }

    struct dirent* entidad;
    entidad = readdir(dir);
    while(entidad != NULL)
    {
        printf("%s\n", entidad->d_name);
        if(entidad->d_type == 4)
        {
            if(strcmp("Sartenejas", entidad->d_name) == 0)
            {
                SHayado = 0;
            }
            if(strcmp("Litoral", entidad->d_name) == 0)
            {
                LHayado = 0;
            }
        }
        entidad = readdir(dir);
    }
    
    closedir(dir);
    if(SHayado == 0 && LHayado == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


int BuscaCarnet(char* carnet, char* pathSede, struct dirent* entidad, LEst* ListaEst, LMat* ListaMats)
{
    DIR* dirRaizCarnets = opendir(strcat(pathSede, "/comprobantes"));
    entidad = readdir(dirRaizCarnets);
    char dosNums[3] = { carnet[0], carnet[1], 0};

    DIR* comprobantes;
    //BUSCA CARPETA DONDE ESTÁ ESTE CARNET
    while(entidad != NULL)
    {
        //SI HAYA CARPETA, ENTRA
        if(strcmp(dosNums,entidad->d_name) == 0)
        {
            char* pathCarnets = malloc(64);
            strcat(pathCarnets,pathSede);
            strcat(pathCarnets, "/");
            strcat(pathCarnets, entidad->d_name);

            comprobantes = opendir(pathCarnets);
            entidad = readdir(comprobantes);
            //BUSCA ARCHIVO DEL CARNET
            while(entidad != NULL)
            {
                //SI LO ENCUENTRA, ENTRA
                if(strstr(entidad->d_name, carnet) != NULL)
                {
                    printf("ARCHIVO DE CARNET HAYADO!\n");
                    break;
                }
                entidad = readdir(comprobantes);
            }
        }
        entidad = readdir(dirRaizCarnets);
    }

    closedir(comprobantes);
}


int BuscaMateria(char* codigo, char* pathSede, int seccion, struct dirent* entidad, LMat* ListaMats)
{
    DIR* dirRaizCodigos = opendir(strcat(pathSede, "/listas"));
    entidad = readdir(dirRaizCodigos);
    char dosLetras[3] = { codigo[0], codigo [2], 0};
    DIR* materias;
    char* pathCodigos = malloc(64);
    //BUSCA CARPETA DONDE ESTÁ ESTA MATERIA
    while(entidad != NULL)
    {
        printf("ENTRA AQUI: %s---------\n", entidad->d_name);
        //SI HAYA CARPETA, ENTRA
        if(strcmp(dosLetras,entidad->d_name) == 0)
        {
            strcpy(pathCodigos,pathSede);
            strcat(pathCodigos, "/");
            strcat(pathCodigos, entidad->d_name);

            materias = opendir(pathCodigos);
            entidad = readdir(materias);
            //BUSCA ARCHIVO DEL CARNET
            while(entidad != NULL)
            {
                //SI LO ENCUENTRA, ENTRA
                if(VerificarMateria(seccion, codigo, entidad) == 0)
                {
                    printf("ARCHIVO DE MATERIA HAYADO!\n");
                    break;
                }
                entidad = readdir(materias);
            }
        }
        entidad = readdir(dirRaizCodigos);
    }
}

//NOTA: Quitar parametro "directorio" al conectar con main y reemplasar por
//comandos->directorio
//el parametro modoCoM es para indicar si busca un carnet o una materia
// - Si su valor es 0, va a buscar un carnet
// - Si su valor es 1, una materia
int BuscaArchivos(char* carnetOCodigo, int seccion, int modoCoM, char* directorio, LEst* ListaEst, LMat* ListaMats)
{
    DIR* raiz = opendir(directorio);

    struct dirent* entidad;
    entidad = readdir(raiz);

    //ENTRA A CARPETA RAIZ Y BUSCA LAS CARPETAS DE LAS DOS SEDES
    while (entidad != NULL)
    {
        DIR* sede;
        //Si haya las sedes, verifica cada una de ellas
        if(strcmp(entidad->d_name, "Sartenejas") == 0 || strcmp(entidad->d_name, "Litoral") == 0)
        {
            char pathSede[100] = { 0 };
            strcpy(pathSede, directorio);
            strcat(pathSede, "/");
            strcat(pathSede,entidad->d_name);
            sede = opendir(pathSede);

            //BUSCA ARCHIVOS DE CARNET
            if(modoCoM == 0)
            {
                //BuscaCarnet(carnetOCodigo, pathSede, entidad, ListaEst, ListaMats);
            }
            //BUSCA ARCHIVOS DE MATERIAS
            if(modoCoM == 1)
            {
                BuscaMateria(carnetOCodigo, pathSede, seccion, entidad, ListaMats);
            }
            //Se cierra para abrirse después con la otra sede o cerrar la busqueda
            closedir(sede);
        } 

        entidad = readdir(raiz);
    }

    closedir(raiz);
    return 0;
}


int VerificarMateria(int seccion, char* codigo, struct dirent* entidad)
{
    printf("%s\n", codigo);
    char* materiaLeida = malloc(8);
    int i;
    printf("%s\n", entidad->d_name);
    char espacios = 0;
    for (i = 0; i < sizeof(entidad->d_name); i++)
    {
        if (entidad->d_name[i] == ' ')
        {
            espacios++;
            if(strcmp(codigo,materiaLeida) != 0)
            {
                return 1;
            }
        }
        if(espacios == 0)
        {
            char letra = entidad->d_name[i];
            strcat(materiaLeida,&letra);
        }
        if(espacios == 2)
        {
            int seccionLeida = (int)((entidad->d_name[i+1]) - 48);
            if(strcmp(codigo,materiaLeida) == 0 && seccion == seccionLeida)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
    }
    return 1;
}


void mandarListaBuscar(LMat *Lista, LEst *Lista2, char direccion[]){

	LMat* aux;
	//LEst* aux2;

	aux = Lista;
	//aux2 = Lista2;

	printf("La lista es la siguiente\n");
	while (aux !=NULL){
		printf("codigo:%s \n", aux->codigo);
		printf("seccion:%d \n", aux->seccion);
		//BuscaArchivos(aux->codigo, aux->seccion, 1, direccion, aux2, aux);

		aux =aux->sig;
	}
}



/*
int main(int argc, char* argv[])
{
    BuscaArchivos("TI4523", 1, "./DACE" );
    return 0;
<<<<<<< HEAD
}*/