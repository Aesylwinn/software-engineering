#include <QApplication>

#include "loginpage.h"
#include "registerpage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Pages
    LoginPage loginPage;
    RegisterPage registerPage;

    // Slots and Signals
    QObject::connect(&loginPage, &LoginPage::onRegister, &registerPage, &RegisterPage::show);
    QObject::connect(&registerPage, &RegisterPage::onSuccess, &loginPage, &LoginPage::show);
    QObject::connect(&registerPage, &RegisterPage::onCanceled, &loginPage, &LoginPage::show);
    // Start on the login page
    loginPage.show();

    return a.exec();
}
