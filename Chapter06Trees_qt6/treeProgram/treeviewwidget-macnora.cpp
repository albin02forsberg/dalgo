// TreeViewWidget, by Ragnar Nohre (c) 2017-2018

#include "treeviewwidget.h"
#include "assert.h"

#include <QtGui>

#include <vector>
/***/
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>

#include <QRect>
#include <QPoint>
#include <QThread>
#include <QApplication>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
/***/
#include <random>

#include <algorithm>

#include <math.h>

#include "students.h"



using namespace std;

TreeViewWidget *TreeViewWidget::_sTheOne = nullptr;


void TreeViewWidget::visualWait(int milliseconds){
    if (milliseconds>0){
        update();
        QApplication::processEvents();
        QThread::msleep(milliseconds);
    }
}

Node *TreeViewWidget::subtreeWorstcaseAVL(int height){
    if (height<0)
        return nullptr;

    Node *pSub = new Node(0);
    pSub->_pLeft = subtreeWorstcaseAVL(height-2);
    pSub->_pRight = subtreeWorstcaseAVL(height-1);
    return pSub;
}

Node *TreeViewWidget::subtreeRandomAVL(int height, string path, const string &failpath){
    if (height<0)
        return nullptr;

    int h1 = height-1;
    int h2 = (path==failpath && failpath!="" ? h1-2 : h1 - rand() % 2);
    if (rand() % 2)
        std::swap( h1, h2 );
    Node *pSub = new Node(0);
    pSub->_pLeft = subtreeRandomAVL(h1,  path+"0", failpath);
    pSub->_pRight = subtreeRandomAVL(h2, path+"1", failpath);
    return pSub;
}



Node *TreeViewWidget::subtreeFromRandom(int depth)
{
    static float probabilityToCreate[] = {1.0, 1.0, 1.0, 1.0/4,  0.6, 0.6, 0.6, 0.6, 0.6,  0.0 };

    float f =  float(rand()) / RAND_MAX;

    Node *pSub = nullptr;
    if (f< probabilityToCreate[depth]){
        pSub = new Node(0);
        pSub->_pLeft =  subtreeFromRandom(depth+1);
        pSub->_pRight = subtreeFromRandom(depth+1);
    }
    return pSub;
}


int TreeViewWidget::size(Node* pRoot){
    if (pRoot==nullptr)
        return 0;
    return size(pRoot->_pLeft) + 1 + size(pRoot->_pRight);
}


int TreeViewWidget::hOfTree(Node* pRoot){
    if (pRoot==nullptr)
        return -1;
    return 1+std::max(hOfTree(pRoot->_pLeft), hOfTree(pRoot->_pRight));
}


void TreeViewWidget::addParentlocationToNewnodes(Node *pRoot, QPointF locationOfParent, std::map<Node*,QPointF> &locations){
    if (pRoot==nullptr)
        return;
    if (locations.find(pRoot)==locations.end())
        locations[pRoot] = locationOfParent;

    addParentlocationToNewnodes(pRoot->_pLeft,  locations[pRoot], (locations));
    addParentlocationToNewnodes(pRoot->_pRight, locations[pRoot], (locations));
}


void TreeViewWidget::setDesiredLocations(Node *pRoot, int depth, int& x, float dx, float dy, std::map<Node*,QPointF> &locationFromNode){
    if (pRoot==nullptr)
        return;
    setDesiredLocations(pRoot->_pLeft, depth+1, (x), dx,dy,  (locationFromNode) );
    locationFromNode[pRoot] = QPointF(x*dx, depth*dy);
    x += 1;
    setDesiredLocations(pRoot->_pRight, depth+1, (x), dx,dy, (locationFromNode));
}

void TreeViewWidget::setDesiredLocations(Node *pRoot, std::map<Node*,QPointF> &locationFromNode){
    if (pRoot==nullptr)
        return;
    int one = 1;
    int nbrNodes = size(pRoot);
    int h = hOfTree(pRoot);
    setDesiredLocations(pRoot,
                        1,
                        one,
                        1.0/(nbrNodes+2),
                        1.0/(h+2),
                        (locationFromNode));
}



