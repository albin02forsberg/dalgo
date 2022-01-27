#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "towers.h"

#include <QDebug>
#include "studentsTreTorn1.h"
#include "studentsTreTorn2.h"
#include <assert.h>
#include <string>

const char* nameOfStudent();

Towers TOWERS;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    // _soundClaps(this),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle( QString("nameOfStudent is ") + QString::fromUtf8( nameOfStudent() ) );


    ui->centralWidget->setTowers(&TOWERS);
   // _soundClaps.setSource(QUrl::fromLocalFile(":/sounds/claps.wav"));


    connect(ui->menuSettings, SIGNAL(aboutToShow()), this, SLOT(enableOptions()));
    connect(ui->menuUppdrag, SIGNAL(aboutToShow()), this, SLOT(enableOptions()));

    connect(ui->actionReset, SIGNAL(triggered()), this, SLOT(reset()));

    connect(ui->action3, &QAction::triggered, [this](){ setSize(3);});
    connect(ui->action5, &QAction::triggered, [this](){ setSize(5);});
    connect(ui->action10, &QAction::triggered, [this](){ setSize(10);});
    connect(ui->action20, &QAction::triggered, [this](){ setSize(20);});
    connect(ui->action50, &QAction::triggered, [this](){ setSize(50);});
    connect(ui->action100, &QAction::triggered, [this](){ setSize(100);});

    connect(ui->actionMix, &QAction::triggered, this, &MainWindow::mix);

    connect(ui->actionSlow, &QAction::triggered, [this](){ ui->centralWidget->setSpeed(0); enableOptions();});
    connect(ui->actionNormal, &QAction::triggered, [this](){ ui->centralWidget->setSpeed(1); enableOptions();});
    connect(ui->actionFast, &QAction::triggered, [this](){ ui->centralWidget->setSpeed(2); enableOptions();});



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enableOptions()
{
    qDebug() << "enableOptions() was called";

    ui->actionmoveDiscs->setEnabled(TOWERS.isReseted());

    ui->menuSize->setEnabled(TOWERS.isReseted());
    ui->actionMix->setEnabled(true);

    ui->actionSlow->setChecked(ui->centralWidget->getSpeed()==0);
    ui->actionNormal->setChecked( ui->centralWidget->getSpeed()==1);
    ui->actionFast->setChecked( ui->centralWidget->getSpeed()==2);

    ui->action3->setChecked(TOWERS.nbrDiscs()==3);
    ui->action5->setChecked(TOWERS.nbrDiscs()==5);

    ui->action10->setChecked(TOWERS.nbrDiscs()==10);

    ui->action20->setChecked(TOWERS.nbrDiscs()==20);
    ui->action50->setChecked(TOWERS.nbrDiscs()==50);
    ui->action100->setChecked(TOWERS.nbrDiscs()==100);
}

void MainWindow::reset()
{
    TOWERS.reset();
    ui->centralWidget->update();


}

void MainWindow::setSize(int size)
{
    TOWERS.reset(size);
    ui->centralWidget->update();
}

void MainWindow::mix()
{
    TOWERS.mix();
    ui->centralWidget->update();
}


void MainWindow::on_actionmoveDiscs_triggered()
{
    assert( std::string("Homer Simpson") != nameOfStudent() );

    moveDiscs(TOWERS.nbrDiscs(), 0, 2);
    if (TOWERS.isReseted()){
//        _soundClaps.setVolume(0.25f);
//        _soundClaps.play();
    }
    enableOptions();
}

void MainWindow::on_actionsolveMixed_triggered()
{
    if (!TOWERS.isReseted()){
        solveMixedTower();
        if (TOWERS.isReseted()){
//            _soundClaps.setVolume(0.25f);
//            _soundClaps.play();
        }
    }
    enableOptions();
}
