#ifndef ORDENAMIENTOFORM_H
#define ORDENAMIENTOFORM_H

#include <QWidget>

namespace Ui {
class OrdenamientoForm;
}

class OrdenamientoForm : public QWidget
{
    Q_OBJECT

public:
    explicit OrdenamientoForm(QWidget *parent = 0);
    ~OrdenamientoForm();
    int valores[1000];

public slots:
    void Randomizar();
    void Limpiar();
    void Ordenar();
    int binSort(int valores[1000]);
    int mergeSort(int valores[1000]);
    int quickSort(int valores[1000]);
    int heapSort(int valores[1000]);
    int burbujaSort(int valores[1000]);

private:
    Ui::OrdenamientoForm *ui;
};

#endif // ORDENAMIENTOFORM_H
