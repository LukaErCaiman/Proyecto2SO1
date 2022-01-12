#ifndef lectorArchivos
#define lectorArchivos


int LeerCarnet(char* directorio, LMat *Lista, int tipo);

int LeerCurso(char* directorio, LMat *Lista, int tipo);

void pasarCadena2(LEst *Lista , LFinal *L, char cadena1[], int tipo);

void imprimirLMat2(LMat *Lista);

void ArmarDireccionCurso(int tipo, char direccion[], char curso[], int seccion, char direccion_final[]);

void recorrerLMatAbrirCursos(LMat *Lista, char direccion_inicial[], int sede, int tipo);

void recorrerLEstAbrirComprobantes(LEst *ListaEst, LMat *ListaMat, char directorioDACE[], int sede, int tipo);

#endif
