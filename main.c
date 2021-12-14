#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Variables.h"

void Opciones(int argc, char* argv[], Entradas* input);
void ImprimirError();

int main(int argc, char* argv[])
{
    Entradas comandos;
    int carnet = atoi(argv[1]);

    return 0;
}

void Opciones(int argc, char* argv[], Entradas* input)
{
    strcpy(input->pacienteCero, argv[1]);
    if (argc > 2)
    {
        int i;
        for(i = 0; i < argc; i = i+2)
        {
            if(strcmp(argv[i], "--i") || strcmp(argv[i], "--instancias"))
            {
                if((i+1) > argc)
                {
                    ImprimirError();
                }
                input->instancias = atoi(argv[i+1]);
            }
            
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
}

void ImprimirError()
{
    printf("Sintaxis de ejecucion correcta:\n");
    printf("./rastreo <carnet> [-i | --instancias <n>] [-d | --directorio <dir>]\n");

    exit();
}