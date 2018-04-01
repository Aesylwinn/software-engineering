#include "registerpage.h"
#include "ui_registerpage.h"

#include <exception>

RegisterPage::RegisterPage(base::ClientNetworkMgr* mgr, QWidget *parent)
    : QWidget(parent)
    , mUi(new Ui::RegisterPage)
    , mNetworkMgr(mgr)
{
    if (!mgr) {
        throw std::runtime_error("LoginPage requires network mgr");
    } else {
        connect(mgr, &base::ClientNetworkMgr::responseRecieved, this, &RegisterPage::onResponseRecieved);
    }

    mUi->setupUi(this);

    connect(mUi->registerButton, &QPushButton::clicked, this, &RegisterPage::onRegisterClicked);
}

RegisterPage::~RegisterPage()
{
    delete mUi;
}

void RegisterPage::onRegisterClicked(bool)
{
    // TODO Submit/verify
    emit onSuccess();
    // No longer show window
    hide();
}

void RegisterPage::onResponseRecieved(base::NetworkObject response) {
    switch (response.getPayloadType()) {
    default:
        // Do nothing
        break;
    }
}
