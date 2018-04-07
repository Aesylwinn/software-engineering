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
        "QWidget { background-color: #2E86C1 } "
        "QListWidget{ background-color: #7FB3D5 }"
        "QLabel{background-color: #7FB3D5 }"
        "QLineEdit {"
        "background-color: #E5E8E8;"
        "border: none;"
        "} "
        "QTextEdit { background-color: #EAEDED } "
        "QPushButton {"
            "background-color: rgb(180, 180, 180);"
            "border-style: inset; "
            "border-width:1px;"
            "border-radius:30px;"
            "border-color: white;"
            "max-width:80px;"
            "max-height:60px;"
            "min-width:80px;"
            "min-height:60px"
        "}"
        "QScrollBar:vertical {"
            "    border: 1px solid #999999;"
            "    background:white;"
            "    width:10px;    "
            "    margin: 0px 0px 0px 0px;"
            "}"
            "QScrollBar::handle:vertical {"
            "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
            "    stop: 0 rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130), stop:1 rgb(32, 47, 130));"
            "    min-height: 0px;"
            "}"
            "QScrollBar::add-line:vertical {"
            "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
            "    stop: 0 rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130),  stop:1 rgb(32, 47, 130));"
            "    height: 0px;"
            "    subcontrol-position: bottom;"
            "    subcontrol-origin: margin;"
            "}"
            "QScrollBar::sub-line:vertical {"
            "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
            "    stop: 0  rgb(32, 47, 130), stop: 0.5 rgb(32, 47, 130),  stop:1 rgb(32, 47, 130));"
            "    height: 0 px;"
            "    subcontrol-position: top;"
            "    subcontrol-origin: margin;"
            "}"
            "QComboBox { border: 3px solid gray; border-radius: 18px; padding: 8px 20px 6px 8px; margin-top: 2px; border-color: lightgray; border-bottom-color: white; background: white; selection-background-color: rgb(70, 140, 250) }"
                                      "QComboBox:focus { border-color: rgb(70, 140, 250) }"
                                      "QComboBox::drop-down { subcontrol-origin: padding; subcontrol-position: top right; width: 40px; border-style: none; padding-right 10px; selection-background-color: rgb(70, 140, 250) }"
                                      "QComboBox::down-arrow { image: url(/usr/share/themes/blanco/meegotouch/icons/icon-m-toolbar-down.png); }"
                                      "QListView { selection-background-color: rgb(70, 140, 250); }"
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
    QObject::connect(&createEventPage, &CreateEventPage::onSuccess, &mainPage, &MainPage::refresh);
    QObject::connect(&createEventPage, &CreateEventPage::onCanceled, &mainPage, &MainPage::show);

    QObject::connect(&matchesPage, &MatchesPage::onBack, &mainPage, &MainPage::show);

    // Start on the login page
    loginPage.show();

    return app.exec();
}
