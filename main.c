#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <dirent.h>
#include "Variables.h"
#include "listaData.h"
#include "readdir.h"

LMat  *ListaMaterias  = NULL;
LEst  *ListaEstudiantes = NULL;
LFinal  *ListaMateriasCompleja;


#include "LectorArchivos.h"

Entradas comandos;

void ImprimirError();

int Opciones(int argc, char* argv[], Entradas* input);
int VerificarEsNumero(char* argv);
void ArmarDireccion(int tipo, char direccion[], char carnet[]);



int main(int argc, char* argv[])
{
    comandos.directorio = malloc(64);

    if(argc < 2)
    {
        ImprimirError();
    }

    if (VerificarEsNumero(argv[1]) == 1)
    {
        printf("ERROR: Valor de carnet invalido.\n");
        ImprimirError();
    }
    strcpy(comandos.pacienteCero, argv[1]);


    Opciones(argc, argv, &comandos);

    printf("Entradas: Carnet: %s\n", comandos.pacienteCero);
    printf("Instancias: %d\n", comandos.instancias);
    printf("Directorio: %s\n", comandos.directorio);
    printf("el paciente es %s\n", comandos.pacienteCero);

    int existe = 0;

    char direccion[100]="";
    strcpy(direccion, strchr(comandos.directorio, '.')+1);
        printf("El nuevo directorio es %s\n", direccion);


    int sede = 1;
    do{
        ArmarDireccion(sede, direccion, comandos.pacienteCero);
        printf("El nuevo directorio es %s\n", direccion);
        existe = LeerCarnet(direccion, ListaMaterias);
        sede++;
        if(sede>2) break;
    }while(existe == 0);

    if(!existe){
        printf("No existe el comprobante de este estudiante.\n");
    }else{
        imprimirLMat(ListaMaterias);
    }




    LeerCurso("CCG333 seccion 1.txt",ListaMaterias);


    //Para ver si esta en sartenejas 
    

    //char *directorio = "DACE/Sartenejas/comprobantes/14/1410445.txt";
    /*if(LeerCarnet(directorio2, ListaMaterias)){
        printf("La lista de materias es:\n");
    }else{
        char directorio2[100] = "DACE/Litoral/comprobantes/";
        strncat(directorio2, cohorte, 2);
        strcat(directorio2, "/");
        strcat(directorio2, comandos.pacienteCero);
        strcat(directorio2, ".txt");
        printf("El nuevo directorio es %s\n", directorio2);
        existe

    }*/
    


   /// ejecutarDirectorio(".");

    printf("Luego de todo deberia imprimir la lista de estudiantes\n");
    imprimir_LEst(ListaEstudiantes);

    //imprimirEstudiantesMateria(ListaMateriasCompleja);
    imprimirLFinal(ListaMateriasCompleja);

    return 0;
}

void ArmarDireccion(int tipo, char direccion[], char carnet[]){
    char directorio2[100];
    char cohorte[3];
    switch(tipo){
        case 1:
            strcat(direccion,"DACE/Sartenejas/comprobantes/");
            break;
        case 2:
            strcpy(direccion,"DACE/Litoral/comprobantes/");
            break;
        default:
            strcpy(direccion,"DACE/Sartenejas/comprobantes/");
    }
    strncpy(cohorte, carnet, 2);
    strncat(direccion, cohorte, 2);
    strcat(direccion, "/");
    strcat(direccion, carnet);
    strcat(direccion, ".txt");
}

int Opciones(int argc, char* argv[], Entradas* input)
{
    int i;
    char iRevisada, dRevisada;
    iRevisada = 1;
    dRevisada = 1;


    for(i = 2; i < argc; i = i+2)
    {
        /* Lee numero de instancias */

        if(strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--instancias") == 0)
        {
            if((i+1) >= argc)
            {
                ImprimirError();
            }
            VerificarEsNumero(argv[i+1]);
            input->instancias = atoi(argv[i+1]);
            iRevisada = 0;
        }
        /* Lee direccion del directorio raiz */
        if(strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--directorio") == 0)
        {   
            

            printf("REVISANDO DIRECTORIO");
            if((i+1) >= argc)
            {
                ImprimirError();
            }
            
            strcpy(input->directorio, argv[i+1]);

            dRevisada = 0;

        }
    }
    

    if (iRevisada == 0 && dRevisada == 0)
    {
        return 0;
    }
    else
    {
        if(iRevisada == 1)
        {
            printf("ERROR: Entrada de numero de instancias invalida.\n");
            ImprimirError();
        }
        if(dRevisada == 1)
        {
            printf("ERROR: Entrada de directorio invalida.\n");
            ImprimirError();
        }
    }
    return 1;
}

int VerificarEsNumero(char* argv)
{
    int x;

    for( x = 0; x < strlen(argv); x++)
    {
        if(argv[x] < '0' || argv[x] > '9')
        {
            return 1;
        }
    }

    return 0;
}

void ImprimirError()
{
    printf("Sintaxis de ejecucion correcta:\n");
    printf("./rastreo <carnet> [-i | --instancias <n>] [-d | --directorio <dir>]\n");

    exit(0);
}