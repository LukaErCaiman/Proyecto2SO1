#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "listaData.h"


extern LMat    *ListaMaterias;
extern LEst    *ListaEstudiantes;
extern LFinal  *ListaMateriasCompleja;

void imprimirLMat2(LMat *Lista){
    LMat* aux;
    aux = Lista;
    printf("La lista es la siguiente\n");
    while (aux !=NULL){
        printf("codigo:%s \n", aux->codigo);
        printf("seccion:%d \n", aux->seccion);
        aux = aux->sig;
    }
}


void pasarCadena2(LEst *Lista , LFinal *L, char cadena1[], int tipo){

    if(compararCarnet(ListaEstudiantes, cadena1)){
        ListaEstudiantes = agregarLEst(ListaEstudiantes,tipo, cadena1);
    }else{
        //si no es nuevo, no se agrega
        //printf("El carnet ya existe, no se agrego\n"); 
    }
    LFinal* aux;
    aux = L;
    while (aux->sig !=NULL){
        aux =aux->sig;
    }
    aux->estudiantes   = agregarLEst(aux->estudiantes,tipo, cadena1); 
    
} 

int LeerCarnet(char* directorio, LMat *Lista, int tipo)
{
    FILE* archivo = fopen(directorio, "r");
    
    //Mensaje de error si no hay un archivo con el directorio dado
    if (archivo == NULL)
    {
        printf("ERROR: directorio de archivo invalido!\n");
        return 0;
        exit(1);
    }

    //variable buffer para guardar el contenido de una linea
    char linea[100];

    /*flag que detecte cuando se leyo la primera linea del archivo
    esta linea contiene el codigo, seccion, nombre, profesor y sede de la materia*/
    char primeraLineaLeida = 0;
    char espacio;
    char* codigo = malloc(6);
    char seccion;
    char codiguito[6]; 

    //bucle que itera todas las lineas del archivo
    while(fgets(linea, sizeof(linea), archivo))
    {
        //Si no se ha leido la promera linea
        if(primeraLineaLeida == 0)
        {
            //printf("Carnet: %s", linea);
            primeraLineaLeida = 1;
        }
        else
        {
            //CODIGO DE PRUEBA: RECORRIENDO Y ESCANEANDO LINEAS

            //cuenta ciertos espacios recorridos
            espacio = 0;

            //codigo y la seccion de las materias que cursa
            codigo = malloc(6);

            int i;
            //iteracion sobre la linea, int i es la cuenta del caracter de la linea
            for(i = 0; i < sizeof(linea); i++)
            {
                //si el caracter es un espacio y no se ha llegado al segundo espacio
                if(linea[i] == ' ')
                {
                    //se leyo el codigo, ignoro "seccion:" se hayo otro espacio
                    //aqui se guarda el numero de seccion.
                    if(espacio == 2)
                    {
                        seccion = linea[i-1];
                        //printf("Seccion: %c\n", seccion);
                        break;
                    }
                    //Ya se leyo el codigo de la materia, se imprime y se busca
                    //la seccion despues de pasar dos espacios.
                    else
                    {
                        espacio++;
                        if (espacio == 1)
                        {
                            //printf("Codigo: %s\n", codigo);
                        }
                    }
                }
                else
                {
                    //Lee el codigo de la materia hasta llegar a un espacio
                    if(espacio == 0)
                    {
                        char letra = linea[i];
                        strcat(codigo,&letra);
                    }
                }
            }

            strcpy(codiguito,codigo);
            ListaMaterias = agregarLMat(ListaMaterias,charAEntero(seccion), codiguito);

            
            

        }




    }

    return 1;
}

int LeerCurso(char* directorio,  LMat *Lista, int tipo)
{
    FILE* archivo = fopen(directorio, "r");
    //char* temp;
    //scanf("%s\n",temp);
    
    //Mensaje de error si no hay un archivo con el directorio dado
    if (archivo == NULL)
    {
        printf("ERROR: directorio de archivo invalido!\n");
        exit(1);
    }

    //variable buffer para guardar el contenido de una linea
    char linea[100];

    /*flag que detecte cuando se leyo la primera linea del archivo
    esta linea contiene el codigo, seccion, nombre, profesor y sede de la materia*/
    char primeraLineaLeida = 0;

    //bucle que itera todas las lineas del archivo
    while(fgets(linea, sizeof(linea), archivo))
    {
        //Si no se ha leido la promera linea
        if(primeraLineaLeida == 0)
        {
            //CODIGO DE PRUEBA: RECORRIENDO Y ESCANEANDO LINEAS

            //cuenta ciertos espacios recorridos
            char espacio = 0;
            //detecta si se lee el profesor
            char leyendoProfesor = 0;

            //variables que guardan la seccion, codigo y profesor de materia
            char seccion; 
            int i;
            char* codigo = malloc(16);
            char* profesor = malloc(64);

            //iteracion sobre la linea, int i es la cuenta del caracter de la linea
            for(i = 0; i < sizeof(linea); i++)
            {
                //si el caracter es un espacio y no se ha llegado al segundo espacio
                if(linea[i] == ' ' && espacio != 2)
                {
                    //se leyo el codigo, ignoro "seccion:" se hayo otro espacio
                    //aqui se guarda el numero de seccion, se indica que se
                    //vio dos espacios (cerrando este condicional) y se busca
                    //al profesor despues.
                    if(espacio == 1)
                    {
                        seccion = linea[i+1];
                        //printf("Seccion: %c\n", seccion);
                        espacio++;
                    }

                    //Ya se leyo el codigo de la materia, se imprime y se busca
                    //la seccion despues de pasar dos espacios.
                    else
                    {
                        espacio++;
                        if (espacio == 1)
                        {
                           // printf("Codigo: %s\n", codigo);
                        }
                    }
                }
                else
                {
                    //Lee el codigo de la materia hasta llegar a un espacio
                    if(espacio == 0){
                        char letra = linea[i];
                        strcat(codigo,&letra);
                    }
                    //Lee el nombre del profesor.
                    //Si se llega a un punto, salta un espacio y activa el flag
                    //para leer el nombre del profesor completo, con espacios
                    if(espacio == 2 && linea[i] == '.')
                    {
                        i = i+2;
                        leyendoProfesor = 1;
                    }
                    //lee el nombre del profesor hasta llegar a un guion
                    if (leyendoProfesor == 1 && linea[i] != '-')
                    {
                        char letra = linea[i];
                        strcat(profesor,&letra);

                    }
                    //Si llega a un guion, imprime el nombre del profesor
                    if(linea[i] == '-')
                    {
                        //printf("Profesor: %s\n", profesor);
                        break;
                    }
                    
                }
            }
            //ListaMateriasCompleja = agregarLFinal(ListaMateriasCompleja, 1);
            ListaMateriasCompleja = agregarLFinal(ListaMateriasCompleja, seccion, codigo, profesor, tipo);
            //seccion, codigo, profesor, 
            //si se sale del bucle anterior, significa que leyo toda la linea
            //activa un flag para leer las demas lineas
            primeraLineaLeida = 1;
        }
        else
        {
            //printf("Carnet: %s", linea);
            pasarCadena2(ListaEstudiantes, ListaMateriasCompleja, linea, tipo);
        }
    }

    return 0;
}



