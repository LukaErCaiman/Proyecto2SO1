#include <stdio.h>

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