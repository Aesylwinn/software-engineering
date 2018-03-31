#include "loginpage.h"
#include "ui_loginpage.h"

LoginPage::LoginPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginPage)
{
    ui->setupUi(this);

    connect(ui->loginButton, &QPushButton::clicked, this, &LoginPage::onLoginClicked);
    connect(ui->registerButton, &QPushButton::clicked, this, &LoginPage::onRegisterClicked);
}

LoginPage::~LoginPage()
{
    delete ui;
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
