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


#include "Recorredor.h"

#include "LectorArchivos.h"

Entradas comandos;

void ImprimirError();

int Opciones(int argc, char *argv[], Entradas *input);
int VerificarEsNumero(char *argv);
void ArmarDireccion(int tipo, char direccion[], char carnet[]);


int main(int argc, char *argv[])
{
    // Variable estructura que guarda todas las entradas del usuario
    comandos.directorio = malloc(64);

    if (argc < 2)
    {
        ImprimirError();
    }

    if (VerificarEsNumero(argv[1]) == 1)
    {
        printf("ERROR: Valor de carnet invalido.\n");
        ImprimirError();
    }

    // guarda el paciente cero en la estructura
    strcpy(comandos.pacienteCero, argv[1]);
    Opciones(argc, argv, &comandos);
    int sede = 1;

    //Lee la direccion colocada como argumento y busca el directorio raiz "DACE", si no lo encuentra lanza un error
    //char* directorioDACE = BuscarRaiz(comandos.directorio);
    char* directorioDACE = malloc(32);
    directorioDACE = BuscarRaiz(comandos.directorio);

    //printf("DIRECTORIO TOTAL: %s\n", directorioDACE);
    if(strcmp(directorioDACE, " ") == 0)
    {
        printf("ERROR: Directorio dado invalido, intente otra vez.");
        exit(1);
    }

    int existe = 0;
    char direccion[100] = "";
    strcpy(direccion, comandos.directorio);
    printf("La instancia es %d\n",comandos.instancias );
    int tipomaximo = comandos.instancias;
    int tipo = 0;


    ListaEstudiantes = agregarLEst(ListaEstudiantes, 0, comandos.pacienteCero);
    
    char direccionMaterias[100] = "";
    while(tipo!=tipomaximo){

        recorrerLEstAbrirComprobantes(ListaEstudiantes, ListaMaterias, directorioDACE, sede, tipo);
        strcpy(direccionMaterias,"");
        tipo++;
        recorrerLMatAbrirCursos(ListaMaterias, direccionMaterias , sede, tipo);
    }
    


    printf("La salida del programa es:\n");
    imprimirLFinal(ListaMateriasCompleja);


    printf("\n");
    printf("\n");
    printf("\n");
    printf("Finalmente tenemos la lista de los estudiantes a contactar y su instancia\n");
    imprimir_LEst(ListaEstudiantes);

   
    return 0;
}




int Opciones(int argc, char *argv[], Entradas *input)
{
    int i;
    char iRevisada, dRevisada;
    iRevisada = 1;
    dRevisada = 1;

    for (i = 2; i < argc; i = i + 2)
    {
        /* Lee numero de instancias */

        if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--instancias") == 0)
        {
            if ((i + 1) >= argc)
            {
                ImprimirError();
            }
            VerificarEsNumero(argv[i + 1]);
            input->instancias = atoi(argv[i + 1]);
            iRevisada = 0;
        }
        /* Lee direccion del directorio raiz */
        if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--directorio") == 0)
        {

            if ((i + 1) >= argc)
            {
                ImprimirError();
            }

            strcpy(input->directorio, argv[i + 1]);

            dRevisada = 0;
        }
    }

    if (iRevisada == 0 && dRevisada == 0)
    {
        return 0;
    }
    else
    {
        if (iRevisada == 1)
        {
            input->instancias = 1;
        }
        if (dRevisada == 1)
        {
            strcpy(input->directorio, ".");
        }
    }
    return 0;
}

int VerificarEsNumero(char *argv)
{
    int x;

    for (x = 0; x < strlen(argv); x++)
    {
        if (argv[x] < '0' || argv[x] > '9')
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