int TreeViewWidget::nextkeyWhenDoAssignKeyvalues(Node *pSubtree, int firstValue){
    if (pSubtree==nullptr)
        return firstValue;

    int keyRoot = nextkeyWhenDoAssignKeyvalues(pSubtree->_pLeft, firstValue + 2+rand()%5);
    pSubtree->_key = keyRoot;
    int keyNext = nextkeyWhenDoAssignKeyvalues(pSubtree->_pRight, keyRoot+2+rand()%5);
    return keyNext;
}

void TreeViewWidget::destroySubtree(Node *pRoot)
{
    if (pRoot!=nullptr){
        destroySubtree(pRoot->_pLeft);
        destroySubtree(pRoot->_pRight);
        delete pRoot;
    }
}


TreeViewWidget::TreeViewWidget(QWidget *parent) : QWidget(parent)
{
    assert( _sTheOne==nullptr );
    _sTheOne = this;

    createRandomTree();
    setMouseTracking(true);


    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showContextMenu(const QPoint &)));

}

void TreeViewWidget::updateVisualTree()
{
    update();
}


void TreeViewWidget::flashNode(Node *pNode)
{
    _nodeFlashed = pNode;
    update();
    visualWait(_durationOfDelay);
    _nodeFlashed = nullptr;
    update();

}

bool TreeViewWidget::isTarget(Node *pNode)
{
    return pNode == _nodeThatIsTarget;
}

void TreeViewWidget::createRandomTree()
{

    if (_pRoot)
        destroySubtree(_pRoot);
    _pRoot = subtreeFromRandom(0);

    _locationFromNodeptr.clear();


    int keyFirst = 500-5*size(_pRoot)/2 + rand()%10 - 5;

    nextkeyWhenDoAssignKeyvalues(_pRoot, keyFirst);

    animateTheChange();

}


void TreeViewWidget::createWorstCaseAVL(int height)
{
    if (_pRoot)
        destroySubtree(_pRoot);
    _pRoot = subtreeWorstcaseAVL(height);

    int keyFirst = 500-5*size(_pRoot)/2 + rand()%10 - 5;

    nextkeyWhenDoAssignKeyvalues(_pRoot, keyFirst);

    animateTheChange();
}

void TreeViewWidget::createRandomAVL(int height)
{
    if (_pRoot)
        destroySubtree(_pRoot);
    _pRoot = subtreeRandomAVL(height, "", "");

    int keyFirst = 500-5*size(_pRoot)/2 + rand()%10 - 5;

    nextkeyWhenDoAssignKeyvalues(_pRoot, keyFirst);

    animateTheChange();
}

void TreeViewWidget::createRandomNotAVL(int height)
{
    if (_pRoot)
        destroySubtree(_pRoot);

    string pathToFail = "";
    int length = 1 + rand()%3;
    for (int i= 0; i< length ; i+=1)
        pathToFail = pathToFail + (rand() % 2 ? "0" : "1");

    _pRoot = subtreeRandomAVL(height , "", pathToFail );

    int height2 = 0;
    bool avl = isAVL(_pRoot, (&height2));
    while (avl){
        destroySubtree(_pRoot);
        subtreeRandomAVL(height , "", pathToFail );
        avl = isAVL(_pRoot, (&height2));
    }
    qDebug() << "isAVl returns " << avl << " and height2 " << height2;
    qDebug() << "pathToFail = " <<  QString::fromStdString( pathToFail );

    int keyFirst = 500-5*size(_pRoot)/2 + rand()%10 - 5;

    nextkeyWhenDoAssignKeyvalues(_pRoot, keyFirst);

    animateTheChange();
}

bool TreeViewWidget::isAVL(Node *pTree, int *pHeight){
    if (pTree==nullptr){
        *pHeight = -1;
        return true;
    }

    int heightLeft = 0;
    int heightRight = 0;
    bool ok = isAVL(pTree->_pLeft, (&heightLeft)) && isAVL(pTree->_pRight, (&heightRight));
    ok = ok && abs(heightLeft-heightRight)<=1;
    *pHeight = max(heightLeft, heightRight)+1;
    return ok;

}

