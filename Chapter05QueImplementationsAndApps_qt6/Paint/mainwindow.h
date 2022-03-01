#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QActionGroup>

#include "idrawingparent.h"
#include <vector>
#include <assert.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public IDrawingParent
{
    Q_OBJECT

    QActionGroup *_colorGroup = nullptr;
    QActionGroup *_penGroup = nullptr;
    QActionGroup *_speedGroup = nullptr;

    const int  _numberOfRows   = 30;
    const int _numberOfColumns = 50;

    bool      _doDelaySetpixel = true;
    int       _durationOfSetpixel = 10;

    std::vector< std::vector<QColor> > _pixels; // (_numberOfRows, std::vector<QColor>(_numberOfColumns, Qt::white));

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool isInside(int r, int k) override { return r>=0 && r<_numberOfRows && k>=0 && k<_numberOfColumns;}
    QColor pixel(int r, int k) override { assert(isInside(r,k));  return _pixels[r][k]; }
    void setPixel(int r, int k, QColor color) override;
    int numberOfRows() override { return _pixels.size(); }
    int numberOfColumns() override { return _pixels[0].size(); }
    QColor colorSelected() override;
    bool   isPentool() override;
    bool   isFilltool() override;
    bool   isFulltool() override;

    bool isFilltoolNonRecursiveStack() override;
    bool isFilltoolNonRecursiveFifo() override;
signals:
    void pixelChanged(int r, int k) ;


private slots:
    void on_actionErase_triggered();

    void speedDidChange(QAction *action);
    void penDidChange(QAction *action);

    void on_actionSpiral_triggered();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
