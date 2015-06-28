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
    sceneOriginal = new QGraphicsScene();
    ui->painter->setScene(sceneOriginal);
    rectangle = new QGraphicsItemGroup();
    sizeEllipse = 100;
    initPainter();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(stick()));
    timer->start(1000);
}

GrafoForm::~GrafoForm()
{
    delete ui;
}

/*
Funcion para detener el timer cuando se cierre el formulario actual
*/
void GrafoForm::closeEvent (QCloseEvent *event)
{
    timer->stop();
}

/*
Funcion ejecutada cada segundo
Revisa si hay cambios en las posiciones de los vertices,
si las hay, actualiza las aristas
*/
void GrafoForm::stick(){
    vector<int> cambios;
    for(int x = 0; x < vertices.size(); x++){
        if(vertices[x]->pos() != grafo.vertices[x]->pos){
            cout<<"Cambio de posicion, nodo en la posicion: "<<x<<endl;
            cambios.push_back(x);
            grafo.vertices[x]->pos = vertices[x]->pos();
        }
    }
    //enviar los cambios a una funcion que actualize las aristas
}

/*
 *Funcion que actualiza las aristas del nodo en la posicion especificada
*/
void GrafoForm::updateAristas(int pos){
    multimap<Nodo*, int>::iterator i = grafo.vertices[pos]->aristas.begin();
    for(i; i != grafo.vertices[pos]->aristas.end(); i++){
        QGraphicsLineItem* linea = new QGraphicsLineItem();
        QGraphicsTextItem* texto = new QGraphicsTextItem();
        QGraphicsItemGroup *grupo = new QGraphicsItemGroup();

        //linea->setPos(vertices[pos]->pos());
        QPointF myPos = vertices[pos]->pos();
        QPointF otherPos = (*i).first->pos;
        //linea->setLine(myPos.x(), myPos.y(), otherPos.x(), otherPos.y());
        linea->setLine(otherPos.x() + sizeEllipse/2, otherPos.y()+ sizeEllipse/2, myPos.x()+ sizeEllipse/2, myPos.y()+ sizeEllipse/2);
        texto->setPlainText(QString::number((*i).second));
        int x = (myPos.x() + otherPos.x() + (sizeEllipse))/2;
        int y = (myPos.y() + otherPos.y() + (sizeEllipse))/2;
        texto->setPos(x,y);

        grupo->addToGroup(linea);
        grupo->addToGroup(texto);

        map<Nodo*, QGraphicsItemGroup*> items;
        items[(*i).first]=grupo;
        aristas.push_back(items);
        sceneOriginal->addItem(grupo);
    }
}

/*
 *Funcion que actualiza la arista 'destino' en el nodo especificado
*/
void GrafoForm::updateAristasToNodo(int pos, int destino){

}

