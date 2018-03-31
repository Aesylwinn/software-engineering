#include <QApplication>

#include "../base-app/clientnetworkmgr.h"

#include "loginpage.h"
#include "registerpage.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    base::ClientNetworkMgr networkMgr;

    // Pages
    LoginPage loginPage(&networkMgr);
    RegisterPage registerPage(&networkMgr);

    // Slots and Signals
    QObject::connect(&loginPage, &LoginPage::onRegister, &registerPage, &RegisterPage::show);
    QObject::connect(&registerPage, &RegisterPage::onSuccess, &loginPage, &LoginPage::show);
    QObject::connect(&registerPage, &RegisterPage::onCanceled, &loginPage, &LoginPage::show);

    // Start on the login page
    loginPage.show();

    return app.exec();
}
