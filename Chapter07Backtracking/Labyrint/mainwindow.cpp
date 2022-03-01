// copyright (c) Ragnar Nohre

#include "mainwindow.h"
#include "mazewidget.h"

#include "ui_mainwindow.h"
#include "studentLabyrint1.h"

#include <QPaintEvent>
#include <QPainter>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _groupSpeed = new QActionGroup(this);
    _groupSpeed->addAction(ui->actionSlow);
    _groupSpeed->addAction(ui->actionNormal);
    _groupSpeed->addAction(ui->actionFast);
    _groupSpeed->addAction(ui->actionUltrafast);
    ui->actionNormal->trigger();



    connect(_groupSpeed, &QActionGroup::triggered, this, &MainWindow::speedDidChange);
    ui->actionNormal->trigger();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::speedDidChange(QAction *action)
{
    int durationOfDelay = 0;

    if (action==ui->actionSlow) durationOfDelay = 100;
    else if (action==ui->actionNormal)  durationOfDelay = 30;
    else if (action==ui->actionFast)  durationOfDelay = 1;
    else if (action==ui->actionUltrafast)  durationOfDelay = 0;
    else assert(false);

    ui->centralWidget->setDurationOfDelay(durationOfDelay);

}


void MainWindow::on_actionUniqpath_triggered()
{
    ui->centralWidget->initializeMazeThatFitsWindow(false);

}

void MainWindow::on_actionfMuliplepath_triggered()
{
    ui->centralWidget->initializeMazeThatFitsWindow(true);

}



void MainWindow::on_actionSearchRecursive_triggered()
{
    ui->centralWidget->callStudentsSearch(true);
}

void MainWindow::on_actionSearchFIFO_triggered()
{
    ui->centralWidget->callStudentsSearch(false);

}
