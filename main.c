#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "Variables.h"

void Opciones(int argc, char* argv[], Entradas* input);
void ImprimirError();

int VerificarEsNumero(char* argv);


int main(int argc, char* argv[])
{
    Entradas comandos;

    if(argc < 2)
    {
        ImprimirError();
    }
    else
    {
        if (VerificarEsNumero(argv[1]) == 1)
        {
            printf("ERROR: Valor de carnet invalido.\n");
            ImprimirError();
        }
        int carnet = atoi(argv[1]);
    } 

    return 0;
}


void Opciones(int argc, char* argv[], Entradas* input)
{
    strcpy(input->pacienteCero, argv[1]);

        int i;
        for(i = 0; i < argc; i = i+2)
        {
            /* Lee numero de instancias */
            if(strcmp(argv[i], "--i") || strcmp(argv[i], "--instancias"))
            {
                if((i+1) > argc)
                {
                    ImprimirError();
                }
                VerificarEsNumero(argv[i+1]);
                input->instancias = atoi(argv[i+1]);
            }
            
            /* Lee direccion del directorio raiz*/
            if(strcmp(argv[i], "--d") || strcmp(argv[i], "--directorio"))
            {
                if((i+1) > argc)
                {
                    ImprimirError();
                }
                strcpy(input->directorio, argv[i+1]);
            }
        }
}

void ImprimirError()
{
    printf("Sintaxis de ejecucion correcta:\n");
    printf("./rastreo <carnet> [-i | --instancias <n>] [-d | --directorio <dir>]\n");

    exit(0);
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