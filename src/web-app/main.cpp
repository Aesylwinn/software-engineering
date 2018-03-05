/*Written by Darius and Parker*/
#include "interestdata.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    interestData w;
    w.setWindowFlags(Qt::Window);
    w.show();

    return a.exec();
}
