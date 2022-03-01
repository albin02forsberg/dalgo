#include "mainwindow.h"
#include "mapwidget.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>

#include <stdio.h>

#include <graph.h>
#include <assert.h>
#include <algorithm>

#include "student1drawgraph.h"


using namespace std;

float distance(const QPoint& pt1, const QPoint& pt2);

float myAbs(float f){
    return (f<0? -f : f);
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle( QString("Grafritare ") + QString::fromUtf8( nameOfStudent1() ) );
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::knownDistanceToNode(Ixnode ixNode, float dist)
{
    // Denna v ersion  anropas av ragnarsTest
    assert( dist >= _distanceLastKnown );
    _distanceLastKnown = dist;

}
void MainWindow::nodeWasPlacedInPriorityQueue(Ixnode ixNode){

}

void MainWindow::nodeWasPoppedFromPriorityQueue(Ixnode ixNode){

}

//     6371L, 1811L, //  0

Graph MainWindow::readGraph(QString xyFilename, QString linksFilename){

    QFile fileXY(xyFilename);
    QFile fileLinks(linksFilename);

    bool ok = fileXY.open(QFile::ReadOnly | QFile::Text)
            &&  fileLinks.open(QFile::ReadOnly | QFile::Text);

    if(!ok){
        qDebug() << "readGraph - could not open files for read!";
        return Graph();
    }

    Graph graph;

    char aLine[100];

    const int maximumY = 4235;
    while (fileXY.readLine(aLine, 100) >0) {
        int x,yUpsidedown;
        sscanf(aLine, "%dL, %dL, ", &x, &yUpsidedown);
        int y =  maximumY - yUpsidedown;
        Node node;
        node._point = QPoint(200+x,400+y);
        graph.push_back( node );
    }
    qDebug() << "maximumY " << maximumY;
    fileXY.close();

    const int numberOfNodes = graph.size();
    while (fileLinks.readLine(aLine, 100) >0) {
        int ixSource, ixDestination;
        sscanf(aLine, "%dL, %dL, ", &ixSource, &ixDestination);

        assert( ixSource>=0 && ixSource<numberOfNodes );
        assert( ixDestination>=0 && ixDestination<numberOfNodes );

        float cost = distance(graph[ixSource]._point, graph[ixDestination]._point);
        addPath((graph), ixSource, ixDestination, cost);

    }
    fileLinks.close();

    qDebug() << "graph - succeded (?)";
    return graph;
}






Graph MainWindow::randomGraphWithGaps()
{
    const int numR = 20;
    const int numK = 40;

    const int numNodes = numR*numK;


    Graph graph = std::vector<Node>( numNodes, Node() );

    for (int r=0; r<numR ; r+=1)
        for (int k=0; k<numK; k+=1){
            int index = r*numK + k;
            graph[index]._point = QPoint(500+k*100, 500+r*100+rand()%40);

        }

    for (int r=0; r<numR ; r+=1)
        for (int k=0; k<numK; k+=1){
            int index = r*numK + k;


            if (k<(numK-1)) { //  && rand()%2){
                int i = r*numK + k+1;
                bool  isVisible = (rand()%100 <= 50);
                float cost = distance(graph[index]._point, graph[i]._point) *(isVisible?1:25);

                addPath(graph, index, i, cost, isVisible);
            }
            if (r<(numR-1) & rand()%100 < 90 ){
                int i = (r+1)*numK + k;
                bool  isVisible = (rand()%100 <= 50);
                float cost = distance(graph[index]._point, graph[i]._point) *(isVisible?1:25);

                addPath(graph, index, i, cost, isVisible);
            }



        }

    return graph;
}

void MainWindow::addPath(Graph& graph, Ixnode ix1, Ixnode ix2, float cost, bool visible){
    graph[ix1]._outputs.push_back( Arc(ix2, visible, cost));
    graph[ix2]._outputs.push_back( Arc(ix1, visible, cost));

}

Graph MainWindow::graphWith5Nodes(){

    Graph graph = std::vector<Node>( 5, Node() );

    graph[0]._point = QPoint(100,100);
    graph[1]._point = QPoint(500, 50);
    graph[2]._point = QPoint(200,200);
    graph[3]._point = QPoint(300, 250);
    graph[4]._point = QPoint(600, 200);

    addPath((graph), 0, 1, 5.0);
    addPath((graph), 0, 2, 1.0);

    addPath((graph), 2, 1, 3.0);
    addPath((graph), 2, 3, 1.0);

    addPath((graph), 3,1, 1.0 );
    addPath((graph), 3,4, 1.0 );

    addPath((graph), 4,1, 2.0 );

    return graph;
}


void MainWindow::on_action5Noder_triggered()
{
    newGraphSelected();

    Graph &theGraph = ui->centralWidget->_theGraph;

    theGraph = graphWith5Nodes();

    ui->centralWidget->setImage(nullptr);
    ui->centralWidget->graphChanged();


}

void MainWindow::on_actionRandom_A_triggered()
{
    newGraphSelected();

    Graph &theGraph = ui->centralWidget->_theGraph;

    theGraph = randomGraphWithGaps();
    ui->centralWidget->setImage(nullptr);

    ui->centralWidget->graphChanged();

}

void MainWindow::on_actionUSA_triggered()
{
    newGraphSelected();

    Graph &theGraph = ui->centralWidget->_theGraph;

    theGraph = readGraph(":/texter/usaxy.txt", ":/texter/usalinks.txt" );
    ui->centralWidget->setImage(nullptr);

    ui->centralWidget->graphChanged();

}

void MainWindow::on_actionUSA_FLYG_triggered()
{

    Graph &theGraph = ui->centralWidget->_theGraph;
    theGraph = readGraph(":/texter/usaxy.txt", ":/texter/usalinks.txt" );


    const int ixWest = 4187;
    const int ixMid = 39791;
    const int ixEast = 81509;

    float f = 0.05;
    float costWM = f*distance(theGraph[ixWest]._point, theGraph[ixMid]._point);
    float costME = f*distance(theGraph[ixMid]._point, theGraph[ixEast]._point);
    float costWE = f*distance(theGraph[ixWest]._point, theGraph[ixEast]._point);

    addPath((theGraph), ixWest, ixMid, costWM);
    addPath((theGraph), ixMid, ixEast, costME);
    addPath((theGraph), ixWest, ixEast, costWE);

    ui->centralWidget->setImage(nullptr);

    ui->centralWidget->graphChanged();
}


float MainWindow::costOfPathInGraph(const vector<Ixnode>& backwardspath, const vector<Node>&graph){
    float totalCost = 0;
    Ixnode ixPrev = backwardspath.back();
    for (int k=0  ; k<backwardspath.size()-1 ; k+=1){
        Ixnode ixTo = backwardspath[k];
        Ixnode ixFrom = backwardspath[k+1];
        float costBetweenPrevAndIx = 9.9e10;
        for (Arc  n : graph[ixFrom]._outputs)
            if (n.m_ixDestination == ixTo)
                costBetweenPrevAndIx = n.m_cost;
        totalCost += costBetweenPrevAndIx;
    }

    assert( totalCost < 9.9e10 );
    return totalCost;
}

bool MainWindow::ragnarsTest(const Graph& graph, Ixnode ix1, Ixnode ix2, float trueCost){


    _distanceLastKnown = 0;
    QString nameOfStudent = QString::fromUtf8(nameOfStudent2());
    QString txt = QString("ragnarsTest: testar shortestPath av ") + nameOfStudent;
    QMessageBox::information(this, nameOfStudent, txt );

    if (nameOfStudent=="Homer Simpson"){
        QMessageBox::critical(this, nameOfStudent, "Felaktigt namn:" + nameOfStudent);
        return false;
    }

    vector<Ixnode> backpath = shortestPathBetweenNodes(graph, ix1,ix2, this);


    bool ok =  backpath.front()==ix2 && backpath.back()==ix1; // skall vara baklänges
    if (!ok){
        QMessageBox::information(this,"Ragnars Test", "Baklängesväg returnerades ej!!!!!");
        return false;
    }

    float cost = costOfPathInGraph( backpath, graph);
    if (myAbs(cost-trueCost) >0.1){
        QString str = "BUG: din kostnad = " + QString::number(cost) + " (borde vara " + QString::number(trueCost)+")";

        QMessageBox::information(this,"Ragnars Test", str);
        return false;
    }
    return true;
}

void MainWindow::on_actionRagnarsTest_triggered()
{

    Graph graph = graphWith5Nodes();

    bool ok = ragnarsTest(graph, 0,1, 3);


    if (ok) {
        graph = readGraph(":/texter/usaxy.txt", ":/texter/usalinks.txt" );
        ok = ragnarsTest(graph, 100,80000, 1596.29);
    }

    if (ok)
         QMessageBox::information( this, "Ragnars Test", "Ragnars test lyckades!");
    else QMessageBox::critical(this, "Ragnars Test", "Testen misslyckades!" );
}


void MainWindow::newGraphSelected()
{
    ui->centralWidget->clear();
    QString nameOfStudent = QString::fromUtf8(nameOfStudent1());
    if (nameOfStudent==QString("Homer Simpson")){
        QMessageBox::warning(this,"Felaktigt namn", "nameOfStudent1() == \"Homer Simpson\"");
    }

}


void MainWindow::on_actionAstar_triggered()
{
    bool &isAStar = ui->centralWidget->_isAStar;
    isAStar = !isAStar;

    ui->actionAstar->setChecked(isAStar);


}

void MainWindow::readImages(){
    qDebug() << "reading images.";

    _image = QImage(":/bilder/lenna.bmp");
    _diffImage = QImage(":/bilder/lenna.bmp");

    for (int y=1;y<_image.height()-1; y+=1)
        for (int x=1; x<_image.width()-1; x+=1){
            int g0 = QColor( _image.pixel(x,y) ).green();
            int ge = QColor( _image.pixel(x+1,y) ).green();


            int e = abs(127 + g0-ge);
            if (e>255)
                e = 255;
            if (e<0)
                e = 0;
            _diffImage.setPixel(x,y,  e) ;

        }
    qDebug() << "images read.";
}


Ixnode MainWindow::ixnodeFromPixel(int x, int y){

    return _image.width() * y + x;

}

void MainWindow::setGraphFromImage(){
    Graph &theGraph = ui->centralWidget->_theGraph;

    int numberOfNodes = _image.width()*_image.height();

    theGraph = vector<Node>(numberOfNodes);


    for (int y=1;y<_image.height()-1; y+=1)
        for (int x=1; x<_image.width()-1; x+=1){
            int ixNode = ixnodeFromPixel(x,y);
            Node &node = theGraph[ ixNode ];
            node._point = QPoint(x,y);

            int ge = QColor( _image.pixel(x+1,y) ).green();
            int gw = QColor( _image.pixel(x-1,y) ).green();
            int gn = QColor( _image.pixel(x,y-1) ).green();
            int gs = QColor( _image.pixel(x,y+1) ).green();

            node._outputs.push_back( Arc(ixnodeFromPixel(x+1,y), true, 1.0/(1.0+abs(gn-gs))));
            node._outputs.push_back( Arc(ixnodeFromPixel(x-1,y), true, 1.0/(1.0+abs(gn-gs))));
            node._outputs.push_back( Arc(ixnodeFromPixel(x,y+1), true, 1.0/(1.0+abs(gw-ge))));
            node._outputs.push_back( Arc(ixnodeFromPixel(x,y-1), true, 1.0/(1.0+abs(gw-ge))));

        }
}


void MainWindow::on_actionLenna_triggered()
{
    newGraphSelected();

    readImages();
    setGraphFromImage();
    ui->centralWidget->setImage(&_image);
    ui->centralWidget->graphChanged();

}

void MainWindow::on_actionLenna_diff_triggered()
{
    newGraphSelected();

    readImages();
    setGraphFromImage();

    ui->centralWidget->setImage(&_diffImage);
    ui->centralWidget->graphChanged();
}
