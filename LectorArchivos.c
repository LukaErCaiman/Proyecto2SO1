#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LeerCarnet(char* directorio);
int LeerCurso(char* directorio);

int main(int argc, char* argv[])
{
    LeerCurso(argv[1]);
    return 0;
}

int LeerCarnet(char* directorio)
{
    FILE* archivo = fopen(directorio, "r");
    if (archivo == NULL)
    {
        printf("ERROR: directorio de archivo invalido!\n");
        exit(1);
    }

    char linea[100];
    char primeraLineaLeida = 0;

    while(fgets(linea, sizeof(linea), archivo))
    {
        if(primeraLineaLeida == 0)
        {
            printf("Carnet: %s", linea);
            primeraLineaLeida = 1;
        }
        else
        {
            //CODIGO DE PRUEBA: RECORRIENDO Y ESCANEANDO LINEAS
            int i;
            char espacio = 0;
            char* codigo = malloc(16);
            char seccion; 

            for(i = 0; i < sizeof(linea); i++)
            {

                if(linea[i] == ' ')
                {
                    if(espacio == 2)
                    {
                        seccion = linea[i+1];
                        printf("Seccion: %c\n", seccion);
                        break;
                    }
                    else
                    {
                        espacio++;
                        if (espacio == 1)
                        {
                            printf("Codigo: %s\n", codigo);
                        }
                    }
                }
                else
                {
                    if(espacio == 0)
                    {
                        char letra = linea[i];
                        strcat(codigo,&letra);
                    }
                }
            }
        }
    }

    return 0;
}

int LeerCurso(char* directorio)
{
    FILE* archivo = fopen(directorio, "r");
    if (archivo == NULL)
    {
        printf("ERROR: directorio de archivo invalido!\n");
        exit(1);
    }

    char linea[100];
    char primeraLineaLeida = 0;

    while(fgets(linea, sizeof(linea), archivo))
    {
        if(primeraLineaLeida == 0)
        {
            //CODIGO DE PRUEBA: RECORRIENDO Y ESCANEANDO LINEAS
            int i;
            char espacio = 0;
            char leyendoProfesor = 0;

            char seccion; 
            char* codigo = malloc(16);
            char* profesor = malloc(64);

            for(i = 0; i < sizeof(linea); i++)
            {
                if(linea[i] == ' ' && espacio != 2)
                {
                    if(espacio == 1)
                    {
                        seccion = linea[i+1];
                        printf("Seccion: %c\n", seccion);
                        espacio++;
                    }
                    else
                    {
                        espacio++;
                        if (espacio == 1)
                        {
                            printf("Codigo: %s\n", codigo);
                        }
                    }
                }
                else
                {
                    //Lee el codigo de la materia
                    if(espacio == 0)
                    {
                        char letra = linea[i];
                        strcat(codigo,&letra);
                    }
                    //Lee el nombre del profesor
                    if(espacio == 2 && linea[i] == '.')
                    {
                        i = i+2;
                        leyendoProfesor = 1;
                    }
                    if (leyendoProfesor == 1 && linea[i] != '-')
                    {
                        char letra = linea[i];
                        strcat(profesor,&letra);
                    }
                    if(linea[i] == '-')
                    {
                        printf("Profesor: %s\n", profesor);
                    }
                    
                }
            }

            primeraLineaLeida = 1;
        }
        else
        {
            printf("Carnet: %s", linea);
        }
    }

    return 0;
}