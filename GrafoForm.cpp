#include "GrafoForm.h"
#include "ui_GrafoForm.h"

GrafoForm::GrafoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GrafoForm)
{
    msg.setWindowTitle("Formulario de Grafo");
    ui->setupUi(this);
    currentScale = 1;
    scaleFactor = 1.1;
    scaleMin = .1;
}

GrafoForm::~GrafoForm()
{
    delete ui;
}

void GrafoForm::on_zoomIn_clicked()
{
    currentScale*=scaleFactor;
    ui->painter->scale(scaleFactor,scaleFactor);
}

void GrafoForm::on_zoomOut_clicked()
{
    if(currentScale>scaleMin){
        currentScale/=scaleFactor;
        ui->painter->scale(1/scaleFactor,1/scaleFactor);
    }
}

void GrafoForm::getRandomPos(int &x, int &y){

}

void GrafoForm::fillCombos(){
    int cant = ui->cmbVertice->count();
    cout<<cant<<" , "<<grafo.vertices.size()<<endl;
    if(cant != grafo.vertices.size()){
        ui->cmbDestino->clear();
        ui->cmbOrigen->clear();
        ui->cmbVertice->clear();
        for(int x = 0; x < grafo.vertices.size(); x++){
            QString val = QString::fromStdString(grafo.vertices[x]->valor);
            ui->cmbDestino->addItem(val);
            ui->cmbOrigen->addItem(val);
            ui->cmbVertice->addItem(val);
        }
    }
}

void GrafoForm::on_insertar_clicked()//Insertar Vertice
{
    msg.setText("Ingrese un valor para el vertice");
    string valor = ui->txtValor->text().toStdString();
    if (valor != ""){
        cout<<"Insertando"<<endl;
        Nodo* nuevo = new Nodo(valor);
        grafo.insertar(nuevo);
        fillCombos();
        msg.setText("Vertice creado exitosamente");
    }
    msg.exec();
}

void GrafoForm::on_crearArista_clicked()//Crear Arista
{
    msg.setText("Creacion de la Arista fallida");
    if(ui->cmbOrigen->count()>1){
        Nodo* origen = grafo.buscarNodo(ui->cmbOrigen->currentText().toStdString());
        Nodo* destino = grafo.buscarNodo(ui->cmbDestino->currentText().toStdString());
        if(origen && destino && origen != destino){
            string texto = ui->txtArista->text().toStdString();
            if(texto != ""){
                int valor = ui->txtArista->text().toInt();
                grafo.crearArista(origen, destino, valor);
                msg.setText("Arista creada exitosamente");
            }else
                msg.setText("Ingrese un valor para la arista");
        }else
            msg.setText("No puede crear una arista a un mismo vertice");
    }
    msg.exec();
}

void GrafoForm::on_eliminarVertice_clicked()//Eliminar vertice
{
    grafo.imprimirVectores();
}
