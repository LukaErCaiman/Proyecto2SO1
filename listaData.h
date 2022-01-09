#ifndef listaData
#define listaData

typedef struct nodo{
    char carnet[100];
    int tipo;
    struct nodo *sig;
}LEst;

typedef struct materia{
    char profesor[30];
    char sede[12];
    int seccion;
    int identificador;
    char nombre[100];
    char codigo[7];
    struct materia *sig;
}LMat;



int identificar_LEst (LEst *L);

// /int agregarMateria(LEst *L, char carnet[], char materia[]);

LMat *agregarLMat(LMat *Lista, int seccion, char codigo[]);

LEst *agregarLEst(LEst *Lista, int tipo, char cadena[]);

LEst *Borrar_LEst2(LEst *Lista, int v);

void Borrar_LEst(LEst *Lista, int v);

void imprimirEstudiantesMateria(LEst *Lista);

void imprimirLMat(LMat *Lista);

void imprimir_LEst(LEst *Lista);

int compararCarnet(LEst *L, char carnet[]);

int charAEntero(char caracter);



#endif