#ifndef GRAFO
#define GRAFO
#include "Nodo.h"
#include <map>

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

//    int* Dijkstra(Nodo* inicio){
//        enum Posicion{
//            Nodo, Distancia, Visitado, Path
//        };

//        int arreglo[vertices.size()][vertices.size()];
//        //llenando el arreglo
//        for(int x = 0; x < vertices.size(); x++){
//            arreglo[Nodo][x] = x;
//            arreglo[Distancia][x] = INT_MAX;
//            arreglo[Visitado][x] = 0;
//            arreglo[Path][x] = -1;
//        }

//        Cola cola;

//        cola.insert(inicio, 0);
//        arreglo[Distancia][buscarPos(inicio->valor)] = 0;

//        int actual , adyacente , peso;
//        while(!cola.empty()){
//            Arista* aristaActual = cola.pop();
//            int actual = buscarPos(aristaActual->arista.first->valor);
//            int distancia = aristaActual->arista.second;
//            if( arreglo[Visitado][ actual ] )
//                continue; //Si el vértice actual ya fue visitado entonces sigo sacando elementos de la cola
//            arreglo[Visitado][ actual ] = true;

//            multimap<Nodo* , int > aristas = vertices[actual]->aristas;

////            multimap< Nodo*, int >::iterator x = vertices[actual]->aristas.begin();
////            for(x; x != vertices[actual]->aristas.begin(); x++){

////            }
////            arreglo[Visitado][pos] = 1;
////            arreglo[Distancia][pos] = distancia;
////            arreglo[Path][pos] = pos;
//        }

////        return arreglo;
//    }

//    int* Floyd(){
//        int arreglo[vertices.size()][vertices.size()];
//    }

//    Grafo Kruskal(){

//    }

//    Grafo Prim(Nodo* inicio){

//    }
};

#endif // GRAFO

