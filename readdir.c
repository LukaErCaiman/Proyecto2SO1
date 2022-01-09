#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

typedef struct nodoArchivo{
    char nombre[100];
    struct nodoArchivo *sig;
}LArch;

LArch  *ListaArchivos = NULL;

/* Función para devolver un error en caso de que ocurra */
void error(const char *s);
/* Función que hace algo con un archivo */
void procesoArchivo(char *archivo);
/*funcion que agrega a la lista un archivo*/
LArch *agregarLArch(LArch *Lista, char nombre[]);
//funcion para ejecutar la lectura de un directorio
int ejecutarDirectorio(char directorio[]);



void imprimir_LArch(LArch *Lista);

/*
int main(){
	char directorio[10] = ".";
	ejecutarDirectorio(directorio);
  	return EXIT_SUCCESS;

}*/
int ejecutarDirectorio(char directorio[]){
  /* Con un puntero a DIR abriremos el directorio */
  DIR *dir;
  /* en *ent habrá información sobre el archivo que se está "sacando" a cada momento */
  struct dirent *ent;

  /* Empezaremos a leer en el directorio actual */
  dir = opendir (directorio);

  /* Miramos que no haya error */
  if (dir == NULL)
    error("No puedo abrir el directorio");
 
  /* Una vez nos aseguramos de que no hay error, ¡vamos a jugar! */
  /* Leyendo uno a uno todos los archivos que hay */
  while ((ent = readdir (dir)) != NULL)
    {
      /* Nos devolverá el directorio actual (.) y el anterior (..), como hace ls */
      if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) )
    {
      /* Una vez tenemos el archivo, lo pasamos a una función para procesarlo. */
      procesoArchivo(ent->d_name);
    }
    }
  closedir (dir);
  imprimir_LArch(ListaArchivos);
}

void error(const char *s)
{
  /* perror() devuelve la cadena S y el error (en cadena de caracteres) que tenga errno */
  perror (s);
  exit(EXIT_FAILURE);
}

void procesoArchivo(char *archivo)
{
  /* Para "procesar", o al menos, hacer algo con el archivo, vamos a decir su tamaño en bytes */
  /* para ello haremos lo que vemos aquí: https://poesiabinaria.net/2010/04/tamano-de-un-fichero-en-c/ */
	FILE *fich;
	long ftam;

	fich=fopen(archivo, "r");
	if (fich){
		fseek(fich, 0L, SEEK_END);
		ftam=ftell(fich);
		fclose(fich);
		/* Si todo va bien, decimos el tamaño */
		printf ("%30s (%ld bytes)\n", archivo, ftam);
		ListaArchivos = agregarLArch(ListaArchivos, archivo);
	}else{
		/* Si ha pasado algo, sólo decimos el nombre */
		printf ("%30s (No info.)\n", archivo);
		ListaArchivos = agregarLArch(ListaArchivos, archivo);
	}
}

LArch *agregarLArch(LArch *Lista, char nombre[]){
	LArch *nuevoLArch, *aux;
	nuevoLArch                = (LArch*) malloc (sizeof (LArch));
	//nuevoLArch->nombre        = nombre;
	nuevoLArch->sig           = NULL;
	strcpy(nuevoLArch->nombre,nombre);


	if (Lista==NULL){

		Lista=nuevoLArch;

	}else{

		aux=Lista;

		while (aux->sig !=NULL){

			aux = aux->sig;

		}

		aux->sig=nuevoLArch;

	}
	//identificar_LArch(Lista);

	return Lista;

}

void imprimir_LArch(LArch *Lista){
	LArch* aux;
	aux = Lista;
	while (aux !=NULL){
	//printf("%s\n", aux->nombre);
	printf("Nombre: %s\n", aux->nombre);




	aux =aux->sig;
	}
}