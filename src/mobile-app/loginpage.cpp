#include "loginpage.h"
#include "ui_loginpage.h"

#include <exception>

LoginPage::LoginPage(base::ClientNetworkMgr* mgr, QWidget *parent)
    : QWidget(parent)
    , mUi(new Ui::LoginPage)
    , mNetworkMgr(mgr)
{
    if (!mgr) {
        throw std::runtime_error("LoginPage requires network mgr");
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
    // TODO: submit/verify
    emit onSuccess();
}

void LoginPage::onRegisterClicked(bool)
{
    emit onRegister();
}
