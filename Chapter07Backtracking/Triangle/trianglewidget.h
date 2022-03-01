#ifndef TRIANGLEWIDGET_H
#define TRIANGLEWIDGET_H

#include "state.h"
#include <set>
#include <QWidget>
#include <QColor>

#include <QRgb>

class TriangleWidget : public QWidget
{
    Q_OBJECT

    const int   _posIlligal = 15;

    const QColor _colorDiscFill   = QColor(0,162,255);
    const QColor _colorSelectedFil = QColor(0,80,200);

    const QColor _colorDiscBorder = QColor(0,118,186);
    const QColor _colorJumpFill   = QColor(241,255,167);
    const QColor _colorFinalBorder= QColor(255,147,0);
    const QColor _colorHoleBorder = QColor(200,200,200);


    int    _separation;
    int    _radius;
    float  _partOfAnimation = 0.0;

    State _state;
    int    _posSelected =  _posIlligal;
    std::set<int> _posOfDestinations;
    std::set<int> _posOfCouldDisappears;

    std::set<int> _posOfFinals;


    QPoint center(int pos);
    QRect  rectFromPos(int pos);
    QRect  rectFromAnimation(int posSrc, int posDest, float t);


    void calcMetrics();


    void select(int pos);

    bool isLegalPos(int pos) { return pos>=0 && pos<15; }
    void animate(Move move);



    void showContextMenu(QPoint point);

    void visualWait(int ms);



    int posContainingPoint(QPoint pt);
protected:
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

public:
    explicit TriangleWidget(QWidget *parent = nullptr);
    void reset();
    void resetToEasyState();


};

void hilightFinal(int pos);




#endif // TRIANGLEWIDGET_H
