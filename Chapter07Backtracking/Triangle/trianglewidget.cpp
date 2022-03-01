// copyright (c) Ragnar Nohre

#include "trianglewidget.h"
#include "studentsTriangle.h"

#include <QPainter>
#include <QMouseEvent>
#include <QThread>
#include <QApplication>
#include <QMenu>

#include <algorithm>

using namespace std;



/******************************************************************
positionsnummer enligt nedanstående:

                  0
                1   2
              3   4   5
            6   7   8   9
          10  11  12  13 14

 ******************************************************************/


bool contains(std::set<int> &theSet, int theElement){
    return theSet.find(theElement)!=theSet.end();
}



TriangleWidget::TriangleWidget(QWidget *parent) : QWidget(parent)
{
    _separation = 30;

    _posSelected = _posIlligal;

    setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, &TriangleWidget::customContextMenuRequested,
            this, &TriangleWidget::showContextMenu );

    setMouseTracking(true);
    resetToEasyState();


}



void TriangleWidget::calcMetrics()
{
  int sq = min(size().height()-25, size().width());
  _separation = sq/5;
  _radius     = _separation/2;
}// calcMetrics


void TriangleWidget::visualWait(int ms)
{
    QApplication::processEvents();
    QThread::msleep(ms);
}


QPoint TriangleWidget::center(int pos)
{
  static int ix0[] = { 0, 1, 3, 6, 10 };
  int r=4;
  for (r=4 ; ix0[r]>pos ; r--)
    ;
  int k = pos - ix0[r];

  float d = 1.1547f;

  int y = _separation/2  + 10 + _separation*r;
  int x = 3*_separation +  (int) ((-0.5*d*r + k*d)*_separation + 0.5);

  return QPoint(x,y);
}// center


QRect TriangleWidget::rectFromPos(int pos){
    return QRect( -_radius, -_radius, _radius*2, _radius*2 ).translated( center(pos) );
}

QRect TriangleWidget::rectFromAnimation(int posSrc, int posDest, float t)
{
    QPoint ptSrc = center(posSrc);
    QPoint ptDest = center(posDest);

    QPoint pt = (1-t)*ptSrc + t*ptDest;

    return QRect( -_radius, -_radius, _radius*2, _radius*2 ).translated( pt );


}





void TriangleWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    calcMetrics();


    painter.fillRect(event->rect(), Qt::white);

    painter.setBrush(Qt::NoBrush);
    painter.setPen(QPen(_colorHoleBorder,1));

    for (int pos=0 ; pos<15 ; ++pos)
        painter.drawEllipse( rectFromPos(pos) );

    painter.setBrush(_colorJumpFill);
    for (int pos=0 ; pos<15 ; ++pos)
        if (contains(_posOfDestinations, pos))
            painter.drawEllipse( rectFromPos(pos) );

    float a = _radius/6;

    painter.setBrush(_colorDiscFill);
    painter.setPen(QPen(_colorDiscBorder,1));
    for (int pos=0 ; pos<15 ; ++pos)
        if (_state.isOccupied(pos)){
            if (contains(_posOfCouldDisappears, pos))
                painter.drawEllipse( rectFromPos(pos).adjusted(a,a,-a,-a) );
            else if (pos!=_posSelected)
                painter.drawEllipse( rectFromPos(pos) );
        }

    painter.setBrush(Qt::NoBrush);
    painter.setPen(QPen(_colorFinalBorder,3));
    for (int pos=0 ; pos<15 ; ++pos)
        if (contains(_posOfFinals, pos))
            painter.drawEllipse( rectFromPos(pos));
    painter.setPen(QPen(_colorDiscBorder,1));


    float d = 0;
    if (_posSelected!=_posIlligal){
        painter.setBrush(_colorSelectedFil);
        if (_partOfAnimation==0)
            painter.drawEllipse( rectFromPos(_posSelected).adjusted(-d,-d,d,d) );
        else {
            QRect rc = rectFromAnimation(_posSelected, *_posOfDestinations.begin(), _partOfAnimation);
            painter.drawEllipse( rc.adjusted(-d,-d,d,d) );

        }
    }
}