void TreeViewWidget::createRandomSearchTree(int size)
{
    destroySubtree(_pRoot);
    _pRoot = nullptr;

    vector<int> keys(size);
    for (int i=0;i<size ; i+=1)
        keys[i] = i;
    std::random_device rd;
    std::mt19937 g(rd());
    shuffle(keys.begin(), keys.end() , g);

    auto oldDuration = _durationOfDelay;
    _durationOfDelay = 0;

    for (int i=0; i<size; i+=1)
        ::insertKeyToSearchtree(_pRoot, keys[i]);
    _locationFromNodeptr.clear();
    _durationOfDelay = oldDuration;
    animateTheChange();
    int size2 = antalNoder(_pRoot);
    float average = (float) sumOfDepth(_pRoot, 0)/size2;
    char str[100];
    sprintf(str, "Genomsnittligt djup är %.2f (antal noder %d)", average, size2);
    QMessageBox::information(this, "Information om trädet!", str);

}


int TreeViewWidget::sumOfDepth(Node *pRoot, int depthOfThisNode){
    if (pRoot==nullptr)
        return 0;
    return depthOfThisNode
            + sumOfDepth(pRoot->_pLeft, depthOfThisNode+1)
            + sumOfDepth(pRoot->_pRight, depthOfThisNode+1);
}
int TreeViewWidget::antalNoder(Node *pRoot){
    if (pRoot==nullptr)
        return 0;
    return 1 + antalNoder(pRoot->_pLeft)+ antalNoder(pRoot->_pRight);
}



void TreeViewWidget::paintEvent(QPaintEvent *event)
{
    addParentlocationToNewnodes(_pRoot,QPointF(0.5,0), (_locationFromNodeptr));
    QPainter painter(this);

    painter.fillRect(event->rect(), Qt::white);

    drawArcs(painter, QPointF(0.5, 0), _pRoot);
    fillNodesInSubtree(painter, _pRoot);
    drawBorders(painter);

    if (_pNodeUnderMouse){
        QFont font = painter.font();
        font.setPixelSize(24);
        painter.setFont(font);

        QString str = "key = " + QString::number(_pNodeUnderMouse->_key) + "    ";

        painter.drawText(10,30, str );

    }

}

void TreeViewWidget::mouseMoveEvent(QMouseEvent *event)
{
    Node *pNode = nodeFromPos(event->pos());
    if (pNode!=_pNodeUnderMouse){
        _pNodeUnderMouse = pNode;
        update();
    }


}

Node* TreeViewWidget::nodeFromPos( QPoint pos){
    float distMin = 10000;
    Node* pNodeNear = nullptr;
    for (auto ite : _locationFromNodeptr){
         QPoint pt = ptFromLocation(ite.second);
         float d = distance(pos, pt);
         if (d<distMin){
             distMin = d;
             pNodeNear = ite.first;
         }
    }
    if (pNodeNear){
        if (rectFromNode(pNodeNear).contains(pos) || distMin < 10){
            return pNodeNear;
        }
    }
    return nullptr;
}



void TreeViewWidget::animateTheChange(){
    std::map<Node*, QPointF>  oldLocations = _locationFromNodeptr;
    std::map<Node*, QPointF>  newLocations = _locationFromNodeptr;

    addParentlocationToNewnodes(_pRoot, QPointF(0.5,0), (oldLocations));
    setDesiredLocations(_pRoot, (newLocations) );

    for (float f=0.1; f<1; f+=0.1){
        for (auto ite : newLocations){
            Node *pNode = ite.first;
            QPointF locOld = oldLocations[pNode];
            QPointF locNew = newLocations[pNode];
            QPointF locCurrent( locOld.x()*(1-f)+locNew.x()*f, locOld.y()*(1-f)+locNew.y()*f);
            _locationFromNodeptr[pNode] = locCurrent;
        }
        update();
        QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
        QThread::msleep(50);


    }
    _locationFromNodeptr = newLocations;
    update();

}

bool TreeViewWidget::readTree(FILE *fp)
{
    destroySubtree(_pRoot);
    _pRoot = ::readTree(fp);
    _locationFromNodeptr.clear();
    animateTheChange();
    update();
    return true;
}

bool TreeViewWidget::saveTree(FILE *fp)
{
    ::saveTree(fp, _pRoot);
    update();
    return true;
}

void TreeViewWidget::nodeAdded(Node *pNode)
{
    assert( pNode );
    _nodesExisting.insert(pNode);
    assert( _locationFromNodeptr.find(pNode) == _locationFromNodeptr.end());

}

