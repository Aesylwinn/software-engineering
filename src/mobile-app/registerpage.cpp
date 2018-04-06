#include "registerpage.h"
#include "ui_registerpage.h"

#include <QMessageBox>

#include <exception>

RegisterPage::RegisterPage(base::ClientNetworkMgr* mgr, QWidget *parent)
    : QWidget(parent)
    , mUi(new Ui::RegisterPage)
    , mNetworkMgr(mgr)
    , mRegisterTicket(-1)
{
    if (!mgr) {
        throw std::runtime_error("LoginPage requires network mgr");
    } else {
        connect(mgr, &base::ClientNetworkMgr::responseRecieved, this, &RegisterPage::onResponseRecieved);
    }

    mUi->setupUi(this);

    connect(mUi->registerButton, &QPushButton::clicked, this, &RegisterPage::onRegisterClicked);
    connect(mUi->cancelButton, &QPushButton::clicked, this, &RegisterPage::onCancelClicked);
}

RegisterPage::~RegisterPage()
{
    delete mUi;
}

void RegisterPage::onRegisterClicked(bool)
{
    // Grab data
    base::CreateAccountRequest data;
    data.username = mUi->usernameField->text();
    data.password = mUi->passwordField->text();
    QString confirmedPassword = mUi->confirmPasswordField->text();
    data.profile.setEmail(mUi->emailField->text());
    data.profile.setFirstName(mUi->firstNameField->text());
    data.profile.setLastName(mUi->lastNameField->text());
    data.profile.setGender(mUi->maleButton->isChecked() ? mUi->maleButton->text() : mUi->femaleButton->text());
    data.profile.setBirthday(mUi->dobDatePicker->date());

    // Verify
    if (data.password != confirmedPassword) {
        QMessageBox messageBox;
        messageBox.critical(this, "Error", "Passwords do not match!");
    }

    // Request
    base::NetworkObject request(data);
    mRegisterTicket = mNetworkMgr->sendRequest(request);
}

void RegisterPage::onCancelClicked(bool)
{
    emit onCanceled();
    hide();
}

void RegisterPage::onResponseRecieved(base::NetworkObject response) {
    switch (response.getPayloadType()) {
    case base::PT_CreateAccountResponse:
        if (response.getTicket() == mRegisterTicket) {
            base::CreateAccountResponse info = response.convert<base::CreateAccountResponse>();
            qInfo("Account created: %d msg: %s", info.valid, qUtf8Printable(info.details));

            if (info.valid) {
                // Signal succes and close the window
                emit onSuccess();
                hide();
            } else {
                QMessageBox messageBox;
                messageBox.critical(this, "Error", "Failed to create account. Username taken.");
            }
        }
        break;

    default:
        // Do nothing
        break;
    }
}
