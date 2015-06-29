#ifndef NODO
#define NODO
#include <iostream>
#include <Qt>
#include "qnamespace.h"
#include <QGraphicsTextItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <vector>
#include <map>
#include "Cola.h"
using namespace std;

class Nodo{
public:
    string valor;
    multimap<Nodo*, int> aristas;
    QPointF pos;

    Nodo(string val){
        this->valor = val;
    }

    multimap<Nodo*, int>::iterator* buscarArista(Nodo* arista){
        for(multimap<Nodo*, int>::iterator x = aristas.begin();//initial value
            x != aristas.end(); //limit
            x++){
            if( (*x).first == arista)
                return &x;
        }

        return NULL;
    }
};

#endif // NODO

