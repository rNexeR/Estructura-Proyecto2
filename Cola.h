#ifndef COLA_H
#define COLA_H

#include "Grafo.h"
#include "Arista.h"

enum Posicion{
    POSICION, DISTANCIA, VISITADO, PATH
};

class Cola{
public:
    Arista* inicio;
    Arista* final;
    Cola(){
        inicio = NULL;
        final = NULL;
    }

    ~Cola(){

    }

    void insert(Nodo* nuevo, int distancia){
        if(!inicio){
            inicio = new Arista();
            inicio->arista = pair<Nodo*, int>(nuevo, distancia);
            inicio->sig = NULL;
            final = inicio;
            return;
        }
        if(distancia < inicio->arista.second){
            Arista* temp = inicio;
            inicio = new Arista();
            inicio->arista = pair<Nodo*, int>(nuevo, distancia);
            inicio->sig = temp;
            final = temp;
            return;
        }
        if(final->arista.second < distancia){
            Arista* nueva = new Arista();
            nueva->arista = pair<Nodo*, int>(nuevo, distancia);
            nueva->sig = final;
            final = nueva;
            return;
        }
        Arista* temp = inicio;
        while(temp->sig && temp->sig->arista.second < distancia)
            temp = temp->sig;
        Arista* nueva = new Arista();
        nueva->arista = pair<Nodo*, int>(nuevo, distancia);
        nueva->sig = temp->sig;
        temp->sig = nueva;
    }

    Arista* pop(){
        Arista* temp = inicio;
        inicio = inicio->sig;
        return temp;
    }

    bool empty(){
        return !inicio;
    }

    void clean(){
        while(pop());
    }
};

#endif // COLA_H

