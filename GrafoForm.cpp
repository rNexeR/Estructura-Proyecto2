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
    sceneDijkstra = new QGraphicsScene();
    sceneFloyd = new QGraphicsScene();
    sceneKruskal = new QGraphicsScene();
    scenePrim = new QGraphicsScene();
    ui->painter->setScene(sceneOriginal);
    sizeEllipse = 100;

//    Nodo* nodo = new Nodo("A");
//    nodo->pos = QPointF(150,150);
//    grafo.insertar(nodo);

//    Nodo* nodo2 = new Nodo("B");
//    nodo2->pos = QPointF(350,350);
//    grafo.insertar(nodo2);

//    grafo.crearArista(nodo, nodo2, 3);

    initPainter(&grafo, sceneOriginal);
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
    //vector<int> cambios;
    for(int x = 0; x < vertices.size(); x++){
        if(vertices[x]->pos() != grafo.vertices[x]->pos){
            cout<<"Cambio de posicion, nodo en la posicion: "<<x<<endl;
            //cambios.push_back(x);
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

void GrafoForm::initPainter(Grafo *grafo, QGraphicsScene *scene){
    rectangle = new QGraphicsItemGroup();
    QGraphicsRectItem* item1 = new QGraphicsRectItem(0,0,sizeEllipse+20,sizeEllipse+20);
    QGraphicsTextItem* texto = new QGraphicsTextItem();

    item1->setBrush(QBrush(Qt::gray));
    texto->setPos(10, -10);
    texto->setPlainText("Nuevo Nodo");

    rectangle->addToGroup(item1);
    rectangle->addToGroup(texto);

    if(scene == sceneOriginal)
        scene->addItem(rectangle);

    for(int x = 0; x < (*grafo).vertices.size(); x++){
        crearVertice(grafo, scene, x);
        if(scene == sceneOriginal)
            vertices[x]->setFlag(QGraphicsItem::ItemIsMovable, false);
    }

    for(int x = 0; x < vertices.size(); x++){
        crearArista(grafo, scene, x);
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
        ui->cmbInicioDijkstra->clear();
        ui->cmbInicioPrim->clear();
        for(int x = 0; x < grafo.vertices.size(); x++){
            QString val = QString::fromStdString(grafo.vertices[x]->valor);
            ui->cmbDestino->addItem(val);
            ui->cmbOrigen->addItem(val);
            ui->cmbVertice->addItem(val);
            ui->cmbInicioDijkstra->addItem(val);
            ui->cmbInicioPrim->addItem(val);
        }
    }
}

void GrafoForm::crearVertice(Grafo *grafo, QGraphicsScene* scene, int pos){
    vector<QGraphicsItemGroup*> *vertices = &(this->vertices);

    if(scene == sceneKruskal)
        vertices = &verticesKruskal;
    else if(scene == scenePrim)
        vertices = &verticesPrim;


        QBrush redBrush(Qt::red);
        QPen blackPen(Qt::black);
        blackPen.setWidth(1);
        int lastPos = pos;
        string text = (*grafo).vertices[lastPos]->valor;

        QPointF posi = (*grafo).vertices[lastPos]->pos;

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
        if(scene == sceneOriginal)
            grupo->setFlag(QGraphicsItem::ItemIsMovable, true);
        grupo->setZValue(1);
        grupo->setPos(posi);

        vertices->push_back(grupo);
        scene->addItem(grupo);
        (*grafo).vertices[lastPos]->pos = (*vertices)[lastPos]->scenePos();
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
            if(grafo.insertar(nuevo)){
            crearVertice(&grafo, sceneOriginal, grafo.vertices.size()-1);
            fillCombos();
            msg.setText("Vertice creado exitosamente");
            }
        }
    }
    msg.exec();
}

