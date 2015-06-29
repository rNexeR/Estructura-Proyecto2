#ifndef GRAFO
#define GRAFO
#include "Nodo.h"

class Grafo{
public:
    vector<Nodo*> vertices;
    bool insertar(Nodo* nuevo)
    {
        cout<<"\t Trying to insert"<<endl;
        if(buscarPos(nuevo->valor) == -1){
            vertices.push_back(nuevo);
            cout<<"\t Vertice Creado en Grafo"<<endl;
            return true;
        }
        return false;
    }

    void crearArista(Nodo* origen, Nodo* destino, int arista)
    {
        if(!origen->buscarArista(destino))
        {
            origen->aristas.insert(pair<Nodo*, int>(destino, arista));
            destino->aristas.insert(pair<Nodo*, int>(origen, arista));
        }
    }

    Nodo* buscarNodo(string val){
        for(int x = 0; x < vertices.size(); x++)
        {
            if(vertices[x]->valor == val)
                return vertices[x];
        }
        return NULL;
    }

    int buscarPos(string val)
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
        int res = buscarPos(nodo->valor);

        if(res >= 0)
        {
            for(multimap<Nodo*, int>::iterator x = vertices[res]->aristas.begin();//initial value
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
        multimap<Nodo*, int>::iterator* temp = origen->buscarArista(destino);

        if(temp)
        {
            multimap<Nodo*, int>::iterator* tempo = destino->buscarArista(origen);
            origen->aristas.erase(*temp);
            destino->aristas.erase(*tempo);
        }
    }

    void imprimirVectores(){
        for(int x = 0; x < vertices.size(); x++){
            cout<<vertices[x]->valor<<endl;
            for(multimap<Nodo*, int>::iterator i = vertices[x]->aristas.begin(); i != vertices[x]->aristas.end(); i++){
                cout<<"\t"<<(*i).first->valor<<" , "<<(*i).second<<endl;
            }
        }
    }

};

#endif // GRAFO

