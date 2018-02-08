#include "interestdata.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InterestData w;
    w.show();

    return a.exec();
}
