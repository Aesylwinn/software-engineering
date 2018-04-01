#include <QApplication>

#include "../base-app/clientnetworkmgr.h"
#include "../base-app/base-app_global.h"

#include "loginpage.h"
#include "registerpage.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Communicate with server
    base::ClientNetworkMgr networkMgr;
    networkMgr.connect(SERVER_ADDRESS, SERVER_PORT);

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
