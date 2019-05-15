#include "mainwindow.h"
#include "ui_mainwindow.h"

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionDoConnect_2_triggered()
{
    qDebug() << "Hello dany";
    //robot->doConnect();

    //
    if(!timer->isActive())
        timer->start();
}

void MainWindow::timerAction(){
    qDebug() << "salut toi";
}
