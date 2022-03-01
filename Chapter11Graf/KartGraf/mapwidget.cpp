#include "mapwidget.h"

#include "student2shortestpath.h"
#include "student1drawgraph.h"

#include <QPaintEvent>
#include <QPainter>
#include <algorithm>
#include <math.h>

#include <QPixmap>


float distance(const QPoint& pt1, const QPoint& pt2){
    float dx = pt1.x()-pt2.x();
    float dy = pt1.y()-pt2.y();
    return sqrt( dx*dx + dy*dy );
}

MapWidget::MapWidget(QWidget *parent) : QWidget(parent)
{        
    _indexOfStartNode = -1;
    _indexOfEndNode   = -1;

    _pImage = nullptr;

    setMouseTracking(true);

}


void MapWidget::setImage(QImage *pImage){
    _pImage = pImage;

}

void MapWidget::drawPath(QPainter& painter)
{
    QPen penGap(QColor(255,0,0,255),2);
    QPen penNormal(QColor(0,0,255,255),2);

    Ixnode ixBefore = -1;
      for (Ixnode ix : _traceback){
        QPoint pt = _paintedScaledGraph[ix]._point;
        if (ixBefore!=-1){
            bool visible = true;
            for (Arc n : _paintedScaledGraph[ixBefore]._outputs)
                if (n.m_ixDestination==ix)
                    visible = n.m_isVisible;
            if (visible)
                painter.setPen( penNormal );
            else painter.setPen( penGap);

            painter.drawLine(_paintedScaledGraph[ixBefore]._point, pt);
        }
        ixBefore = ix;
    }
}


void MapWidget::drawKnowndistances(QPainter& painter){



    QColor pink(255,127,127,_pImage==nullptr ? 100 : 10);
    for (Knowndistance kn : _knownDistances){
        QPoint pt = _paintedScaledGraph[kn._ixNode]._point;
        painter.fillRect(pt.x()-2, pt.y()-2,5,5, pink);
    }

    QColor red(255,0,0,255); //pImage==nullptr ? 100 : 10);

    for (auto i : _countinprioqueFromNodeix){
        if (i.second>0){
            Ixnode ixNode = i.first;

            QPoint pt = _paintedScaledGraph[ixNode]._point;
            painter.fillRect(pt.x()-2, pt.y()-2,5,5, red);
           }
    }
}

float MapWidget::scaleThatMakesGraphFitWindow(){
    int maxX = 0;
    int maxY = 0;
    for (Node& node : _theGraph){
       maxX = std::max(maxX, node._point.x() );
       maxY = std::max(maxY, node._point.y() );
    }
    float scaleX = (float) size().width()/maxX;
    float scaleY = (float) size().height()/maxY;
    float scale = 0.9*std::min(scaleX, scaleY);
    return scale;
}

void MapWidget::knownDistanceToNode(Ixnode ixNode, float distance)
{
    _knownDistances.push_back( Knowndistance(ixNode, distance) );

}

void MapWidget::nodeWasPlacedInPriorityQueue(Ixnode ixNode)
{
    _countinprioqueFromNodeix[ixNode] += 1;
}

void MapWidget::nodeWasPoppedFromPriorityQueue(Ixnode ixNode)
{
    _countinprioqueFromNodeix[ixNode] -= 1;
    if (_countinprioqueFromNodeix[ixNode]==0)
        _countinprioqueFromNodeix.erase(ixNode);
}


void MapWidget::makePixmap(){

     _pixmap = QPixmap( size() );

     QPainter painter( &_pixmap );

     painter.fillRect( _pixmap.rect() , Qt::white );


     painter.setPen(QPen(Qt::gray,0));

     if (_pImage  == nullptr){
        float scale = scaleThatMakesGraphFitWindow();
        _paintedScaledGraph = _theGraph;
        for (Node& node : _paintedScaledGraph)
             node._point =  node._point*scale;
        studentsDrawGraph(painter,  _paintedScaledGraph );

     }
     else {
         float scaleY = (float)_pixmap.rect().height()/_pImage->height();
         float scaleX = (float)_pixmap.rect().width()/_pImage->width();
         _paintedScaledGraph = _theGraph;
         for (Node& node : _paintedScaledGraph){
              node._point = QPoint(node._point.x()*scaleX, node._point.y()*scaleY);
         }

         painter.drawImage(_pixmap.rect(), *_pImage);
     }

}

void MapWidget::graphChanged(){
    makePixmap();
    repaint();
}

void MapWidget::paintEvent(QPaintEvent *event){


  QPainter painter(this);

  painter.drawPixmap( this->rect(), _pixmap );

  drawKnowndistances(painter);
  drawPath(painter);

}


void MapWidget::mousePressEvent(QMouseEvent *event)
{


  if (_paintedScaledGraph.size()==0)
      _indexOfStartNode = -1;
  else _indexOfStartNode = indexOfNearestNode(event->pos());

}

void MapWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (_indexOfStartNode>=0){
        _indexOfEndNode = indexOfNearestNode(event->pos());
        _knownDistances.clear();
        _countinprioqueFromNodeix.clear();

        if (_isAStar)
             _traceback = shortestPathBetweenNodes2(_theGraph, _indexOfStartNode, _indexOfEndNode, this);
        else _traceback = shortestPathBetweenNodes(_theGraph, _indexOfStartNode, _indexOfEndNode, this);

        repaint();
    }
}

void MapWidget::mouseReleaseEvent(QMouseEvent *event)
{
     if (_paintedScaledGraph.size()==0)
         return;

    _indexOfEndNode = indexOfNearestNode(event->pos());
    _knownDistances.clear();
    _countinprioqueFromNodeix.clear();

    if (_isAStar)
         _traceback = shortestPathBetweenNodes2(_theGraph, _indexOfStartNode, _indexOfEndNode, this);
    else _traceback = shortestPathBetweenNodes(_theGraph, _indexOfStartNode, _indexOfEndNode, this);

    repaint();

    _indexOfStartNode = -1;
    //_indexOfEndNode   = -1;

}

void MapWidget::resizeEvent(QResizeEvent *event)
{
    makePixmap();
}

Ixnode MapWidget::indexOfNearestNode(const QPoint& pt){
    Ixnode indexOfNerest = 0;
    Ixnode minimumDistance = 100000.0;
    for (Ixnode ix=0; ix<_paintedScaledGraph.size(); ix+=1){
        float dist = distance(pt, _paintedScaledGraph[ix]._point);
        if (dist<minimumDistance){
            minimumDistance = dist;
            indexOfNerest = ix;
        }
    }
    return indexOfNerest;
}
