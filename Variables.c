#include <stdlib.h>
#include <string.h>
#include "Variables.h"


Persona* CrearLista();
Persona* CrearPersona(Persona* Lista);

Persona* CrearLista()
{
    Persona *nuevo = (Persona*)malloc(sizeof(Persona));
    nuevo->carnet[0] = "0000000";
    nuevo->head = NULL;
    nuevo->ant = NULL;
    nuevo->sig = NULL;
    return nuevo;
}


Persona* CrearPersona(Persona* Lista) 
{
    Persona *nuevo = malloc(sizeof(Persona));

    //asignando nombre


    //datos dados, ahora se asignan apuntadores
    if (Lista->head == NULL)
    {
        Lista->head = nuevo;
        nuevo->ant = NULL;
        nuevo->sig = NULL;

        return Lista;
    }
    else
    {
        Persona* ultimo = Lista->head;
        while(ultimo->sig != NULL)
        {
            ultimo = ultimo->sig;
        }
        ultimo->sig = nuevo;
        
        nuevo->ant = ultimo;
        nuevo->sig = NULL;
        return Lista;
    }
}