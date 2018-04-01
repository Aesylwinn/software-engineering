#include <QApplication>

#include <QMessageBox>

#include "../base-app/clientnetworkmgr.h"
#include "../base-app/base-app_global.h"

#include "createeventpage.h"
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
    CreateEventPage createEventPage(&networkMgr);

    // Slots and Signals
    QObject::connect(&networkMgr, &base::ClientNetworkMgr::disconnected, [&] {
        // Need to go back to the login page
        createEventPage.hide();
        loginPage.show();

        int retry = QMessageBox::StandardButton::Retry;
        int abort = QMessageBox::StandardButton::Abort;
        if (QMessageBox::critical(&loginPage, "Error", "Disconnected", retry, abort) == retry) {
            networkMgr.connect(SERVER_ADDRESS, SERVER_PORT);
        } else {
            app.exit(1);
        }
    });

    QObject::connect(&loginPage, &LoginPage::onRegister, &registerPage, &RegisterPage::show);
    QObject::connect(&loginPage, &LoginPage::onSuccess, &createEventPage, &CreateEventPage::show);

    QObject::connect(&registerPage, &RegisterPage::onSuccess, &loginPage, &LoginPage::show);
    QObject::connect(&registerPage, &RegisterPage::onCanceled, &loginPage, &LoginPage::show);

    //QObject::connect(&createEventPage, &CreateEventPage::onSuccess,);
    //QObject::connect(&createEventPage, &CreateEventPage::onCanceled,);

    // Start on the login page
    loginPage.show();

    return app.exec();
}
