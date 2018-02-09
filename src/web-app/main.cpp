#include "interestdata.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    interestData w;
    w.show();

    return a.exec();
}
