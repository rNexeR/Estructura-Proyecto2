#ifndef ORDENAMIENTOFORM_H
#define ORDENAMIENTOFORM_H

#include <QWidget>
#include <QTime>
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
    int cant = 500000;
    int valores1[500000];
    int valores2[500000];
    int valores3[500000];
    int valores4[500000];
    int valores5[500000];

public slots:
    void binSort(int sarray[], int array_size);

    void merge(int a[], const int low, const int mid, const int high);
    void merge_sort( int a[], const int low, const int high );

    int divide(int *array, int start, int end);
    void quicksort(int *array, int start, int end);

    void swap(int &x,int &y);
    void heapify(int x, int a[], int n, int hs);
    void BuildMaxHeap(int a[], int n, int hs);
    void HeapSort(int a[], int n);

    int* burbujaSort(int valores[]);


private slots:
    void on_bubble_clicked();

    void on_random_clicked();

    void on_quick_clicked();

    void on_quick_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::OrdenamientoForm *ui;
};

#endif // ORDENAMIENTOFORM_H
