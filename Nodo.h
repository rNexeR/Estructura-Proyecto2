#ifndef NODO
#define NODO
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Nodo{
public:
    string valor;
    multimap<Nodo*, char> aristas;

    Nodo(string val){
        this->valor = val;
    }

    multimap<Nodo*, char>::iterator* buscarArista(Nodo* arista){
        for(multimap<Nodo*, char>::iterator x = aristas.begin();//initial value
            x != aristas.end(); //limit
            x++){
            if( (*x).first == arista)
                return &x;
        }

        return NULL;
    }
};

#endif // NODO

