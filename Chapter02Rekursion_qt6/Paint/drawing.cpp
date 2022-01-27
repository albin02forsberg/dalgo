#include "drawing.h"
#include <assert.h>

#include <QPaintEvent>
#include <QPainter>
#include <QPoint>
#include <algorithm>
#include "mainwindow.h"

#include "studentfill1.h"
#include "studentfill2.h"

#include <QThread>
#include <QApplication>
#include <QDebug>

#include <string>


const char* nameOfStudent1();
const char* nameOfStudent2();


using namespace std;

void Drawing::updateSizeVariables()
{
    _xOffset = 5;
    _yOffset = 5;

    _widthOfPixelrect = float(size().width() - 2*_xOffset)/drawingParent()->numberOfColumns();
    _heightOfPixelrect = float(size().height() -2*_yOffset)/drawingParent()->numberOfRows();

}

QRectF Drawing::qrectfFrom(int r, int k)
{
    QRectF rect(_xOffset+k*_widthOfPixelrect,_yOffset+r*_heightOfPixelrect, _widthOfPixelrect, _heightOfPixelrect);
    return rect;
}

QRect Drawing::rectLarger( QRectF rectf ){
    QRect rc( int(rectf.x()), int(rectf.y()), int(2+rectf.width()),int(2+rectf.height()));
    return rc;
}

void Drawing::paintEvent(QPaintEvent *event)
{
    updateSizeVariables();

    QPainter painter(this);
    painter.fillRect(event->rect(), Qt::white);

    QPoint topLeft = event->rect().topLeft();
    QPoint bottRight = event->rect().bottomRight();

    int rBegin = max(rFromY(topLeft.y()), 0);
    int rEnd = min(rFromY(bottRight.y())+1, drawingParent()->numberOfRows());
    int kBegin = max(kFromX(topLeft.x()), 0);
    int kEnd = min(kFromX(bottRight.x())+1, drawingParent()->numberOfColumns());
    painter.setPen(Qt::gray);

    for (int r=rBegin ; r<rEnd; r+=1)
        for (int k=kBegin ; k<kEnd ; k+=1){
            painter.setBrush(drawingParent()->pixel(r,k));
            painter.drawRect(qrectfFrom(r,k));
        }

}

void Drawing::mousePressEvent(QMouseEvent *event)
{
    int r = rFromY(event->pos().y());
    int k = kFromX(event->pos().x());

    if (drawingParent()->isInside(r,k)){
        if (drawingParent()->isPentool())
            drawingParent()->setPixel(r,k, drawingParent()->colorSelected());
        else if (drawingParent()->isFilltool()){
            assert( std::string("Homer Simpson") != nameOfStudent1() );
            recursiveFill(r,k, drawingParent(), drawingParent()->pixel(r,k), drawingParent()->colorSelected());
        }
        else if (drawingParent()->isFulltool())
            recursiveFull(r,k, drawingParent(), drawingParent()->pixel(r,k), drawingParent()->colorSelected());
        else if (drawingParent()->isFilltoolNonRecursiveStack()){
            assert( std::string("Homer Simpson") != nameOfStudent2() );
            nonRecursiveFillStack(r,k, drawingParent(), drawingParent()->pixel(r,k), drawingParent()->colorSelected());
        }
        else if (drawingParent()->isFilltoolNonRecursiveFifo()){
             assert( std::string("Homer Simpson") != nameOfStudent2() );
            nonRecursiveFillFifo(r,k, drawingParent(), drawingParent()->pixel(r,k), drawingParent()->colorSelected());
        }
    }
}

void Drawing::mouseMoveEvent(QMouseEvent *event)
{
    int r = rFromY(event->pos().y());
    int k = kFromX(event->pos().x());

    if (drawingParent()->isInside(r,k)){
        if (drawingParent()->isPentool())
            drawingParent()->setPixel(r,k, drawingParent()->colorSelected());

    }
}

Drawing::Drawing(QWidget *theParent) : QWidget(theParent)
{
  assert( dynamic_cast<IDrawingParent*>( theParent ) );

  //connect(parent(),&MainWindow::pixelChanged, this, &Drawing::pixelDidChange );


  connect(parent(),SIGNAL(pixelChanged(int,int)), this, SLOT(pixelDidChange(int,int)) );


}

void Drawing::pixelDidChange(int r, int k)
{
   update( rectLarger(qrectfFrom(r,k)) );
}
