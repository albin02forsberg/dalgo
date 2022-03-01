// copyright (c) Ragnar Nohre

#include "mazewidget.h"

#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <QMenu>
#include <QApplication>
#include <QThread>
#include <QMessageBox>

#include "studentLabyrint1.h"
#include "studentLabyrint2.h"

MazeWidget::MazeWidget(QWidget *parent) : QWidget( parent )
{
    initializeMazeThatFitsWindow(false);


    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showContextMenu(const QPoint &)));

    connect(&_mazeModel, &MazeModel::mazeCellChanged, this, &MazeWidget::mazeWasUpdated);
}

void MazeWidget::callStudentsSearch(bool recursive)
{
    _mazeModel.resetSearchData();
    update();

    RK rk = _mazeModel._rkStart;
    bool found = recursive ? ::didIndicatePathToGoal(&_mazeModel, rk.m_r, rk.m_k)
                           : ::foundShortestPathToGoalFIFO(&_mazeModel, rk.m_r, rk.m_k);
    if (!found)
        QMessageBox::information(this, "Sökresultat", "Målet hittades ej!");

}


void MazeWidget::mazeWasUpdated(int r, int k){

    QRectF rcf = rcFromRK(RK(r,k));

    QRect rc( rcf.left(), rcf.top(), rcf.width(), rcf.height());

    update(rc);
    visualWait(_durationOfDelay);
}


void MazeWidget::visualWait(int milliseconds){
    if (milliseconds>0){
        QApplication::processEvents();
        QThread::msleep(milliseconds);
    }
}



void MazeWidget::setDimensions()
{
    _heightOfCell = float(this->size().height())/(_mazeModel.sizeR());
    _widthOfCell  = float(this->size().width())/(_mazeModel.sizeK());
}

RK MazeWidget::rkFromPoint(QPoint pt)
{
    return { int(pt.y()/_heightOfCell), int(pt.x()/_widthOfCell) };
}

QRectF MazeWidget::rcFromRK(RK rk){
    return QRectF(rk.m_k*_widthOfCell, rk.m_r*_heightOfCell, _widthOfCell, _heightOfCell);
}



void MazeWidget::paintEvent(QPaintEvent *event)
{
    setDimensions();

    QPainter painter(this);
    painter.fillRect(event->rect(), Qt::darkGray);

    float d = std::min(_heightOfCell, _widthOfCell)/4;

    RK rkTopLeft = rkFromPoint(event->rect().topLeft());
    RK rkBottRight = rkFromPoint(event->rect().bottomRight());


    painter.setBrush(Qt::white);
    painter.setPen(Qt::NoPen);
    for (int r = rkTopLeft.m_r ; r<=rkBottRight.m_r ; r+=1)
        for (int k = rkTopLeft.m_k ; k<=rkBottRight.m_k ; k+=1){
            if (_mazeModel.isInside(r,k) &&  !_mazeModel.isWall(r,k)){
                QRectF rc = rcFromRK( {r,k} );
                rc.adjust(-d,-d,d,d);
                painter.drawRoundedRect( rc, d , d);
            }
        }
    for (int r = rkTopLeft.m_r ; r<=rkBottRight.m_r ; r+=1)
        for (int k = rkTopLeft.m_k ; k<=rkBottRight.m_k ; k+=1){
            if (_mazeModel.isInside(r,k) && !_mazeModel.isWall(r,k)){
                if (_mazeModel.isRed(r,k)){
                    painter.setBrush(QColor(255,100,100));
                    QRectF rc = rcFromRK( {r,k} );
                    painter.drawRoundedRect( rc, d , d);
                }
                if (_mazeModel.hasStone(r,k)){
                    painter.setBrush(QColor(0,128,0));
                    QRectF rc = rcFromRK( {r,k} );
                    rc.adjust(d,d,-d,-d);
                    painter.drawEllipse(rc);
                }
            }

        }


    painter.setBrush(Qt::red);
    painter.drawEllipse(rcFromRK(  _mazeModel._rkStart ));
    painter.setBrush(Qt::NoBrush);
    painter.setPen(Qt::red);

    painter.drawEllipse(rcFromRK(  _mazeModel._rkGoal ));

}





void MazeWidget::initializeMazeThatFitsWindow(bool multiPath)
{
    int r = this->size().height()/30;
    int k = this->size().width()/30;
    initializeMaze(r,k, multiPath);
}


void MazeWidget::initializeMaze(int r, int k, bool multiPath)
{
    _mazeModel.constructMaze(r,k, multiPath );
    update();
}


void MazeWidget::showContextMenu(const QPoint &point){

    RK rk = rkFromPoint(point);
    if (_mazeModel.isInside(rk.m_r, rk.m_k) && !_mazeModel.isWall(rk.m_r, rk.m_k)){
        QMenu menu;

        QAction *actionStart = menu.addAction("set Start" );
        QAction *actionGoal  = menu.addAction("set Goal" );
        QAction *actionSwap  = menu.addAction("swap Start/Goal" );


        QPoint ptOfMenu = mapToGlobal( point );
        QAction *selected = menu.exec( ptOfMenu );
        if (selected==actionStart)
            _mazeModel._rkStart = rk;
        if (selected==actionGoal)
             _mazeModel._rkGoal = rk;
        if (selected==actionSwap)
            std::swap( _mazeModel._rkStart,  _mazeModel._rkGoal);
        update();
    }


}
