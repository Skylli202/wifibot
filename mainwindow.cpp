#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "speedcontrol.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerAction()));
    robot = new MyRobot(this);

    SpeedControl *speedControl = new SpeedControl(this);
    speedControl->move(100,100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionDoConnect_2_triggered()
{
//    qDebug() << "Hello dany";
    robot->doConnect();
}

void MainWindow::timerAction(){
    qDebug() << "salut toi";
}

void MainWindow::on_actionDoDisconnect_triggered()
{
    robot->disConnect();
}
