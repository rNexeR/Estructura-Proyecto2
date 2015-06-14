#ifndef GRAFO
#define GRAFO
#include "Nodo.h"

class Grafo{
public:
    vector<Nodo*> vertices;
    void insertar(Nodo* nuevo)
    {
        if(buscar(nuevo->valor) == NULL)
            vertices.push_back(nuevo);
    }

    void crearArista(Nodo* origen, Nodo* destino, char arista)
    {
        if(!origen->buscarArista(destino))
        {
            origen->aristas.insert(pair<Nodo*, char>(destino, arista));
            destino->aristas.insert(pair<Nodo*, char>(origen, arista));
        }
    }

    int buscar(string val)
    {
        for(int x = 0; x < vertices.size(); x++)
        {
            if(vertices[x]->valor == val)
                return x;
        }
        return -1;
    }

    void eliminar(Nodo* nodo)
    {
        int res = buscar(nodo->valor);

        if(res >= 0)
        {
            for(multimap<Nodo*, char>::iterator x = vertices[res]->aristas.begin();//initial value
                    x != vertices[res]->aristas.end(); //limit
                    x++)
            {
                eliminarArista((*x).first, nodo);
            }
            delete nodo;
            vertices.erase(vertices.begin()+res-1);
        }
    }

    void eliminarArista(Nodo* origen, Nodo* destino)
    {
        multimap<Nodo*, char>::iterator* temp = origen->buscarArista(destino);

        if(temp)
        {
            multimap<Nodo*, char>::iterator* tempo = destino->buscarArista(origen);
            origen->aristas.erase(*temp);
            destino->aristas.erase(*tempo);
        }
    }

};

#endif // GRAFO

