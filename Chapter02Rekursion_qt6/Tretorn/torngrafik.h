#ifndef TORNGRAFIK_H
#define TORNGRAFIK_H

#include <QWidget>
#include <QRect>

#include <vector>
#include "towers.h"


class Torngrafik : public QWidget
{
    Q_OBJECT

    Towers *_pTowers;

    bool _isMooving = false;
    QPoint _centerOfMoving = QPoint(0,0);
    int _sizeOfMooving = 0;
    int _pinDontPaintLastDisc = -1;


    int _height;
    int _width;

    int _diameterOfLargestDisc;
    int _diameterOfSmallestDisc;
    int _widthOfPin;
    int _heightOfDisk;

    int _xOfPin[3];


    int _speed = 0;

    int _yTopOfBoard;
    int _yTopOfPin;


    int _pinSelectedSource;


    void setMetrics();
    QRect rectOfDiscSize(int size);


    void drawTowers(QPainter &painter);
    QPoint centerOfPinAndPos(int pin, int pos);
    QRect rectOfPinAndPos(int pin, int pos);
    int pinOfTopdiscContainingPoint(QPoint pos);
    QRect rectOfPin(int pin);
    int pinContainingPoint(QPoint pos);

public:
    explicit Torngrafik(QWidget *parent = nullptr);

    void setSpeed(int speed) { _speed = speed; }
    int getSpeed() { return _speed; }

    void setTowers(Towers* pTowers);

    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

signals:

public slots:

private slots:
    void animateLifted(int pinSource);
    void animateDropped(int pinSource, int pinDestination);
};

#endif // TORNGRAFIK_H