void TreeViewWidget::nodeDeleted(Node *pNode){
    assert(pNode);
    _nodesExisting.erase(pNode);
    _nodesThatAreRed.erase(pNode);
    _locationFromNodeptr.erase(pNode);
    if (pNode==_nodeFlashed)
        _nodeFlashed = nullptr;
    if (pNode==_pNodeUnderMouse)
        _pNodeUnderMouse = nullptr;
}

void TreeViewWidget::makeRed(Node *pNode){
    _nodesThatAreRed.insert( pNode );
    update();
    visualWait(_durationOfDelay);

}

void TreeViewWidget::insertKeyToSearchtree(int key){

    ::insertKeyToSearchtree(_pRoot, key);

    animateTheChange();
}

void TreeViewWidget::removeKeyFromSearchtree(int key)
{
    ::removeKeyFromSearchtree(_pRoot, key);

    animateTheChange();
}

void TreeViewWidget::insertMultipleRandomKeysToSearchtree(int numberOfKeysToInsert)
{
    for (int i=0;i<numberOfKeysToInsert; i+=1){
        ::insertKeyToSearchtree(_pRoot, rand() % 1000);
    }

    animateTheChange();
}
void TreeViewWidget::removeMultipleRandomKeysFromSearchtree(int numberOfKeysToInsert)
{
    for (int i=0;i<numberOfKeysToInsert; i+=1){
        ::removeKeyFromSearchtree(_pRoot, rand() % 1000);
    }

    animateTheChange();
}


void TreeViewWidget::insertRemoveRandomkeys(int nbrIterations)
{
    for (int i=0;i<nbrIterations; i+=1){
        ::insertKeyToSearchtree(_pRoot, rand() % 1000);
        ::removeKeyFromSearchtree(_pRoot, rand() % 1000);
    }

    animateTheChange();
}

void TreeViewWidget::showContextMenu(const QPoint &point)
{
    QMenu menu;
    Node *pNode = nodeFromPos(point);
    QAction *actionDelete = nullptr;

    QAction *actionInsertMinus1 = nullptr;
    QAction *actionInsert       = nullptr;
    QAction *actionInsertPlus1  = nullptr;

    QAction *actionContainsMinus1 = nullptr;
    QAction *actionContains        = nullptr;
    QAction *actionContainsPlus1   = nullptr;
    QAction *actionFindTarget      = nullptr;
    int theKey = 0;

    if (pNode){
        theKey = pNode->_key;

        actionDelete = menu.addAction("delete " + QString::number(theKey));
        menu.addSeparator();
        actionInsertMinus1 = menu.addAction("insert " + QString::number(theKey-1) + " (-1)");
        actionInsert       = menu.addAction("insert " + QString::number(theKey));
        actionInsertPlus1  = menu.addAction("insert " + QString::number(theKey+1) + " (+1)");
        menu.addSeparator();
        actionContainsMinus1 = menu.addAction("contains " + QString::number(theKey-1) + "? (-1)");
        actionContains       = menu.addAction("contains " + QString::number(theKey) + "?");
        actionContainsPlus1  = menu.addAction("contains " + QString::number(theKey+1)+ "? (+1)");
        menu.addSeparator();
        actionFindTarget     = menu.addAction("didIndicatePathToTarget");

    }
    QPoint ptOfMenu = mapToGlobal(point);
    QAction *selected = menu.exec(ptOfMenu);
    if (selected!=nullptr){
        if (selected==actionDelete)
            removeKeyFromSearchtree(theKey);
        else if (selected==actionInsertMinus1)
            insertKeyToSearchtree(theKey-1);
        else if (selected==actionInsert)
            insertKeyToSearchtree(theKey);
        else if (selected==actionInsertPlus1)
            insertKeyToSearchtree(theKey+1);

        else if (selected==actionContains || selected==actionContainsMinus1 || selected==actionContainsPlus1){
            int keySearch = selected==actionContains ? theKey
                                                     : selected==actionContainsMinus1 ? theKey-1
                                                                                      : theKey+1;
            bool found = ::contains(_pRoot, keySearch);
            QString title = QString("Anropade contains(%1);").arg( keySearch );
            QString booltxt = found == true ?  "true": found==false? "false" : "????";
            QString result = QString(" Resultat: %1").arg(booltxt);

            QMessageBox::information(this, title, title+result);
        }
        else if (selected==actionFindTarget){
            _nodeThatIsTarget  = pNode;
            ::didIndicatePathToTarget(_pRoot);

            visualWait(1500);
            _nodesThatAreRed.clear();
            update();
            _nodeThatIsTarget = nullptr;
        }

    }
}




