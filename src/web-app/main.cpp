/*Written by Darius and Parker*/
#include "interestdata.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    interestData w;
    w.setWindowFlags(Qt::Window);
    w.setStyleSheet("background-color:#5ec7ff");
    w.show();


    return a.exec();
}
