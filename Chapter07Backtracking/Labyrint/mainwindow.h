#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QActionGroup>
#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QActionGroup *_groupSpeed = nullptr;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:

    void on_actionUniqpath_triggered();

    void on_actionfMuliplepath_triggered();

    void speedDidChange(QAction *action);
    void on_actionSearchRecursive_triggered();

    void on_actionSearchFIFO_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
