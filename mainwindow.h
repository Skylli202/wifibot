#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

#include "myrobot.h"
#include "keyenterreceiver.h"

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
    void on_pushButton_clicked();

    void on_actionDoConnect_2_triggered();

private:
    Ui::MainWindow *ui;
    MyRobot *robot;
    keyEnterReceiver *key;
};

#endif // MAINWINDOW_H
