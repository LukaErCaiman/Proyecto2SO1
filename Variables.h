#ifndef ENTRADAS_H
#define ENTRADAS_H

typedef struct Variables
{
    int instancias;
    char* directorio;
    char* pacienteCero;
} Entradas;

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
