#ifndef ARISTA_H
#define ARISTA_H

#include "Nodo.h"

class Arista{
public:
    pair<Nodo*, int> arista;
    Arista* sig;

    Arista(){
        sig = NULL;
    }
};

#endif // ARISTA_H

