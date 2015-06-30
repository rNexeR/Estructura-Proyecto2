#ifndef ARISTADOBLE_H
#define ARISTADOBLE_H

class AristaDoble{
public:
    Nodo* origen;
    Nodo* destino;
    int costo;
    AristaDoble* sig;

    AristaDoble(){
        origen = NULL;
        destino = NULL;
        costo = 0;
    }
};

#endif // ARISTADOBLE_H

