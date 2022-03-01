#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include "graph.h"
#include "student2shortestpath.h"
#include <map>


class MapWidget : public QWidget, IVisualFeedback
{

    Q_OBJECT

    Ixnode _indexOfStartNode;
    Ixnode _indexOfEndNode;
    std::vector<Ixnode> _traceback;
    QPixmap _pixmap;
    struct Knowndistance{
        Ixnode _ixNode;
        float  _distance;
        Knowndistance(Ixnode ixNode, float distance) : _ixNode(ixNode), _distance(distance) {}
    };

    QImage *_pImage;

    std::vector<Knowndistance> _knownDistances;
    std::map<Ixnode,int>  _countinprioqueFromNodeix;


    Ixnode indexOfNearestNode(const QPoint &pt);

    void drawPath(QPainter &painter);
    
    void makePixmap();
    float scaleThatMakesGraphFitWindow();
    void drawKnowndistances(QPainter &painter);

public:

    bool _isAStar = false;

    void knownDistanceToNode(Ixnode ixNode, float distance) override;
    void nodeWasPlacedInPriorityQueue(Ixnode ixNode) override;
    void nodeWasPoppedFromPriorityQueue(Ixnode ixNode) override;


    std::vector<Node> _theGraph;
    std::vector<Node> _paintedScaledGraph;
    void clear(){ _traceback.clear(); _knownDistances.clear(); }

    explicit MapWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

    void graphChanged();

    void setImage(QImage *pImage);
signals:

public slots:
};

#endif // MAPWIDGET_H
