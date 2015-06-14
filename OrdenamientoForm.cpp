#include "OrdenamientoForm.h"
#include "ui_OrdenamientoForm.h"

OrdenamientoForm::OrdenamientoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrdenamientoForm)
{
    ui->setupUi(this);
}

OrdenamientoForm::~OrdenamientoForm()
{
    delete ui;
}

void OrdenamientoForm::Randomizar(){

}

void OrdenamientoForm::Limpiar(){

}

void OrdenamientoForm::Ordenar(){

}

int OrdenamientoForm::binSort(int valores[1000]){
    return 0;
}

int OrdenamientoForm::mergeSort(int valores[1000]){
    return 0;
}

int OrdenamientoForm::quickSort(int valores[1000]){
    return 0;
}

int OrdenamientoForm::heapSort(int valores[1000]){
    return 0;
}

int OrdenamientoForm::burbujaSort(int valores[1000]){
    return 0;
}
