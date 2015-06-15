#ifndef ORDENAMIENTOFORM_H
#define ORDENAMIENTOFORM_H

#include <QWidget>
#include <iostream>
using namespace std;

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
    int* binSort(int valores[1000]);
    int* mergeSort(int valores[1000]);
    int* quickSort(int valores[1000]);
    int* heapSort(int valores[1000]);
    int* burbujaSort(int valores[1000]);

private slots:
    void on_bubble_clicked();

    void on_random_clicked();

private:
    Ui::OrdenamientoForm *ui;
};

#endif // ORDENAMIENTOFORM_H
