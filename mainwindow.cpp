#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->timer = new QTimer(this);
    this->timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerAction()));
    this->robot = new MyRobot(this);

    this->speedcontrol = new SpeedControl(this,10);
    speedcontrol->move(100,100);

    QWebEngineView *view = new QWebEngineView(parent);
     view->load(QUrl("http://192.168.1.11:8080/stream_simple.html"));
     view->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// on_action stuff
void MainWindow::on_actionDoConnect_triggered()
{
    robot->doConnect();
}

void MainWindow::timerAction(){
    qDebug() << "salut toi";
}

void MainWindow::on_actionDoDisconnect_triggered()
{
    robot->disConnect();
}

void MainWindow::on_backwardButton_clicked()
{
    robot->writeData(120, 120, false, false);
    ui->pressedKeyLabel->setText("moving backward");
}

void MainWindow::on_forwardButton_clicked()
{
    robot->writeData(120, 120, true, true);
    ui->pressedKeyLabel->setText("moving forward");
}

// keypress
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    short speedValue = (short) this->speedcontrol->getSpeedValue();
    if(event->key() == Qt::Key_Escape)
    {
        robot->doConnect();
        ui->pressedKeyLabel->setText("You pressed ESC");
    } else if (event->key() == Qt::Key_Up) {
        ui->pressedKeyLabel->setText("You pressed " + QKeySequence(event->key()).toString());
        robot->writeData(speedValue, speedValue, true, true);
    } else if (event->key() == Qt::Key_Down) {
        ui->pressedKeyLabel->setText("You pressed " + QKeySequence(event->key()).toString());
        robot->writeData(speedValue, speedValue, false, false);
    } else if (event->key() == Qt::Key_Left) {
        ui->pressedKeyLabel->setText("You pressed " + QKeySequence(event->key()).toString());
        robot->writeData(40, 40, false, true);
    } else if (event->key() == Qt::Key_Right) {
        ui->pressedKeyLabel->setText("You pressed " + QKeySequence(event->key()).toString());
        robot->writeData(40,40,true,false);
    } else {
        ui->pressedKeyLabel->setText("You pressed " + QKeySequence(event->key()).toString());
    }
}

// keyrelease
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        ui->pressedKeyLabel->setText("You released ESC");
    } else if (event->key() == Qt::Key_Up) {
        ui->pressedKeyLabel->setText("You released " + QKeySequence(event->key()).toString());
        robot->resetDataToSend();
    } else if (event->key() == Qt::Key_Down) {
        ui->pressedKeyLabel->setText("You released " + QKeySequence(event->key()).toString());
        robot->resetDataToSend();
    } else if (event->key() == Qt::Key_Left) {
        ui->pressedKeyLabel->setText("You released " + QKeySequence(event->key()).toString());
        robot->resetDataToSend();
    } else if (event->key() == Qt::Key_Right) {
        ui->pressedKeyLabel->setText("You released " + QKeySequence(event->key()).toString());
        robot->resetDataToSend();
    } else {
        ui->pressedKeyLabel->setText("You released " + QKeySequence(event->key()).toString());
    }
}