float TreeViewWidget::distance(QPoint pt1, QPoint pt2){
    float dx = pt1.x()-pt2.x();
    float dy = pt1.y()-pt2.y();
    return sqrt( dx*dx+dy*dy);
}


void TreeViewWidget::drawArcs(QPainter &painter, QPointF locationOfParent, Node* pSubtree ){
    if (pSubtree==nullptr){
        return;
    }

    QPointF location = _locationFromNodeptr[pSubtree];
    drawArc(painter, locationOfParent, location);
    drawArcs(painter, location, pSubtree->_pLeft);
    drawArcs(painter, location, pSubtree->_pRight);
}


void TreeViewWidget::drawArc(QPainter &painter, QPointF ptf1, QPointF ptf2){

    painter.setPen(QPen(Qt::black,0, Qt::SolidLine));
    painter.drawLine(ptFromLocation(ptf1) , ptFromLocation(ptf2));
}

QPoint TreeViewWidget::ptFromLocation(QPointF ptf){
    QSize size = this->rect().size();
    return QPoint( ptf.x()*size.width(), ptf.y()*size.height());
}


void TreeViewWidget::fillNodesInSubtree(QPainter &painter, Node* pNode){
    if (pNode==nullptr)
        return;

    fillNode(painter, pNode);
    fillNodesInSubtree(painter, pNode->_pLeft);
    fillNodesInSubtree(painter, pNode->_pRight);
}

void TreeViewWidget::drawBorders(QPainter &painter){
    for (auto ite  : _locationFromNodeptr){
        drawBorderOfNode(painter, ite.first);
    }
}


void TreeViewWidget::fillNode(QPainter &painter, Node* pNode){
    painter.setPen(Qt::NoPen);

    QRect rc = rectFromNode(pNode);


    if (pNode==_nodeFlashed){
        QRect rcLarger = rc.adjusted(-5,-5,5,5);
        painter.setBrush(Qt::black);
        painter.drawEllipse(rcLarger);
    }
    if (_nodesThatAreRed.find(pNode)!=_nodesThatAreRed.end() ){
        QRect rcLarger = rc.adjusted(-5,-5,5,5);
        painter.setBrush(Qt::red);
        painter.drawEllipse(rcLarger);
    }


    if (pNode==_nodeFlashed)
         painter.setBrush(Qt::white);
    else painter.setBrush(colorFromKey(pNode->_key));


    painter.drawEllipse(rc);

    painter.setPen(Qt::black);

    int a = 0;
    rc.adjust(a,a,-a,-a);

    QFont font = painter.font();
    font.setPixelSize(rc.width()/2);

    painter.setFont(font);
    if (_shouldShowKey)
        painter.drawText(rc, Qt::AlignCenter, QString::number(pNode->_key));


    // TODO draw key

}

void TreeViewWidget::drawBorderOfNode(QPainter &painter, Node* pNode){
    painter.setPen( QPen(Qt::black, 1, Qt::SolidLine));
    painter.setBrush( Qt::NoBrush );

    painter.drawEllipse( rectFromNode(pNode) );
}


QRect TreeViewWidget::rectFromNode(Node* pNode) {
    int z = this->rect().width()/50;
    QRect rc(-z/2,-z/2,z,z);
    QPoint pt = ptFromLocation( _locationFromNodeptr[pNode]);
    return  rc.translated(pt);
}




QColor TreeViewWidget::colorFromKey(int key){

    static QColor color[] = { QColor(255,128,128), QColor(128,255,128), QColor(128,128,255),
                            QColor(255,255,128), QColor(255,128,255), QColor(128,255,255) };

    if (!_shouldShowColor)
        return _shouldShowKey ? Qt::white :  Qt::lightGray;

    static const int numColors = sizeof(color)/sizeof(color[0]);
    return color[key % numColors];
}


