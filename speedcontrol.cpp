#include "speedcontrol.h"
#include "ui_speedcontrol.h"

#include <QDebug>

SpeedControl::SpeedControl(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SpeedControl)
{
    ui->setupUi(this);
    speedValue = 0;
    ui->label->setText("");

    connect(ui->upButton, SIGNAL(clicked()), this, SLOT(increaseSpeed()));
    connect(ui->downButton, SIGNAL(clicked()), this, SLOT(decreaseSpeed()));
}

SpeedControl::~SpeedControl()
{
    delete ui;
}

bool SpeedControl::speedValueCanBeIncreaseTo(int newSpeed){
    int minValue = ui->progressBar->minimum();
    int maxValue = ui->progressBar->maximum();


    // Listener
//    qDebug() << "minValue = " << minValue;
//    qDebug() << "maxValue = " << maxValue;

    if(newSpeed > maxValue)
        return false;

    if(newSpeed < minValue)
        return false;

    return true;
}

void SpeedControl::increaseSpeed(){
    if(!speedValueCanBeIncreaseTo(speedValue+1)){
        qDebug() << "speedValue cannot be increase (max value reached)";
    } else {
        speedValue++;
        ui->progressBar->setValue(speedValue);
        ui->label->setText(QString::number(ui->progressBar->value()));
        qDebug() << "speedValue has been increased (" << speedValue << ")";
    }
}

void SpeedControl::decreaseSpeed(){
    if(!speedValueCanBeIncreaseTo(speedValue-1)){
        qDebug() << "speedValue cannot be decrease (min value reached)";
    } else {
        speedValue--;
        ui->progressBar->setValue(speedValue);
        ui->label->setText(QString::number(ui->progressBar->value()));
        qDebug() << "speedValue has been decreased (" << speedValue << ")";
    }
}
