#ifndef GRAFOFORM_H
#define GRAFOFORM_H
#include "Grafo.h"

#include <QWidget>
#include <QMessageBox>
#include <QGraphicsObject>
#include <QTimer>

enum Posicion{
    POSICION, DISTANCIA, VISITADO, PATH
};

struct Arista{
    pair<Nodo*, int> arista;
    Arista* sig;
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

namespace Ui {
class GrafoForm;
}

class GrafoForm : public QWidget
{
    Q_OBJECT

public:
    explicit GrafoForm(QWidget *parent = 0);
    ~GrafoForm();

public slots:
    void stick();
    void closeEvent (QCloseEvent *event);

private slots:
    void on_zoomIn_clicked();

    void on_zoomOut_clicked();

    void on_insertar_clicked();

    void getRandomPos(int &x, int &y);

    void fillCombos();
    void crearVertice(int pos);
    void initPainter();
    bool readyToCreate();
    void crearArista(int pos);
    void updateAristasToNodo(int pos, int destino);
    void eliminarArista(Nodo* origen, Nodo* destino);

    //void relajacion( int actual , int adyacente , int peso  );
    void Dijkstra(Nodo* inicio);
    void Floyd();
    void Prim(Nodo* inicio);
    void Kruskal();

    void on_crearArista_clicked();

    void on_eliminarVertice_clicked();

    void on_eliminarArista_clicked();

    void on_crearArista_6_clicked();

    void on_crearArista_2_clicked();

    void on_crearArista_3_clicked();

    void on_crearArista_5_clicked();

    void on_crearArista_4_clicked();

private:
    Ui::GrafoForm *ui;

    Grafo grafo;
    QMessageBox msg;
    QTimer *timer;

    //GraphicView
    double currentScale, scaleMin, scaleFactor;
    QGraphicsItemGroup* rectangle;
    QGraphicsScene *sceneOriginal, *sceneKruskal, *scenePrim, *sceneDijkstra, *sceneFloyd;
    vector<QGraphicsItemGroup*> vertices;
    int sizeEllipse;

    //Dijkstra
    //int Dijks[][];
    //Cola colaDijkstra;


    //Arreglo de Vertices
};

#endif // GRAFOFORM_H
