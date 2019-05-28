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
    explicit SpeedControl(QWidget *parent = nullptr, int cursorValue = 1);
    ~SpeedControl();

    bool speedValueCanBeIncreaseTo(int newSpeed);

    // Getter & Setter
    void setCursorValue(int i);
    int getCursorValue();

private slots:
    void increaseSpeed();
    void decreaseSpeed();

private:
    Ui::SpeedControl *ui;
    int speedValue;
    int cursorValue;
};

#endif // SPEEDCONTROL_H
