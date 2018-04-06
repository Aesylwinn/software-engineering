#include <QApplication>

#include <QMessageBox>

#include "../base-app/clientnetworkmgr.h"
#include "../base-app/base-app_global.h"

#include "createeventpage.h"
#include "loginpage.h"
#include "mainpage.h"
#include "matchespage.h"
#include "registerpage.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setStyleSheet(
        "QWidget { background-color: #c2f2fc } "
        "QLineEdit { background-color: #e6f4f7 } "
        "QTextEdit { background-color: #e6f4f7 } "
    );

    // Communicate with server
    base::ClientNetworkMgr networkMgr;
    networkMgr.connect(SERVER_ADDRESS, SERVER_PORT);

    // Pages
    LoginPage loginPage(&networkMgr);
    RegisterPage registerPage(&networkMgr);

    MainPage mainPage(&networkMgr);
    CreateEventPage createEventPage(&networkMgr);
    MatchesPage matchesPage(&networkMgr);

    // Slots and Signals
    QObject::connect(&networkMgr, &base::ClientNetworkMgr::disconnected, [&] {
        // Need to go back to the login page
        mainPage.hide();
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
    QObject::connect(&loginPage, &LoginPage::onSuccess, &mainPage, &MainPage::show);

    QObject::connect(&registerPage, &RegisterPage::onSuccess, &loginPage, &LoginPage::show);
    QObject::connect(&registerPage, &RegisterPage::onCanceled, &loginPage, &LoginPage::show);

    QObject::connect(&mainPage, &MainPage::onCreateEvent, &createEventPage, &CreateEventPage::show);
    QObject::connect(&mainPage, &MainPage::onViewMatches, &matchesPage, &MatchesPage::show);
    QObject::connect(&mainPage, &MainPage::onLogout, &loginPage, &LoginPage::show);

    QObject::connect(&createEventPage, &CreateEventPage::onSuccess, &mainPage, &MainPage::show);
    QObject::connect(&createEventPage, &CreateEventPage::onCanceled, &mainPage, &MainPage::show);

    QObject::connect(&matchesPage, &MatchesPage::onBack, &mainPage, &MainPage::show);

    // Start on the login page
    loginPage.show();

    return app.exec();
}
