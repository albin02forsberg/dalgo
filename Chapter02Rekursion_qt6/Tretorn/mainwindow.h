#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// #include <QSoundEffect>

#include "towers.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

   //  QSoundEffect _soundClaps;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void enableOptions();
    void reset();
    void mix();

    void on_actionmoveDiscs_triggered();

    void on_actionsolveMixed_triggered();

private:
    void setSize(int size);

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
