#ifndef listaData
#define listaData

typedef struct nodo{
    char carnet[100];
    int tipo;
    int identificador;
    struct nodo *sig;
}LEst;

typedef struct materia{
    char profesor[30];
    char sede[12];
    int seccion;
    int tipo;
    int identificador;
    char nombre[100];
    char codigo[7];
    struct materia *sig;
}LMat;


typedef struct nodo_estudiante{
    char carnet[100];
    struct estudiante *estudiantes;
}LEst2;

typedef struct materia_compleja{
    char profesor[30];
    int sede;
    int seccion;
    int tipo;
    int identificador;
    char nombre[100];
    char codigo[6];
    struct materia_compleja *sig;
    struct nodo *estudiantes;
}LFinal;



int identificar_LEst (LEst *L);

int agregarEstudianteLFinal(LEst *L, char carnet[], char materia[]);

LFinal *agregarLFinal(LFinal *Lista, int seccion, char codigo[], char profesor[], int tipo);

void imprimirLFinal(LFinal *Lista);

LMat *agregarLMat(LMat *Lista, int seccion, char codigo[]);

LEst *agregarLEst(LEst *Lista, int tipo, char cadena[]);

LEst *Borrar_LEst2(LEst *Lista, int v);

void Borrar_LEst(LEst *Lista, int v);

void imprimirEstudiantesMateria(LEst *Lista);

void imprimirLMat(LMat *Lista);

void imprimirLMatPorPasos(LMat *Lista);

void imprimir_LEst(LEst *Lista);

int compararCarnet(LEst *L, char carnet[]);

int compararCodigo(LFinal *L, char codigo[]);

int charAEntero(char caracter);

char enteroAChar(int numero);

int BuscaArchivos(char* carnetOCodigo, int seccion, int modoCoM, char* directorio, LEst* ListaEst, LMat* ListaMats);


#endif