#ifndef SPEEDCONTROL_H
#define SPEEDCONTROL_H

#include <QFrame>

namespace Ui {
class SpeedControl;
}

class SpeedControl : public QFrame
{
    Q_OBJECT

public:
    explicit SpeedControl(QWidget *parent = nullptr);
    ~SpeedControl();

private slots:
    void increaseSpeed();
    void decreaseSpeed();

private:
    Ui::SpeedControl *ui;
    int speedValue;
};

#endif // SPEEDCONTROL_H
