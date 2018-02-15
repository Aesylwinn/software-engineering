#include "interestdata.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    interestData w;
    w.setWindowFlags(Qt::Window);
//    int x = w.width()*1.2;
//    int y = w.height()*1.2;
//    w.setFixedSize(x,y);
    w.show();

    return a.exec();
}
