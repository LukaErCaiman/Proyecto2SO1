#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Variables.h"
#include "listaData.h"
#include "LectorArchivos.h"

LMat  *ListaMaterias  = NULL;
Entradas comandos;

void ImprimirError();

int Opciones(int argc, char* argv[], Entradas* input);
int VerificarEsNumero(char* argv);


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

    return 0;
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