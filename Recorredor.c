#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

int RecorrerRaiz(char* directorio);
int BuscaArchivos(char* carnetOCodigo, char modoCoM, char* directorio);
int BuscaCarnet(char* carnet, char* pathSede, struct dirent* entidad);
int BuscaMateria(char* codigo, char* pathSede, struct dirent* entidad);


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

//NOTA: Quitar parametro "directorio" al conectar con main y reemplasar por
//comandos->directorio
//el parametro modoCoM es para indicar si busca un carnet o una materia
// - Si su valor es 0, va a buscar un carnet
// - Si su valor es 1, una materia
int BuscaArchivos(char* carnetOCodigo, char modoCoM, char* directorio)
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
                BuscaCarnet(carnetOCodigo, pathSede, entidad);
            }
            //BUSCA ARCHIVOS DE MATERIAS
            if(modoCoM == 1)
            {
                BuscaMateria(carnetOCodigo, pathSede, entidad);
            }
            //Se cierra para abrirse después con la otra sede o cerrar la busqueda
            closedir(sede);
        } 

        entidad = readdir(raiz);
    }

    closedir(raiz);
    return 0;
}

int BuscaCarnet(char* carnet, char* pathSede, struct dirent* entidad)
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
    closedir(dirRaizCarnets);
}


int BuscaMateria(char* codigo, char* pathSede, struct dirent* entidad)
{
    DIR* dirRaizCodigos = opendir(strcat(pathSede, "/listas"));
    entidad = readdir(dirRaizCodigos);
    char dosLetras[3] = { codigo[0], codigo[1], 0};
    
    DIR* materias;
    //BUSCA CARPETA DONDE ESTÁ ESTA MATERIA
    while(entidad != NULL)
    {
        //SI HAYA CARPETA, ENTRA
        if(strcmp(dosLetras,entidad->d_name) == 0)
        {
            char* pathCodigos = malloc(64);
            strcat(pathCodigos,pathSede);
            strcat(pathCodigos, "/");
            strcat(pathCodigos, entidad->d_name);
            materias = opendir(pathCodigos);
            entidad = readdir(materias);

            //BUSCA ARCHIVO DEL CARNET
            while(entidad != NULL)
            {
                //SI LO ENCUENTRA, ENTRA
                if(strstr(entidad->d_name, codigo) != NULL)
                {
                    printf("ARCHIVO DE MATERIA HAYADO!\n");
                    break;
                }
                entidad = readdir(materias);
            }
        }
        entidad = readdir(dirRaizCodigos);
    }
    closedir(materias);
}

int main(int argc, char* argv[])
{
    BuscaArchivos("TI4523", 1, "./DACE" );
    return 0;
}