void GrafoForm::initPainter(){
    QGraphicsRectItem* item1 = new QGraphicsRectItem(0,0,sizeEllipse+20,sizeEllipse+20);
    QGraphicsTextItem* texto = new QGraphicsTextItem();

    item1->setBrush(QBrush(Qt::gray));
    texto->setPos(10, -10);
    texto->setPlainText("Nuevo Nodo");

    rectangle->addToGroup(item1);
    rectangle->addToGroup(texto);

    sceneOriginal->addItem(rectangle);
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

void GrafoForm::fillPainter(char tipo){
    if(tipo == 'N'){
        QBrush redBrush(Qt::red);
        QPen blackPen(Qt::black);
        blackPen.setWidth(1);
        int lastPos = grafo.vertices.size()-1;
        string text = grafo.vertices[lastPos]->valor;

        QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem();
        ellipse->setRect(10, 15, sizeEllipse, sizeEllipse);
        ellipse->setBrush(redBrush);
        ellipse->setPen(blackPen);

        QGraphicsTextItem *texto = new QGraphicsTextItem();
        texto->setPlainText(QString::fromStdString(text));
        texto->setPos(50,50);

        QGraphicsItemGroup *grupo = new QGraphicsItemGroup();
        grupo->addToGroup(ellipse);
        grupo->addToGroup(texto);
        grupo->setAcceptDrops(true);
        grupo->setFlag(QGraphicsItem::ItemIsMovable, true);
        grupo->setZValue(1);

        vertices.push_back(grupo);
        sceneOriginal->addItem(grupo);
        grafo.vertices[lastPos]->pos = vertices[lastPos]->scenePos();
    }else{

    }
}

bool GrafoForm::readyToCreate(){
    for(int x = 0; x < vertices.size(); x++){
        if(rectangle->collidesWithItem(vertices[x]))
            return false;
    }
    return true;
}

void GrafoForm::on_insertar_clicked()//Insertar Vertice
{
    msg.setText("Ingrese un valor para el vertice");
    string valor = ui->txtValor->text().toStdString();
    if (valor != ""){
        if(!readyToCreate()){
            msg.setText("Un nodo ocupa el lugar de creacion del nuevo nodo, muevalo");
        }else{
            cout<<"Insertando"<<endl;
            Nodo* nuevo = new Nodo(valor);
            grafo.insertar(nuevo);
            fillPainter('N');
            fillCombos();
            msg.setText("Vertice creado exitosamente");
        }
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
                updateAristas(grafo.buscarPos(origen->valor));

                int posOrigen = ui->cmbOrigen->currentIndex();
                int posDestino = ui->cmbDestino->currentIndex();
                vertices[posOrigen]->setFlag(QGraphicsItem::ItemIsMovable, false);
                vertices[posDestino]->setFlag(QGraphicsItem::ItemIsMovable, false);

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
    msg.setText("Eliminacion de Vertice Fallida");
    int index =ui->cmbVertice->count();
    if(index>0){
        Nodo* eliminar = grafo.buscarNodo(ui->cmbVertice->currentText().toStdString());
        if(eliminar){
            vector<QGraphicsItemGroup*>::iterator i = vertices.begin();
            vector< map<Nodo*, QGraphicsItemGroup*> >::iterator j = aristas.begin();
            for(int x = 0; x < index; x++){
                i++;
                j++;
            }
//            (*i)->setVisible(false);
            //sceneOriginal->removeItem(vertices[index]);
            cout<<"Paso"<<endl;
            for(map<Nodo*, QGraphicsItemGroup*>::iterator y = (*j).begin(); y != (*j).end(); y++){
                sceneOriginal->removeItem((*y).second);
            }

            //aristas.erase(j);
            //vertices.erase(i);
            //grafo.eliminar(eliminar);
        }
    }
}

void GrafoForm::eliminarArista(Nodo* origen, Nodo* destino){
    int posOrigen = grafo.buscarPos(origen->valor);
    int posDestino = grafo.buscarPos(destino->valor);

    cout<<origen->valor<<endl;
    cout<<destino->valor<<endl;

    map<Nodo*, QGraphicsItemGroup*>::iterator i = aristas[posOrigen].begin();
    while(i != aristas[posOrigen].end()){
        if((*i).first == destino)
            break;
        i++;
    }
    aristas[posOrigen].erase(i);
//    QGraphicsItemGroup* grupo = aristas[posOrigen][destino];
//    sceneOriginal->destroyItemGroup(grupo);
//    grupo = aristas[posDestino][origen];
//    sceneOriginal->destroyItemGroup(aristas[posDestino][origen]);
}

void GrafoForm::on_eliminarArista_clicked()//Eliminar Arista
{
    msg.setText("Eliminacion de la Arista fallida");
    if(ui->cmbOrigen->count()>1){
        Nodo* origen = grafo.buscarNodo(ui->cmbOrigen->currentText().toStdString());
        Nodo* destino = grafo.buscarNodo(ui->cmbDestino->currentText().toStdString());
        if(origen && destino && origen != destino){
            eliminarArista(origen, destino);
        }
    }
}
