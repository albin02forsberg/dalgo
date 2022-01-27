#ifndef DRAWING_H
#define DRAWING_H

#include <QWidget>
#include "idrawingparent.h"

class Drawing : public QWidget
{
    Q_OBJECT

    int _xOffset = 0;
    int _yOffset = 0;
    float _widthOfPixelrect = 10;
    float _heightOfPixelrect = 10;

    void  updateSizeVariables();
    IDrawingParent *_drawingParent = nullptr;

    IDrawingParent* drawingParent()  { return (IDrawingParent*) _drawingParent; }
    QRect rectLarger(QRectF rectf);
protected:
    QRectF qrectfFrom(int r, int k);
    int   rFromY(int y)  { return (y-_yOffset)/_heightOfPixelrect; }
    int   kFromX(int x)  { return (x-_xOffset)/_widthOfPixelrect; }

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;


public:
    explicit Drawing(QWidget *theparent = nullptr);

    void setDrawingParent(IDrawingParent* p) { _drawingParent = p;}

signals:

public slots:
    void pixelDidChange(int r, int k);

};

#endif // DRAWING_H