void ArmarDireccionCurso(int tipo, char direccion[], char curso[], int seccion, char direccion_final[]){
    char directorio2[100];
    char cohorte[3];
    char inicial[2];

    strcpy(directorio2, direccion);
    //printf("curso en funcion direccion %s\n", curso );

    for(int p = 0; p<2 ; p++){
        inicial[p]=curso[p];
    }
    inicial[2] = '\0';
    
    //strncpy(inicial, curso, 2);
    //printf("Las iniciales del curso son: %s\n", inicial);
    switch(tipo){
        case 1:
            strcat(directorio2,"DACE/Sartenejas/listas/");
            break;
        case 2:
            strcpy(directorio2,"DACE/Litoral/listas/");
            break;
        default:
            strcpy(directorio2,"DACE/Sartenejas/comprobantes/listas/");

    }
    strncat(directorio2, inicial, 2);
    strcat(directorio2, "/");
    strcat(directorio2, curso);
    strcat(directorio2, " seccion ");
    char cToStr[2];
    cToStr[1] = '\0';
    cToStr[0] =  enteroAChar(seccion);
    //sprintf(directorio2, "%s%c", directorio2, enteroAChar(seccion));
    strcat(directorio2, cToStr );

    strcat(directorio2, ".txt");
    strcpy(direccion_final, directorio2);
}

void recorrerLMatAbrirCursos(LMat *Lista, char direccion_inicial[], int sede, int tipo){
    LMat* aux;
    aux = Lista;
    char direccion[100];

    while (aux != NULL){
        ArmarDireccionCurso(sede, direccion_inicial , aux->codigo, aux->seccion, direccion);
        //printf("La direccion final es %s\n", direccion);

        if(compararCodigo(ListaMateriasCompleja, aux->codigo)){
            LeerCurso(direccion,  ListaMaterias, tipo);
        }else{
            //printf("La materia no se agrego porque ya existe\n");
        }
        
        aux = aux->sig;
    }
}
void ArmarDireccion(int tipo, char direccion[], char carnet[])
{
    char directorio2[100];
    char cohorte[3];

    switch(tipo){
        case 1:
            strcat(direccion,"/Sartenejas/comprobantes/");
            break;
        case 2:
            strcpy(direccion,"/Litoral/comprobantes/");
            break;
        default:
            strcpy(direccion,"/Sartenejas/comprobantes/");

    }
    strncpy(cohorte, carnet, 2);
    strncat(direccion, cohorte, 2);
    strcat(direccion, "/");
    strcat(direccion, carnet);
    strcat(direccion, ".txt");
}

void recorrerLEstAbrirComprobantes(LEst *ListaEst, LMat *ListaMat, char directorioDACE[], int sede, int tipo){
    //printf("La direccion es %s\n", directorioDACE );
    LEst* auxiliar;
    auxiliar = ListaEst;
    int p;
    int existe = 0;
    int numero_estudiantes = identificar_LEst(auxiliar);
    int iteraciones = 0;
    char direccion_auxiliar[100];
    strcpy(direccion_auxiliar, directorioDACE);
    while (numero_estudiantes!=iteraciones){   

        if(auxiliar->tipo != tipo){
            auxiliar = auxiliar->sig;
            iteraciones++;
            continue;
        } 
        p = 1;
        do{
            ArmarDireccion(p, direccion_auxiliar, auxiliar->carnet);
            //printf("El nuevo directorio es %s\n", direccion_auxiliar);
            existe = LeerCarnet(direccion_auxiliar, ListaMaterias, tipo);
            p++;
            if (p > 2)break;
        }while (existe == 0);
        
        if (!existe){
            printf("No existe el comprobante de este estudiante.\n");
        }
        else{
            //imprimirLMat(ListaMaterias);
        } 

        auxiliar =auxiliar->sig;
        iteraciones++;

    }
}

