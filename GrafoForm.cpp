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
    sizeEllipse = 100;

//    Nodo* nodo = new Nodo("A");
//    nodo->pos = QPointF(150,150);
//    grafo.insertar(nodo);

//    Nodo* nodo2 = new Nodo("B");
//    nodo2->pos = QPointF(350,350);
//    grafo.insertar(nodo2);

//    grafo.crearArista(nodo, nodo2, 3);

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
 *Funcion que actualiza la arista 'destino' en el nodo especificado
*/
void GrafoForm::updateAristasToNodo(int pos, int destino){

}

void GrafoForm::initPainter(){
    rectangle = new QGraphicsItemGroup();
    QGraphicsRectItem* item1 = new QGraphicsRectItem(0,0,sizeEllipse+20,sizeEllipse+20);
    QGraphicsTextItem* texto = new QGraphicsTextItem();

    item1->setBrush(QBrush(Qt::gray));
    texto->setPos(10, -10);
    texto->setPlainText("Nuevo Nodo");

    rectangle->addToGroup(item1);
    rectangle->addToGroup(texto);

    sceneOriginal->addItem(rectangle);

    for(int x = 0; x < grafo.vertices.size(); x++){
        crearVertice(x);
        vertices[x]->setFlag(QGraphicsItem::ItemIsMovable, false);
    }

    for(int x = 0; x < vertices.size(); x++){
        crearArista(x);
    }
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

void GrafoForm::crearVertice(int pos){
        QBrush redBrush(Qt::red);
        QPen blackPen(Qt::black);
        blackPen.setWidth(1);
        int lastPos = pos;
        string text = grafo.vertices[lastPos]->valor;

        QPointF posi = grafo.vertices[lastPos]->pos;

        QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem();
        ellipse->setRect(10, 15, sizeEllipse, sizeEllipse);
        ellipse->setBrush(redBrush);
        ellipse->setPen(blackPen);
        //ellipse->setPos(posi);


        QGraphicsTextItem *texto = new QGraphicsTextItem();
        texto->setPlainText(QString::fromStdString(text));
        texto->setPos(50,50);

        QGraphicsItemGroup *grupo = new QGraphicsItemGroup();
        grupo->addToGroup(ellipse);
        grupo->addToGroup(texto);
        grupo->setAcceptDrops(true);
        grupo->setFlag(QGraphicsItem::ItemIsMovable, true);
        grupo->setZValue(1);
        grupo->setPos(posi);

        vertices.push_back(grupo);
        sceneOriginal->addItem(grupo);
        grafo.vertices[lastPos]->pos = vertices[lastPos]->scenePos();
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
    msg.setText("Creacion de Vertice fallida");
    string valor = ui->txtValor->text().toStdString();
    if (valor != "" & !grafo.buscarNodo(valor)){
        if(!readyToCreate()){
            msg.setText("Un nodo ocupa el lugar de creacion del nuevo nodo, muevalo");
        }else{
            cout<<"Insertando"<<endl;
            Nodo* nuevo = new Nodo(valor);
            grafo.insertar(nuevo);
            crearVertice(grafo.vertices.size()-1);
            fillCombos();
            msg.setText("Vertice creado exitosamente");
        }
    }
    msg.exec();
}

/*
 *Funcion que actualiza las aristas del nodo en la posicion especificada
*/
void GrafoForm::crearArista(int pos){
    multimap<Nodo*, int>::iterator i = grafo.vertices[pos]->aristas.begin();
    for(i; i != grafo.vertices[pos]->aristas.end(); i++){
        cout<<"Creando Arista"<<endl;
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
        cout<<texto->pos().x()<<" , "<<texto->pos().y()<<endl;

        grupo->addToGroup(linea);
        grupo->addToGroup(texto);
        sceneOriginal->addItem(grupo);
    }
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
                crearArista(grafo.buscarPos(origen->valor));

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
        int eliminar = grafo.buscarPos(ui->cmbVertice->currentText().toStdString());
        if(eliminar != -1){
            vector<QGraphicsItemGroup*>::iterator i = vertices.begin();
            QList<QGraphicsItem*> items = sceneOriginal->items();
                for (int i = 0; i < items.size(); i++) {
                    sceneOriginal->removeItem(items[i]);
                    delete items[i];
                }
            for(int x = 0; x < vertices.size()-1; x++){
                vertices.erase(i);
                i++;
            }
            vertices.clear();
            grafo.eliminar(grafo.vertices[eliminar]);
            initPainter();
        }
    }
}

void GrafoForm::eliminarArista(Nodo* origen, Nodo* destino){
}

void GrafoForm::on_eliminarArista_clicked()//Eliminar Arista
{
    msg.setText("Eliminacion de la Arista fallida");
    if(ui->cmbOrigen->count()>1){
        Nodo* origen = grafo.buscarNodo(ui->cmbOrigen->currentText().toStdString());
        Nodo* destino = grafo.buscarNodo(ui->cmbDestino->currentText().toStdString());
        if(origen && destino && origen != destino){

        }
    }
}
