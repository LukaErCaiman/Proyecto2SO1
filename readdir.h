#ifndef lectorDirectorios
#define lectorDirectorios

typedef struct nodoArchivo{
    char nombre[100];
    struct nodoArchivo *sig;
}LArch;

/* Función para devolver un error en caso de que ocurra */
void error(const char *s);
/* Función que hace algo con un archivo */
void procesoArchivo(char *archivo);
/*funcion que agrega a la lista un archivo*/
LArch *agregarLArch(LArch *Lista, char nombre[]);
//funcion para ejecutar la lectura de un directorio
int ejecutarDirectorio(char directorio[]);

#endif