#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct nodo{
    char carnet[100];
    int tipo;
    int identificador;
    struct nodo *sig;
    struct materia *materias;
}LEst;

typedef struct materia{
    char profesor[30];
    char sede[12];
    int seccion;
    int tipo;

    int identificador;
    char nombre[100];
    char codigo[6];
    struct materia *sig;
}LMat;


int identificar_LEst (LEst *L){
	int i=0;
	while(L!=NULL)
	{

		i++;
		//printf(" [%d] <=>",L->identificador);
		L->identificador = i;

		L=L->sig;

	}
	return i;
}

int charAEntero(char caracter){
	int entero = caracter - '0';
	return entero;  
}

/*typedef struct materia{
    char profesor[30];
    char sede[12];
    int seccion;
    int identificador;
    char nombre[100];
    char codigo[7];
    struct materia *sig;
}LMat;*/

/*

LMat *agregarLMat(LMat *Lista, char codigo[]){
	LMat *nuevoLMat, *aux;
	nuevoLMat             = (LMat*) malloc (sizeof (LMat));
	nuevoLMat->sig        = NULL;
	strcpy(nuevoLMat->codigo,codigo);
	//nuevoLMat->seccion = seccion;

	if (Lista==NULL){

		Lista=nuevoLMat;

	}else{

		aux=Lista;

		while (aux->sig !=NULL){

			aux = aux->sig;

		}

		aux->sig=nuevoLMat;

	}
	//identificar_LMat(Lista);
	printf("%s\n", nuevoLMat->codigo);

	return Lista;

}*/



LMat *agregarLMat(LMat *Lista, int seccion, char codigo[]){
	LMat *nuevoLMat, *aux;
	nuevoLMat                = (LMat*) malloc (sizeof (LMat));
	//nuevoLEst->nombre        = nombre;
	nuevoLMat->sig           = NULL;
	nuevoLMat->seccion          = seccion;
	for(int p = 0; p<11 ; p++){
		nuevoLMat->codigo[p]=codigo[p];
	}
	printf("\n");
	//strcpy(nuevoLMat->codigo,codigo);


	if (Lista==NULL){

		Lista=nuevoLMat;

	}else{

		aux=Lista;

		while (aux->sig !=NULL){

			aux = aux->sig;

		}

		aux->sig=nuevoLMat;

	}
	//identificar_LEst(Lista);

	return Lista;

}

LEst *agregarLEst(LEst *Lista, int tipo, char cadena[]){
	LEst *nuevoLEst, *aux;
	nuevoLEst                = (LEst*) malloc (sizeof (LEst));
	//nuevoLEst->nombre        = nombre;
	nuevoLEst->sig           = NULL;
	nuevoLEst->tipo          = tipo;
	strcpy(nuevoLEst->carnet,cadena);


	if (Lista==NULL){

		Lista=nuevoLEst;

	}else{

		aux=Lista;

		while (aux->sig !=NULL){

			aux = aux->sig;

		}

		aux->sig=nuevoLEst;

	}
	identificar_LEst(Lista);

	return Lista;

}


//esta funcion elimina un nodo de la lista de PC segun su ID
LEst *Borrar_LEst2(LEst *Lista, int v) {
	LEst *nodo, *anterior;
	nodo = Lista;
	anterior = NULL;

	while(nodo->identificador!=v) {
	  anterior = nodo;
	  nodo = nodo->sig;

	}
	if(!nodo) {
		printf("HUBO UN ERROR FATAL\n");
		return Lista;
	}
	else { /* Borrar el nodo */
		if(anterior==NULL){
			Lista = nodo->sig;
			identificar_LEst(Lista);
			return Lista;

		} /* Primer elemento */
		else{ /* un elemento cualquiera */
		anterior->sig = nodo->sig;
		free(nodo);
		identificar_LEst(Lista);
		return Lista;
		}
		//
	}

}

//esta funcion elimina un nodo de la lista de PC segun su Id pero no devuelve nada
void Borrar_LEst(LEst *Lista, int v) {
	LEst *nodo, *anterior;
	nodo = Lista;
	anterior = NULL;
	//printf("el nodo inicial es %p\n", nodo);
	while(nodo->identificador!=v){
		anterior = nodo;
		nodo = nodo->sig;
	//printf("el nodo actual es %p\n", nodo);

	}
	if(!nodo) {
		printf("hubo un error borrando\n");
		return;
	}
	else { /* Borrar el nodo */
		if(v==1) {/* Primer elemento */
			///printf("ENTRO AQUIIIIIII en la lista");
			Lista = nodo->sig;
		}else{ /* un elemento cualquiera */
		anterior->sig = nodo->sig;
		free(nodo);
		}
		identificar_LEst(Lista);
	}

}

void imprimirLMat(LMat *Lista){
	LMat* aux;
	aux = Lista;
	printf("La lista es la siguiente\n");
	while (aux !=NULL){
	//printf("%s\n", aux->nombre);
	printf("codigo:%s \n", aux->codigo);
	printf("seccion:%d \n", aux->seccion);


	aux =aux->sig;
	}
}


void imprimir_LEst(LEst *Lista){
	LEst* aux;
	aux = Lista;
	while (aux !=NULL){
	//printf("%s\n", aux->nombre);
	printf("ID: %i ", aux->identificador);
	printf("Carnet: %s\n", aux->carnet);




	aux =aux->sig;
	}
}
void imprimirEstudiantesMateria(LEst *Lista){
	LEst* aux;
	aux = Lista;
	while (aux !=NULL){
	//printf("%s\n", aux->nombre);
	printf("ID: %i ", aux->identificador);
	printf("Carnet: %s", aux->carnet);
	//printf("Materia: %s", aux->carnet);
	printf("El valor agregado es %s\n", aux->materias->nombre);

	aux =aux->sig;
	}
}

int compararCarnet(LEst *L, char carnet[]){
	int i=0;
	while(L!=NULL)
	{
		if(strcmp(L->carnet,carnet)==0){
			printf("El numero de carnet ya existe\n");
			return 0;
		}
		L=L->sig;
	}
	return 1;
}
/*
int agregarMateria(LEst *L, char carnet[], char materia[]){
	int i=0;
	while(L!=NULL){
		if(strcmp(L->carnet,carnet)==0){
			L->materias = agregarLMat(L->materias, materia); 

			return 0;
		}
		L=L->sig;
	}
	return 1;
}*/



 