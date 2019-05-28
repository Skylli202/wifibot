#include "speedcontrol.h"
#include "ui_speedcontrol.h"

#include <QDebug>

SpeedControl::SpeedControl(QWidget *parent, int cursorValue) :
    QFrame(parent),
    ui(new Ui::SpeedControl)
{
    ui->setupUi(this);
    // The widget is initializing with the speed at 120 (50%)
    this->speedValue = 120;
    this->cursorValue = cursorValue;
    ui->progressBar->setValue(speedValue);
    ui->label->setText(QString::number(ui->progressBar->value()));

    // Connect signal to slot
    connect(ui->upButton, SIGNAL(clicked()), this, SLOT(increaseSpeed()));
    connect(ui->downButton, SIGNAL(clicked()), this, SLOT(decreaseSpeed()));
}

SpeedControl::~SpeedControl()
{
    delete ui;
}

// Return a boolean base on : is the new speed acceptable as new Speed Value of the robot ?
bool SpeedControl::speedValueCanBeIncreaseTo(int newSpeed){
    int minValue = ui->progressBar->minimum();
    int maxValue = ui->progressBar->maximum();


    // Listener for debug
//    qDebug() << "minValue = " << minValue;
//    qDebug() << "maxValue = " << maxValue;

    if(newSpeed > maxValue)
        return false;

    if(newSpeed < minValue)
        return false;

    return true;
}

// Increase the progress bar while making sure that we do not goes out of boundaries of the speed value of the robot's motor.
void SpeedControl::increaseSpeed(){
    if(!speedValueCanBeIncreaseTo(speedValue+this->cursorValue)){
        qDebug() << "speedValue cannot be increase (max value reached)";
    } else {
        speedValue+= cursorValue;
        ui->progressBar->setValue(speedValue);
        ui->label->setText(QString::number(ui->progressBar->value()));
        qDebug() << "speedValue has been increased (" << speedValue << ")";
    }
}

// Decrease the progress bar while making sure that we do not goes out of boundaries of the speed value of the robot's motor.
void SpeedControl::decreaseSpeed(){
    if(!speedValueCanBeIncreaseTo(speedValue-this->cursorValue)){
        qDebug() << "speedValue cannot be decrease (min value reached)";
    } else {
        speedValue -= cursorValue;
        ui->progressBar->setValue(speedValue);
        ui->label->setText(QString::number(ui->progressBar->value()));
        qDebug() << "speedValue has been decreased (" << speedValue << ")";
    }
}

// Getter & Setter of cursorValue member
void SpeedControl::setCursorValue(int i){
    this->cursorValue = i;
}

int SpeedControl::getCursorValue() {return this->cursorValue;}
