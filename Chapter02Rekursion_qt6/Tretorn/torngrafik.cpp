#include "torngrafik.h"

#include <QPainter>
#include <QPaintEvent>

#include <algorithm>

#include <QPoint>
#include <QDebug>
#include <QApplication>
#include <QThread>
#include <assert.h>


Torngrafik::Torngrafik(QWidget *parent) : QWidget(parent), _pTowers(nullptr){

    setMouseTracking(true);

}

void Torngrafik::setTowers(Towers *pTowers)
{
    assert( _pTowers==nullptr );
    _pTowers = pTowers;    

    connect(pTowers, &Towers::discLifted, this, &Torngrafik::animateLifted);
    connect(pTowers, &Towers::discDropped, this, &Torngrafik::animateDropped );

}





void Torngrafik::setMetrics(){

    _height = rect().height();
    _width = rect().width();

    const int nbrDiscs = _pTowers->nbrDiscs();

    _heightOfDisk = _height/(nbrDiscs+2+1+2);
    _yTopOfBoard =  _height-2*_heightOfDisk;
    _yTopOfPin = _yTopOfBoard - _heightOfDisk*(1+nbrDiscs);

    _diameterOfLargestDisc = int(_width/3*0.9);
    _widthOfPin  = _diameterOfLargestDisc/20;

    _diameterOfSmallestDisc = 3*_widthOfPin;

    _xOfPin[0] = int(_width/6);
    _xOfPin[2] = int( _width - _xOfPin[0] );
    _xOfPin[1] = (_xOfPin[0]+_xOfPin[2])/2;

}


QRect Torngrafik::rectOfDiscSize(int size){ // size = 0..._nbrOfDiscs-1

    int diameter = _diameterOfSmallestDisc + size*(_diameterOfLargestDisc-_diameterOfSmallestDisc)/(_pTowers->nbrDiscs()-1);

    QRect rect(-diameter/2, -_heightOfDisk/2, diameter, _heightOfDisk);
    return rect;
}



void Torngrafik::drawTowers(QPainter& painter){


    painter.setBrush( Qt::black );
    for (int pin=0;pin<3;pin+=1){
        painter.drawRoundedRect(rectOfPin(pin), 5,5);
    }

    if (_pTowers->isLifted()){
        painter.setBrush( Qt::blue );
        for (int pin=0;pin<3;pin+=1)
            if (pin!=_pinSelectedSource)
                painter.drawRoundedRect(rectOfPin(pin), 5,5);
    }

    QRect rectOfBoard(0, _yTopOfBoard,  _width, _height-_yTopOfBoard);
    painter.setBrush( Qt::black );
    painter.drawRoundedRect(rectOfBoard, 5,5);

}



void Torngrafik::paintEvent(QPaintEvent *event)
{
    QPainter painter( this );
    painter.fillRect( event->rect(), Qt::white);

    setMetrics();

    drawTowers(painter);
    painter.setBrush( Qt::darkYellow );


    for (int pin=0;pin<3; pin+=1){
        const int nbrPosToPaint = _pTowers->nbrDiscsAtPin(pin) - (pin==_pinDontPaintLastDisc ? 1:0);

        for (int pos=0;pos<nbrPosToPaint; pos+=1){
            QRect rectDisc = rectOfPinAndPos(pin, pos);
            painter.drawRoundedRect(rectDisc, 5,5);
        }
    }

    if (_isMooving){
        QRect rectDisc = rectOfDiscSize(_sizeOfMooving).translated(_centerOfMoving);
        painter.drawRoundedRect(rectDisc,5,5);
    }
}



QPoint Torngrafik::centerOfPinAndPos(int pin, int pos){
    QPoint center(_xOfPin[pin], _yTopOfBoard - _heightOfDisk/2 - _heightOfDisk*pos);
    return center;
}

QRect Torngrafik::rectOfPinAndPos(int pin, int pos){
    int size = _pTowers->discsizeAtPinAndPos(pin, pos);
    QRect rect = rectOfDiscSize(size);
    QPoint center = centerOfPinAndPos(pin,pos);
    return rect.translated(center);

}

QRect Torngrafik::rectOfPin(int pin){
    QRect rectOfPinAtZero = QRect(-_widthOfPin/2, _yTopOfPin, _widthOfPin, _height-_yTopOfPin);
    return rectOfPinAtZero.translated(_xOfPin[pin],0);
}