/*
 *Funcion que actualiza las aristas del nodo en la posicion especificada
*/
void GrafoForm::crearArista(Grafo *grafo, QGraphicsScene* scene, int pos){
    vector<QGraphicsItemGroup*> *vertices = &(this->vertices);

    if(scene == sceneKruskal)
        vertices = &verticesKruskal;
    else if(scene == scenePrim){
        vertices = &verticesPrim;
    }


    multimap<Nodo*, int>::iterator i = (*grafo).vertices[pos]->aristas.begin();
    for(i; i != (*grafo).vertices[pos]->aristas.end(); i++){
        QGraphicsLineItem* linea = new QGraphicsLineItem();
        QGraphicsTextItem* texto = new QGraphicsTextItem();
        QGraphicsItemGroup *grupo = new QGraphicsItemGroup();

        //linea->setPos(vertices[pos]->pos());
        QPointF myPos = (*vertices)[pos]->pos();
        QPointF otherPos = (*i).first->pos;
        //linea->setLine(myPos.x(), myPos.y(), otherPos.x(), otherPos.y());
        linea->setLine(otherPos.x() + sizeEllipse/2, otherPos.y()+ sizeEllipse/2, myPos.x()+ sizeEllipse/2, myPos.y()+ sizeEllipse/2);
        texto->setPlainText(QString::number((*i).second));
        int x = (myPos.x() + otherPos.x() + (sizeEllipse))/2;
        int y = (myPos.y() + otherPos.y() + (sizeEllipse))/2;
        texto->setPos(x,y);

        grupo->addToGroup(linea);
        grupo->addToGroup(texto);
        scene->addItem(grupo);
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
                crearArista(&grafo, sceneOriginal, grafo.buscarPos(origen->valor));

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
            initPainter(&grafo, sceneOriginal);
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

void GrafoForm::on_crearArista_6_clicked()//Ver Grafo Original
{
    ui->painter->setScene(sceneOriginal);
}

void GrafoForm::on_crearArista_2_clicked()//Dijkstra
{
    ui->painter->setScene(sceneDijkstra);
    if(ui->cmbInicioDijkstra->count()>1){
        Nodo* origen = grafo.buscarNodo(ui->cmbInicioDijkstra->currentText().toStdString());
        if(origen){
            Dijkstra(origen);
        }
    }
}

void GrafoForm::on_crearArista_3_clicked()//Floyd
{
    ui->painter->setScene(sceneFloyd);
    Floyd();
}

void GrafoForm::on_crearArista_5_clicked()//Prim
{
    ui->painter->setScene(scenePrim);
    if(ui->cmbInicioPrim->count()>1){
        Nodo* origen = grafo.buscarNodo(ui->cmbInicioPrim->currentText().toStdString());
        if(origen){
            Grafo prim = Prim(origen);
            initPainter(&prim, scenePrim);
        }
    }
    //Grafo prim = Prim();
}

void GrafoForm::on_crearArista_4_clicked()//Kruskal
{
    ui->painter->setScene(sceneKruskal);
    Grafo kruskal = Kruskal();
    initPainter(&kruskal, sceneKruskal);
}

void GrafoForm::Dijkstra(Nodo* inicio){
    //vector<Nodo*> vertices = grafo.vertices;
    cout<<"Haciendo Dijkstra"<<endl;

    int arreglo[4][grafo.vertices.size()];
    //llenando el arreglo
    for(int x = 0; x < grafo.vertices.size(); x++){
        arreglo[POSICION][x] = x;
        arreglo[DISTANCIA][x] = INT_MAX;
        arreglo[VISITADO][x] = 0;
        arreglo[PATH][x] = -1;
    }

    Cola cola;

    cola.insert(inicio, 0);
    arreglo[DISTANCIA][grafo.buscarPos(inicio->valor)] = 0;

    int actual , adyacente , peso;
    while(!cola.empty()){
        Arista* aristaActual = cola.pop();
        int actual = grafo.buscarPos(aristaActual->arista.first->valor);
        cout<<"Actual: "<<actual<<endl;
        int distancia = aristaActual->arista.second;
        if( arreglo[VISITADO][ actual ] ){
            continue; //Si el vértice actual ya fue visitado entonces sigo sacando elementos de la cola
        }
        arreglo[VISITADO][ actual ] = true;

        //multimap<Nodo* , int > aristas = grafo.vertices[actual]->aristas;

        Nodo *este;
        este = grafo.vertices[actual];
        for(multimap< Nodo* , int >::iterator x = este->aristas.begin(); x != este->aristas.end(); x++){
            adyacente = grafo.buscarPos((*x).first->valor);   //id del vertice adyacente
            peso = (*x).second;        //peso de la arista que une actual con adyacente ( actual , adyacente )
            if( !arreglo[VISITADO][ adyacente ] ){        //si el vertice adyacente no fue visitado
                //relajacion
                if( arreglo[DISTANCIA][ actual ] + peso < arreglo[DISTANCIA][ adyacente ] ){
                    arreglo[DISTANCIA][ adyacente ] = arreglo[DISTANCIA][ actual ] + peso;  //relajamos el vertice actualizando la distancia
                    arreglo[PATH][ adyacente ] = actual;                         //a su vez actualizamos el vertice previo
                    cola.insert( grafo.vertices[adyacente], peso ); //agregamos adyacente a la cola de prioridad
                }
            }
        }
    }

    QGraphicsTextItem* texto = new QGraphicsTextItem();
    texto->setPlainText("DIJKSTRA");
    texto->setPos(100, -50);
    sceneDijkstra->addItem(texto);
    for(int y = 0; y < 4; y++){
        QGraphicsTextItem* texto = new QGraphicsTextItem();
        QString text = "";
        if(y == 0)
            text = "Nodo";
        else if(y ==1)
            text = "Distancia";
        else if(y == 2)
            text = "Visitado";
        else
            text = "Path";
        texto->setPlainText(text);
        texto->setPos(0,y*50);
        sceneDijkstra->addItem(texto);
        for(int z = 0; z < grafo.vertices.size(); z++){
            cout<<arreglo[y][z]<<" ";

            QString nodo = "";
            if (y == 0)
                nodo = QString::fromStdString(grafo.vertices[arreglo[y][z]]->valor);
            else
                nodo = QString::number(arreglo[y][z]);

            QGraphicsTextItem* texto = new QGraphicsTextItem();
            texto->setPlainText(nodo);
            texto->setPos(((z+1)*100),y*50 );
            sceneDijkstra->addItem(texto);
        }
        cout<<endl;
    }
}

void GrafoForm::Floyd(){
    int distancias[grafo.vertices.size()][grafo.vertices.size()];
    int recorrido[grafo.vertices.size()][grafo.vertices.size()];

    //inicializar el arreglo con 0 e infinitos
    for(int y = 0; y < grafo.vertices.size(); y++){
        for(int z = 0; z < grafo.vertices.size(); z++){
            if(y == z)
                distancias[y][z] = 0;
            else
                distancias[y][z] = INT_MAX;
            recorrido[y][z] = z;
        }
    }

    for(int x = 0; x < grafo.vertices.size(); x++){
        Nodo* actual = grafo.vertices[x];
        for(multimap< Nodo* , int >::iterator y = actual->aristas.begin(); y != actual->aristas.end(); y++){
            int pos = grafo.buscarPos((*y).first->valor);
            distancias[x][pos] = (*y).second;
            recorrido[x][pos] = x;
        }
    }

    for(int i = 0; i < grafo.vertices.size(); i++){
        for(int j = 0; j < grafo.vertices.size(); j++){
            for(int k = 0; k < grafo.vertices.size(); k++){
                int suma = distancias[j][i] + distancias[i][k];
                if(distancias[j][k] > suma){
                    distancias[j][k] = suma;
                    recorrido[j][k] = i;
                }
            }
        }
    }

    cout<<endl<<"Distancias"<<endl;
    QGraphicsTextItem* texto = new QGraphicsTextItem();
    texto->setPlainText("FLOYD");
    texto->setPos(100, -100);
    sceneFloyd->addItem(texto);

    texto = new QGraphicsTextItem();
    texto->setPlainText("Distancias");
    texto->setPos(100, -50);
    sceneFloyd->addItem(texto);

    for(int i = 0; i < grafo.vertices.size(); i++){
        for(int j = 0; j < grafo.vertices.size(); j++){
            cout<<distancias[i][j]<<" ";
            QGraphicsTextItem* texto = new QGraphicsTextItem();
            texto->setPlainText(QString::number(distancias[i][j]));
            texto->setPos(j*100, i*50);
            sceneFloyd->addItem(texto);
        }
        cout<<endl;
    }

    cout<<endl<<"Recorridos"<<endl;
    texto = new QGraphicsTextItem();
    texto->setPlainText("Recorridos");
    int x_min = grafo.vertices.size() * 100;
    x_min+=50;
    texto->setPos(x_min + 100, -50);
    sceneFloyd->addItem(texto);
    for(int i = 0; i < grafo.vertices.size(); i++){
        for(int j = 0; j < grafo.vertices.size(); j++){
            cout<<recorrido[i][j]<<" ";
            QGraphicsTextItem* texto = new QGraphicsTextItem();
            texto->setPlainText(QString::number(recorrido[i][j]));
            texto->setPos(x_min + (j*100), i*50);
            sceneFloyd->addItem(texto);
        }
        cout<<endl;
    }
}

Grafo GrafoForm::Prim(Nodo *inicio){
    grafo.resetPrim();
    Grafo prim;
    Nodo* nodo = new Nodo(inicio->valor);
    nodo->pos = inicio->pos;
    prim.insertar(nodo);
    grafo.vertices[0]->prim = true;

    ColaDoble cola;
    for(multimap< Nodo* , int >::iterator y = inicio->aristas.begin(); y != inicio->aristas.end(); y++){
        cola.insert(inicio, (*y).first, (*y).second);
    }

    cout<<"Entro al While"<<endl;

    while(prim.vertices.size() < grafo.vertices.size()){
        AristaDoble* actual = cola.pop();
        if(!actual->destino->prim){

            cout<<actual->origen->valor<<" , "<<actual->destino->valor<< " : "<<actual->costo<<endl;

            Nodo* nuevo = new Nodo(actual->destino->valor);
            nuevo->pos = actual->destino->pos;
            prim.insertar(nuevo);

            prim.crearArista(prim.buscarNodo(actual->origen->valor), nuevo, actual->costo);
            Nodo* este = actual->destino;
            for(multimap< Nodo* , int >::iterator y = este->aristas.begin(); y != este->aristas.end(); y++){
//                if(!(*y).first->prim){
                    cout<<"\t Agregando a la Cola: "<<(*y).first->valor<<endl;
                    cola.insert(este, (*y).first, (*y).second);
//                }
            }
            actual->destino->prim = true;
        }
    }

    return prim;
}

int idDistinto(int arreglo[][4], int size){
    for(int x = 0; x < size; x++){
        if(arreglo[x][3] != 0)
            return x;
    }
    return -1;
}

bool seCreaCiclo(int arreglo[][4], int size, int n1, int n2){
    bool sn1 =false, sn2 = false;
    for(int x = 0; x < size; x++){
        if(arreglo[x][3] != 0)
            continue;
        if(arreglo[x][0] == n1)
            sn1 = true;
        if(arreglo[x][0] == n2)
            sn2 = true;
        if(sn1 && sn2)
            return true;
//        if(arreglo[x][0] == n1 && arreglo[x][1] == n2 || arreglo[x][0] == n2 && arreglo[x][1] == n1)
//            return true;
    }
    return false;
}

Grafo GrafoForm::Kruskal(){
    grafo.resetKruskal();
    Grafo krustal;
    int cantAristas = grafo.cantAristas();
    int arreglo[cantAristas][4];

    ColaDoble cola;
    //llenando la cola
    for(int x = 0; x < grafo.vertices.size(); x++){
        Nodo* actual = grafo.vertices[x];
        Nodo* nuevo = new Nodo(actual->valor);
        nuevo->pos = actual->pos;
        for(multimap< Nodo* , int >::iterator y = actual->aristas.begin(); y != actual->aristas.end(); y++){
            Nodo* actual2 = (*y).first;
            Nodo* nuevo2 = new Nodo(actual2->valor);
            nuevo2->pos = actual2->pos;
            //cout<<"cola"<<endl;
            cola.insert(nuevo, nuevo2, (*y).second);
        }
    }

    cout<<"Size de la cola"<<cola.size<<endl;
    //pasando los valores de la cola al arreglo y agregar el vertice al grafo
    for(int x = 0; x < cantAristas; x++){
        AristaDoble* tope = cola.pop();
        //Insertandolo en el Grafo
        Nodo* origen = tope->origen;
        Nodo* destino = tope->destino;
        if(!krustal.buscarNodo(origen->valor))
            krustal.insertar(origen);
        if(!krustal.buscarNodo(destino->valor))
            krustal.insertar(destino);

        arreglo[x][0] = krustal.buscarPos(tope->origen->valor);
        arreglo[x][1] = krustal.buscarPos(tope->destino->valor);
        arreglo[x][2] = tope->costo;
        arreglo[x][3] = x+1;
    }

    //conectando los Nodos con aristas
    int pos = idDistinto(arreglo, cantAristas);
    while(pos != -1){
        if(!seCreaCiclo(arreglo, cantAristas, arreglo[pos][0], arreglo[pos][1])){
            Nodo* origen = krustal.vertices[arreglo[pos][0]];
            Nodo* destino = krustal.vertices[arreglo[pos][1]];
            krustal.crearArista(origen, destino, arreglo[pos][2]);
        }
        arreglo[pos][3] = 0;
        pos = idDistinto(arreglo, cantAristas);
    }
    return krustal;
}
