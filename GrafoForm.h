#ifndef GRAFOFORM_H
#define GRAFOFORM_H
#include "Grafo.h"

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class GrafoForm;
}

class GrafoForm : public QWidget
{
    Q_OBJECT

public:
    explicit GrafoForm(QWidget *parent = 0);
    ~GrafoForm();

private slots:
    void on_zoomIn_clicked();

    void on_zoomOut_clicked();

    void on_insertar_clicked();

    void getRandomPos(int &x, int &y);

    void fillCombos();
    void on_crearArista_clicked();

    void on_eliminarVertice_clicked();

private:
    Ui::GrafoForm *ui;

    Grafo grafo;
    QMessageBox msg;

    //GraphicView
    double currentScale, scaleMin, scaleFactor;

    //Arreglo de Vertices
};

#endif // GRAFOFORM_H
