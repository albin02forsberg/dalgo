// copyright (c) Ragnar Nohre

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionReset_triggered()
{
    ui->triangleWidget->reset();
}

void MainWindow::on_actioneasy_triggered()
{
    ui->triangleWidget->resetToEasyState();

}
