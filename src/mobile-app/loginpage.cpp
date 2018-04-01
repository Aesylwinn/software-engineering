#include "loginpage.h"
#include "ui_loginpage.h"

#include <exception>

LoginPage::LoginPage(base::ClientNetworkMgr* mgr, QWidget *parent)
    : QWidget(parent)
    , mUi(new Ui::LoginPage)
    , mNetworkMgr(mgr)
    , mLoginTicket(-1)
{
    if (!mgr) {
        throw std::runtime_error("LoginPage requires network mgr");
    } else {
        connect(mgr, &base::ClientNetworkMgr::responseRecieved, this, &LoginPage::onResponseRecieved);
    }

    mUi->setupUi(this);

    connect(mUi->loginButton, &QPushButton::clicked, this, &LoginPage::onLoginClicked);
    connect(mUi->registerButton, &QPushButton::clicked, this, &LoginPage::onRegisterClicked);
}

LoginPage::~LoginPage()
{
    delete mUi;
}

void LoginPage::onLoginClicked(bool)
{
    QString username = mUi->usernameField->text();
    QString password = mUi->passwordField->text();

    base::NetworkObject request(base::LoginRequest{ username, password });
    mLoginTicket = mNetworkMgr->sendRequest(request);

    emit onSuccess();
}

void LoginPage::onRegisterClicked(bool)
{
    emit onRegister();
}

void LoginPage::onResponseRecieved(base::NetworkObject response)
{
    switch (response.getPayloadType()) {
    case base::NetworkObject::PT_LoginResponse:
        if (response.getTicket() == mLoginTicket) {
            base::LoginResponse info = response.getLoginResponse();
            qInfo("authenticated: %d host: %d msg: %s",
                  info.valid, info.isHost, qUtf8Printable(info.details));
            emit onSuccess();
        }
        break;

    default:
        // Do nothing
        break;
    }
}