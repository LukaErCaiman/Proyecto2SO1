#include <stdlib.h>
#include <stdio.h>

#include "Variables.h"

void Opciones(int argc, char* argv[], Entradas* input);

int main(int argc, char* argv[])
{
    Entradas comandos;
    int carnet = atoi(argv[1]);

    return 0;
}

void Opciones(int argc, char* argv[], Entradas* input)
{
    char inputCorrecto = 1;
    if (argc > 2)
    {
        int i;
        for(i = 0; i < argc; i = i+2)
        {
            /*if(strcmp(argv[i], "--i") || strcmp(argv[i], "--instancias"))
            {}
            if(strcmp(argv[i], "--d") || strcmp(argv[i], "--directorio"))
            {}
            */
        }
    }

    if (inputCorrecto == 1)
    {
        printf("Sintaxis de ejecucion correcta:\n");
        printf("./rastreo <carnet> [-i | --instancias <n>] [-d | --directorio <dir>]\n");
    }
}