#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>
#include <QWebEngineView>
#include <QWebEngineFullScreenRequest>

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
        int IR1;
        int IR2;
        int leftOdometry;

        // right side
        short rightSpeed;
        int IR3;
        int IR4;
        int rightOdometry;

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
    QWebEngineView *m_view;
};

#endif // MAINWINDOW_H
