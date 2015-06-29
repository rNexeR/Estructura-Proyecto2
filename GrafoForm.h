#ifndef GRAFOFORM_H
#define GRAFOFORM_H
#include "Grafo.h"

#include <QWidget>
#include <QMessageBox>
#include <QGraphicsObject>
#include <QTimer>

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

    void on_crearArista_clicked();

    void on_eliminarVertice_clicked();

    void on_eliminarArista_clicked();

private:
    Ui::GrafoForm *ui;

    Grafo grafo;
    QMessageBox msg;
    QTimer *timer;

    //GraphicView
    double currentScale, scaleMin, scaleFactor;
    QGraphicsItemGroup* rectangle;
    QGraphicsScene *sceneOriginal, *sceneKruskal, *scenePrim;
    vector<QGraphicsItemGroup*> vertices;
    int sizeEllipse;


    //Arreglo de Vertices
};

#endif // GRAFOFORM_H
