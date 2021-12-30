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

/* Estructura que guarda a estudiantes y/o profesores
    instancia - int que guarda la instancia en que se contacta a este estudiante.
    carnet - arreglo de char que guarda el numero de carnet
    cursos - arreglo de apuntadores de char que guarda los cursos a los que asiste
    head, sig- ant - apuntadores de lista a la cabeza de la lista, el elemento siguiente y anterior */
typedef struct Persona
{
    int instancia;
    char carnet[7];
    char* cursos[10];
    struct Persona head;
    struct Persona sig;
    struct Persona ant;
    
} Persona;

#endif
