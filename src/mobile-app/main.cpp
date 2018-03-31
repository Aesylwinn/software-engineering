#include <QApplication>

#include "loginpage.h"
#include "registerpage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginPage loginPage;
    RegisterPage registerPage;


    registerPage.show();

    return a.exec();
}
