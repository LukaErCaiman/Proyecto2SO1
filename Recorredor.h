#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

#include "listaData.h"

int RecorrerRaiz(char* directorio);
int BuscaArchivos(char* carnetOCodigo, int seccion, char modoCoM, char* directorio, LEst* ListaEst, LMat* ListaMats);
int BuscaCarnet(char* carnet, char* pathSede, struct dirent* entidad, LEst* ListaEst, LMat* ListaMats);
int BuscaMateria(char* codigo, char pathSede, int seccion, struct dirent* entidad, LMat* ListaMats);
