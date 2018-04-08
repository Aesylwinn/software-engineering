/*Written by Darius and Parker*/
#include "interestdata.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    interestData w;
    w.setWindowFlags(Qt::Window);
    w.show();

    a.setStyleSheet(
        "QWidget {background-color:#5ec7ff}"
        "QLineEdit {"
        "background-color: #E5E8E8;"
        "border: none;"
        "} "
        "QPushButton {"
            "background-color: rgb(180, 180, 180);"


            "min-width:60px;"

        "}"

        );

    return a.exec();
}
