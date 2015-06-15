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

int* OrdenamientoForm::binSort(int valores[1000]){

}

int* OrdenamientoForm::mergeSort(int valores[1000]){
    return 0;
}

int* OrdenamientoForm::quickSort(int valores[1000]){
    return 0;
}

int* OrdenamientoForm::heapSort(int valores[1000]){
    return 0;
}

int* OrdenamientoForm::burbujaSort(int valores[1000]){
    int* sort = valores;
    bool swapped = false;
    int sorted = 0;
    do{
        swapped = false;
        for(int x = 0; x<(1000-sorted); x++){
            if(sort[x] > sort[x+1]){
                int y = sort[x];
                sort[x] = sort[x+1];
                sort[x+1] = y;
                swapped=true;
            }
        }
        sorted++;
    }while(swapped);
    for(int x = 0; x<30; x++)
        cout<<sort[x]<<endl;
    return sort;
}

void OrdenamientoForm::on_bubble_clicked()
{
    burbujaSort(valores);
}

void OrdenamientoForm::on_random_clicked()
{
    for(int x = 0; x<1000; x++)
        valores[x] = rand()%1000;
}
