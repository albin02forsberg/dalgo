#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include "graph.h"

#include "student2shortestpath.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, IVisualFeedback//MockUp
{
    Q_OBJECT

    float _distanceLastKnown =  0.0;

    QImage _image;
    QImage _diffImage;

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    virtual void knownDistanceToNode(Ixnode ixNode, float dist) override ;
    virtual void nodeWasPlacedInPriorityQueue(Ixnode ixNode) override;
    virtual void nodeWasPoppedFromPriorityQueue(Ixnode ixNode)override ;

private slots:
    void on_actionUSA_triggered();

    void on_actionRandom_A_triggered();

    void on_actionUSA_FLYG_triggered();

    void on_action5Noder_triggered();

    void on_actionRagnarsTest_triggered();

    void on_actionAstar_triggered();

    void on_actionLenna_triggered();

    void on_actionLenna_diff_triggered();

private:
    void newGraphSelected();

    Ui::MainWindow *ui;

    Graph readGraph(QString xyFilename, QString linksFilename);
    void  addPath(Graph &graph, Ixnode ix1, Ixnode ix2, float cost, bool visible=true);
    Graph graphWith5Nodes();
    Graph randomGraphWithGaps();
    float costOfPathInGraph(const std::vector<Ixnode> &backwardspath, const std::vector<Node> &graph);
    void  readImages();
    Ixnode ixnodeFromPixel(int x, int y);

    void  setGraphFromImage();
    bool  ragnarsTest(const Graph &graph, Ixnode ix1, Ixnode ix2, float trueCost);
};

#endif // MAINWINDOW_H
