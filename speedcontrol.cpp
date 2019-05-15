#include "speedcontrol.h"
#include "ui_speedcontrol.h"

#include <QDebug>

SpeedControl::SpeedControl(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SpeedControl)
{
    ui->setupUi(this);
    speedValue = 0;

    connect(ui->upButton, SIGNAL(clicked()), this, SLOT(increaseSpeed()));
    connect(ui->downButton, SIGNAL(clicked()), this, SLOT(decreaseSpeed()));
}

SpeedControl::~SpeedControl()
{
    delete ui;
}

void SpeedControl::increaseSpeed(){
    speedValue++;
    ui->progressBar->setValue(speedValue);
    qDebug() << "speedValue has been increased (" << speedValue << ")";
}

void SpeedControl::decreaseSpeed(){
    speedValue--;
    ui->progressBar->setValue(speedValue);
    qDebug() << "speedValue has been decreased (" << speedValue << ")";
}
