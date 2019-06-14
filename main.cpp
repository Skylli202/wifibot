#include "mainwindow.h"
#include "math.h"
#include <QApplication>

char getiemebit(unsigned char c, int i);
QString getQString(unsigned char c);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

char getiemebit(unsigned char c, int i)
{
     return ((c>>i) & 1);
}

QString getQString(unsigned char c){
    int local = 0;

    for (int i=0; i<8; i++) {
        unsigned char tmp = getiemebit(c,i);
        if(tmp == 1)
            local += pow(2,i);
    }

    return static_cast<QString>(QString::number(local));
}