void Torngrafik::animateLifted(int pinSource){

    _isMooving = true;
    _sizeOfMooving = _pTowers->discsizeLifted();

    int timeFrame = 20; // ms

    int distanceOneFrame = (_height+_width)*20/1000;
    if (_speed == 0) distanceOneFrame = (distanceOneFrame/4)+1;
    if (_speed == 1) distanceOneFrame = distanceOneFrame + 1;
    if (_speed == 2) distanceOneFrame = distanceOneFrame*10 + 1;

    int posSource = _pTowers->nbrDiscsAtPin(pinSource);

    QPoint c0 = centerOfPinAndPos(pinSource, posSource);
    QPoint c1 = QPoint(c0.x(),  _yTopOfPin -_heightOfDisk/2);

    _centerOfMoving = c0;
    while (_centerOfMoving.y() > c1.y()){
        _centerOfMoving.setY( _centerOfMoving.y()-distanceOneFrame );
        if (_centerOfMoving.y()<c1.y())
            _centerOfMoving = c1;
        update();
        QApplication::processEvents();
        QThread::msleep(timeFrame);
    }
     _centerOfMoving = c1;
     update();
     QApplication::processEvents();
}





void Torngrafik::animateDropped(int pinSource, int pinDestination){
    qDebug() << "animateDroped( "<< pinSource << ", " << pinDestination << " )";

    _pinDontPaintLastDisc = pinDestination;

    int timeFrame = 20; // ms

    int distanceOneFrame = (_height+_width)*20/1000;
    if (_speed == 0) distanceOneFrame = (distanceOneFrame/4)+1;
    if (_speed == 1) distanceOneFrame = distanceOneFrame + 1;
    if (_speed == 2) distanceOneFrame = distanceOneFrame*10 + 1;


    int posDestination = _pTowers->nbrDiscsAtPin(pinDestination)-1;


    QPoint c3 = centerOfPinAndPos(pinDestination, posDestination);
    QPoint c2 = QPoint( c3.x(), _centerOfMoving.y());

     if (_centerOfMoving.x()<c2.x()){
         while (_centerOfMoving.x()<c2.x()){
             _centerOfMoving += QPoint(distanceOneFrame,0);
             if (_centerOfMoving.x()>c2.x())
                 _centerOfMoving = c2;
             update();
             QApplication::processEvents();
             QThread::msleep(timeFrame);
         }
     }
     else
         if (_centerOfMoving.x()>c2.x()){
             while (_centerOfMoving.x()>c2.x()) {
                 _centerOfMoving -= QPoint(distanceOneFrame,0);
                 if (_centerOfMoving.x()<c2.x())
                     _centerOfMoving = c2;
                 update();
                 QApplication::processEvents();
                 QThread::msleep(timeFrame);
             }
         }

     _centerOfMoving = c2;
     int d = distanceOneFrame/2 + 1;
     while (_centerOfMoving.y()<c3.y()) {
         _centerOfMoving += QPoint(0,d);
         if (_centerOfMoving.y()>c3.y())
             _centerOfMoving = c3;
         d = d + 0.5*d;
         update();
         QApplication::processEvents();
         QThread::msleep(timeFrame);
     }
    _centerOfMoving = c3;
    _isMooving = false;
    _pinDontPaintLastDisc = -1;
    update();
}


int Torngrafik::pinOfTopdiscContainingPoint(QPoint pos){
    for (int pin=0;pin<3; pin+=1){
        int posOfTop = _pTowers->nbrDiscsAtPin(pin)-1;
        if (posOfTop>=0){
            QRect  rectTop = rectOfPinAndPos(pin, posOfTop);
            if (rectTop.contains(pos)){
                return pin;

            }
        }
    }
    return -1;
}


int Torngrafik::pinContainingPoint(QPoint pos){
    for (int pin=0; pin<3 ; pin+=1){
        if (rectOfPin(pin).contains(pos))
            return pin;
    }
    return -1;
}


void Torngrafik::mousePressEvent(QMouseEvent *event)
{
    if (!_pTowers->isLifted()){
        int pin = pinOfTopdiscContainingPoint(event->pos());
        if (pin>=0){
            _pinSelectedSource = pin;
            _pTowers->liftDisc(pin);
            unsetCursor();
            update();
        }
    }
    else {
       int pin = pinContainingPoint(event->pos());
       if (pin>=0){
           _pTowers->placeLiftedDisc(pin);
           update();
       }
    }
}

void Torngrafik::mouseMoveEvent(QMouseEvent *event)
{
    if (!_pTowers->isLifted()){
        int pin = pinOfTopdiscContainingPoint(event->pos());
        if (pin>=0){
            setCursor( Qt::PointingHandCursor );
            return;
        }
    }
    else {
        if (pinContainingPoint(event->pos())>=0){
            setCursor(Qt::PointingHandCursor);
            return;
        }

    }
    unsetCursor();
}


