#ifndef ENTRADAS_H
#define ENTRADAS_H

/* Estructure que guarda las entradas dadas por el usuario 
    instancias - guarda el numero de instancias pedidos por el usuario
    directorio - guarda la direccion de la carpeta a revisar dada por el usuario
    pacienteCero - guarda el numero de carnet dado por el usuario*/
typedef struct Entradas
{
    int instancias;
    char* directorio;
    char pacienteCero[7];
} Entradas;

#endif