void TriangleWidget::mousePressEvent(QMouseEvent *event)
{
    int posPressed = posContainingPoint(event->pos());

    if (_state.isOccupied(posPressed)){
        if (_posSelected==posPressed)
            select(_posIlligal);
        else select(posPressed);
    }
    else if (contains(_posOfDestinations, posPressed)){
            mouseMoveEvent(event);
        }
   else select(_posIlligal);

   update();
}


void TriangleWidget::mouseMoveEvent(QMouseEvent *event)
{
    const int posHover = posContainingPoint(event->pos());
    if (_state.isOccupied(posHover) || contains(_posOfDestinations, posHover))
         setCursor(Qt::PointingHandCursor);
    else setCursor(Qt::ArrowCursor);

}

void TriangleWidget::mouseReleaseEvent(QMouseEvent *event)
{

    vector<Move> moves = _state.legalMoves( _posSelected );
    for (Move move : moves){
        int pos2 = posdestinationFromPosAndDirection(_posSelected, move.m_direction );
        QRect rc = rectFromPos(pos2);
        if ( rc.contains(event->pos()) )
          { animate( move );       
            select(_posIlligal);
            update();
            break;
          }

      }

    update();
}


int TriangleWidget::posContainingPoint(QPoint pt){

    for (int pos=0 ; pos<15 ; pos+=1)
        { QRect rc = rectFromPos(pos);
          if (rc.contains(pt)){
              return pos;
          }
        }
    return 15;
}




void TriangleWidget::select(int pos)
{
    _posSelected = pos;

    _posOfDestinations.clear();
    _posOfCouldDisappears.clear();

    vector<Move> moves = _state.legalMoves(_posSelected);
    for (Move move : moves){
        int posNext =  posdestinationFromPosAndDirection( move.m_pos, move.m_direction);
        _posOfDestinations.insert(posNext);
        int posDisapear = posNeighbour(move.m_pos, move.m_direction);
        _posOfCouldDisappears.insert(posDisapear);
    }
}


void TriangleWidget::animate(Move move){

  _posSelected = move.m_pos;
  int posDestination = posdestinationFromPosAndDirection(move.m_pos, move.m_direction);
  int posDisapear    = posNeighbour(move.m_pos, move.m_direction);

  _posOfCouldDisappears.clear();
  _posOfDestinations.clear();
  _posOfDestinations.insert(posDestination);
  _posOfCouldDisappears.insert(posDisapear);

  for (_partOfAnimation = 0; _partOfAnimation<1; _partOfAnimation += 0.05){
      update();
      visualWait(20);
  }
  _partOfAnimation = 0;
  _state = _state.nextState(move);
  _posSelected = _posIlligal;
  _posOfFinals = setOfPossibleFinalPositions(_state);
  update();

}


void TriangleWidget::resetToEasyState()
{

   // 10  11  12  13 14

    for (int pos=0; pos<15; ++pos)
        _state.clearPos(pos);
    _state.setPos(10);
    _state.setPos(11);
    _state.setPos(13);

    _posOfFinals = setOfPossibleFinalPositions(_state);
    update();
}


void TriangleWidget::reset()
{
    for (int pos=0; pos<15; ++pos)
        _state.setPos(pos);
    int numberToClear = 1 + rand()%3;
    for (int i=0; i<numberToClear; i+=1)
        _state.clearPos(rand() % 15);
    _posOfFinals = setOfPossibleFinalPositions(_state);
    update();
}





void TriangleWidget::showContextMenu(QPoint point)
{
    int posOfFinal = posContainingPoint(point);
    if (posOfFinal==_posIlligal)
        return;

    QMenu menu;
    QAction *actionFinal = menu.addAction("Place final disc here!");


    QPoint ptOfMenu = mapToGlobal( point );
    QAction *selected = menu.exec( ptOfMenu );
    if (selected==actionFinal){
       vector<Move> moves = movesInPathToFinal(_state, posOfFinal);
       for (Move move : moves){
           animate(move);
           repaint();
           visualWait(150);
       }
    }


}




