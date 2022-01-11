#ifndef Recorredor
#define Recorredor

int RecorrerRaiz(char* directorio);
char* BuscarRaiz(char* directorio);
int BuscaArchivos(char* carnetOCodigo, int seccion, int modoCoM, char* directorio, LEst* ListaEst, LMat* ListaMats);
int BuscaCarnet(char* carnet, char* pathSede, struct dirent* entidad, LEst* ListaEst, LMat* ListaMats);
int BuscaMateria(char* codigo, char pathSede, int seccion, struct dirent* entidad, LMat* ListaMats);
void mandarListaBuscar(LMat *Lista, LEst *Lista2, char direccion[]);


#endif