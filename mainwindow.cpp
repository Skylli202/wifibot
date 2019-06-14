#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "string"

#include <QDebug>
#include <QURl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->timer = new QTimer(this);
    this->timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerAction()));
    this->robot = new MyRobot(this);

    connect(this->robot, SIGNAL(updateUI(QByteArray)), this, SLOT(update(QByteArray)));

    this->speedcontrol = new SpeedControl(this,10);
    speedcontrol->move(300,100);

    //this->m_view(new QWebEngineView(this));

    this->m_view = new QWebEngineView(this);
    this->m_view->load(QUrl("http://192.168.1.11:8080/?action=stream"));

    this->m_view->move(480, 20);
    this->m_view->resize(300,300);

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
    robot->writeData(static_cast<short>(this->speedcontrol->getSpeedValue()), static_cast<short>(this->speedcontrol->getSpeedValue()), false, false);
    ui->pressedKeyLabel->setText("moving backward");
}

void MainWindow::on_forwardButton_clicked()
{
    robot->writeData(static_cast<short>(this->speedcontrol->getSpeedValue()), static_cast<short>(this->speedcontrol->getSpeedValue()), true, true);
    ui->pressedKeyLabel->setText("moving forward");
}

// Struct data
void MainWindow::getData(QByteArray dataReceived) {
    // left side
    data.leftSpeed = dataReceived[0] + (dataReceived[1] << 8);
    // Gestion de la conversion de char vers short et le bit de signe
    if(data.leftSpeed > 32767)
        data.leftSpeed = data.leftSpeed - 65536;
    data.IR1 = dataReceived[3];
    data.IR2 = dataReceived[4];
    data.leftOdometry = ((((long)dataReceived[8] << 24)) + (((long)dataReceived[7] << 16)) + (((long)dataReceived[6] << 8)) + ((long)dataReceived[5]));

    // right side
    data.rightSpeed = dataReceived[9] + (dataReceived[10] << 8);
    // Gestion de la conversion de char vers short et le bit de signe
    if(data.rightSpeed > 32767)
        data.rightSpeed = data.rightSpeed - 65536;
    data.IR3 = dataReceived[11];
    data.IR4 = dataReceived[12];
    data.rightOdometry = ((((long)dataReceived[16] << 24)) + (((long)dataReceived[15] << 16)) + (((long)dataReceived[14] << 8)) + ((long)dataReceived[13]));

    // general
    data.batteryLevel =  dataReceived[2];
    qDebug() << "dataRecevied[2] = " << data.batteryLevel;
    data.version = dataReceived[18];
}

//  UI
void MainWindow::update(QByteArray qb){
    getData(qb);

    this->m_view->repaint();

    //    robot->printData(qb);

    QString str = "";

    //    // Left stuff
    ui->label_leftSpeed->setText("left speed : " + QString::number(data.leftSpeed));
    ui->label_leftOdometry->setText("left Odome : " + QString::number(data.leftOdometry));

    //    // Right stuff
    ui->label_rightSpeed->setText("right speed : " + QString::number(data.rightSpeed));
    ui->label_rightOdometry->setText("right Odome : " + QString::number(data.rightOdometry));

    //    str = QString(static_cast<unsigned char>(qb[2]));
    ui->label_Battery->setText("Battery : " + QString::number(data.batteryLevel+256));
    ui->label_Version->setText("Version : " + QString::number(data.version));

    // IR
    ui->label_IR1->setText("IR1 : " + QString::number(data.IR1));
    ui->label_IR2->setText("IR2 : " + QString::number(data.IR2));
    ui->label_IR3->setText("IR3 : " + QString::number(data.IR3));
    ui->label_IR4->setText("IR4 : " + QString::number(data.IR4));
}

// keypress
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    short speedValue = static_cast<short>(this->speedcontrol->getSpeedValue());

    // Connect Disconnect
    if (event->key() == Qt::Key_Ampersand) {
        ui->pressedKeyLabel->setText("You pressed " + QKeySequence(event->key()).toString());
        robot->doConnect();
    } else if (event->key() == Qt::Key_Eacute) {
        ui->pressedKeyLabel->setText("You pressed " + QKeySequence(event->key()).toString());
        robot->disConnect();
    }

    // Flèches directionnel
    else if (event->key() == Qt::Key_Up) {
        ui->pressedKeyLabel->setText("You pressed " + QKeySequence(event->key()).toString());
        robot->writeData(speedValue, speedValue, true, true);
    } else if (event->key() == Qt::Key_Down) {
        ui->pressedKeyLabel->setText("You pressed " + QKeySequence(event->key()).toString());
        robot->writeData(speedValue, speedValue, false, false);
    } else if (event->key() == Qt::Key_Left) {
        ui->pressedKeyLabel->setText("You pressed " + QKeySequence(event->key()).toString());
        robot->writeData(speedValue, speedValue, false, true);
    } else if (event->key() == Qt::Key_Right) {
        ui->pressedKeyLabel->setText("You pressed " + QKeySequence(event->key()).toString());
        robot->writeData(speedValue,speedValue,true,false);
    }

    // increaseSpeed decreaseSpeed
    else if (event->key() == Qt::Key_Equal) {
        ui->pressedKeyLabel->setText("You pressed " + QKeySequence(event->key()).toString());
        speedcontrol->increaseSpeed();
    } else if (event->key() == Qt::Key_Colon) {
        ui->pressedKeyLabel->setText("You pressed " + QKeySequence(event->key()).toString());
        speedcontrol->decreaseSpeed();
    }

    // else..
    else {
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
