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
            printf("Carnet: %s", linea);
            primeraLineaLeida = 1;
        }
        else
        {
            //CODIGO DE PRUEBA: RECORRIENDO Y ESCANEANDO LINEAS
            int i;

            //cuenta ciertos espacios recorridos
            char espacio = 0;
            //codigo y la seccion de las materias que cursa
            char* codigo = malloc(16);
            char seccion; 

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
                        seccion = linea[i+1];
                        printf("Seccion: %c\n", seccion);
                        break;
                    }
                    //Ya se leyo el codigo de la materia, se imprime y se busca
                    //la seccion despues de pasar dos espacios.
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
                    //Lee el codigo de la materia hasta llegar a un espacio
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
                        printf("Seccion: %c\n", seccion);
                        espacio++;
                    }

                    //Ya se leyo el codigo de la materia, se imprime y se busca
                    //la seccion despues de pasar dos espacios.
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
                    //Lee el codigo de la materia hasta llegar a un espacio
                    if(espacio == 0)
                    {
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
                        printf("Profesor: %s\n", profesor);
                    }
                    
                }
            }
            //si se sale del bucle anterior, significa que leyo toda la linea
            //activa un flag para leer las demas lineas
            primeraLineaLeida = 1;
        }
        else
        {
            printf("Carnet: %s", linea);
        }
    }

    return 0;
}