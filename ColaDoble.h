#ifndef COLADOBLE_H
#define COLADOBLE_H

#include "Nodo.h"
#include "AristaDoble.h"

class ColaDoble{
public:
    AristaDoble* inicio;
    AristaDoble* final;
    int size = 0;
    ColaDoble(){
        inicio = NULL;
        final = NULL;
    }

    ~ColaDoble(){

    }

    void insert(Nodo* origen, Nodo* destino, int costo){
        size++;
        if(!inicio){
            inicio = new AristaDoble();
            inicio->origen = origen;
            inicio->destino = destino;
            inicio->costo = costo;
            inicio->sig = NULL;
            final = inicio;
            return;
        }
        if(costo < inicio->costo){
            AristaDoble* temp = inicio;
            inicio = new AristaDoble();
            inicio->origen = origen;
            inicio->destino = destino;
            inicio->costo = costo;
            inicio->sig = temp;
            final = temp;
            return;
        }
        if(final->costo < costo){
            AristaDoble* nueva = new AristaDoble();
            nueva->origen = origen;
            nueva->destino = destino;
            nueva->costo = costo;
            nueva->sig = final;
            final = nueva;
            return;
        }
        AristaDoble* temp = inicio;
        while(temp->sig && temp->sig->costo < costo)
            temp = temp->sig;
        AristaDoble* nueva = new AristaDoble();
        nueva->origen = origen;
        nueva->destino = destino;
        nueva->costo = costo;
        nueva->sig = temp->sig;
        temp->sig = nueva;
    }

    AristaDoble* pop(){
        AristaDoble* temp = inicio;
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

#endif // COLADOBLE_H

