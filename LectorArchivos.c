#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LeerCarnet(char* directorio);
int LeerCurso(char* directorio);

int main(int argc, char* argv[])
{
    LeerCarnet(argv[1]);
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
            char* codigo = malloc(10);
            char seccion; 

            for(i = 0; i < sizeof(linea); i++)
            {

                if(linea[i] == ' ')
                {
                    if(espacio == 1)
                    {
                        seccion = linea[i+1];
                        printf("Seccion: %c\n", seccion);
                        break;
                    }
                    else
                    {
                        espacio = 1;
                        printf("Codigo: %s\n", codigo);
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
}

int LeerCurso(char* directorio)
{
    FILE* archivo = fopen(directorio, "r");
    if (archivo == NULL)
    {
        printf("ERROR: directorio de archivo invalido!");
        exit(1);
    }

    char linea[100];
    char primeraLineaLeida = 0;

    while(fgets(linea, sizeof(linea), archivo))
    {
        printf("%s", linea);
    }
}