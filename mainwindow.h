#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>

#include "myrobot.h"
#include "speedcontrol.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void function();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void getData(QByteArray qb);
    struct Data{
        // left side
        short leftSpeed;
        float IR1;
        float IR2;
        float leftOdometry;

        // right side
        short rightSpeed;
        float IR3;
        float IR4;
        float rightOdometry;

        // general
        char batteryLevel;
        int version;
    } Data;
    struct Data data;


private slots:
    void timerAction();
    void on_actionDoDisconnect_triggered();
    void on_actionDoConnect_triggered();
    void on_backwardButton_clicked();
    void on_forwardButton_clicked();
    void update(QByteArray qb);
//    void update();

private:
    Ui::MainWindow *ui;
    MyRobot *robot;
    QTimer *timer;
    SpeedControl *speedcontrol;
};

#endif // MAINWINDOW_H
