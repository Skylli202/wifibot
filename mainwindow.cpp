#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    robot = new MyRobot(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "Hello dany";
    robot->readyRead();

}

void MainWindow::on_actionDoConnect_2_triggered()
{
    qDebug() << "Hello dany";
    robot->doConnect();
}
