#ifndef MAZEWIDGET_H
#define MAZEWIDGET_H

#include <QWidget>

#include "mazemodel.h"

class MazeWidget : public QWidget
{

    Q_OBJECT;



    MazeModel _mazeModel;



    void initializeMaze(int r, int k, bool multiPath);


    float _widthOfCell;
    float _heightOfCell;

    void   setDimensions();
    RK     rkFromPoint(QPoint pt);
    QRectF rcFromRK(RK rk);
    int    _durationOfDelay = 0;
    void visualWait(int milliseconds);
public:
    MazeWidget(QWidget *parent = nullptr);

    void callStudentsSearch(bool recursive);

    void setDurationOfDelay(int delay) {  _durationOfDelay = delay; }


    void paintEvent(QPaintEvent *event) override;

    void initializeMazeThatFitsWindow(bool multiPath);

private slots:
    void showContextMenu(const QPoint &);
    void mazeWasUpdated(int r, int k);
};

#endif // MAZEWIDGET_H
