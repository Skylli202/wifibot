#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>

#include "myrobot.h"

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

private slots:
    void on_actionDoConnect_2_triggered();
    void timerAction();

private:
    Ui::MainWindow *ui;
    MyRobot *robot;
    QTimer *timer;
};

#endif // MAINWINDOW_H
