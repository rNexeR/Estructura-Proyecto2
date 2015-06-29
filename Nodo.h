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
using namespace std;

class Nodo{
public:
    string valor;
    multimap<Nodo*, int> aristas;
    QPointF pos;
    bool prim, kruskal;

    Nodo(string val){
        this->valor = val;
        prim = false;
        kruskal = false;
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

