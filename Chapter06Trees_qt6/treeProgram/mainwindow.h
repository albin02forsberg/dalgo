// Copyright (c) by Ragnar Nohre

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include <QAction>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QActionGroup *_speedGroup = nullptr;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_actionrandom_tree_triggered();
    void on_actioninsert_triggered();
    void on_actiondelete_triggered();
    void on_insert100Random_triggered();
    void on_remove100Random_triggered();

    void on_insertRemove1000RandomKeys_triggered();

    void speedDidChange(QAction* action);
    void on_actionPreOrder_triggered();

    void on_actionInOrder_triggered();

    void on_actionPostOrder_triggered();

    void on_actionheight_triggered();

    void on_actionnumberOfNodes_triggered();

    void on_actionsave_triggered();

    void on_actionread_triggered();

    void on_actionflashNodesAtIncreasingDepth_triggered();

    void on_actioncreate_random_search_tree_triggered();

    void on_actionWorst_Case_AVL_triggered();

    void on_actionRandom_AVL_triggered();

    void on_actionRandom_NOT_AVL_triggered();

    void on_actionshow_Colors_triggered();

    void on_actionshow_Numbers_triggered();

    void on_actioncontains_triggered();

    void on_actiontestTree1_triggered();

    void on_actiontestfunktion1_triggered();

    void on_actiontestfunktion2_triggered();

    void on_actiontestfunktion3_triggered();

    void on_actiontestfunktion4_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
