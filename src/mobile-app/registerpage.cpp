#include "registerpage.h"
#include "ui_registerpage.h"

RegisterPage::RegisterPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterPage)
{
    ui->setupUi(this);

    connect(ui->registerButton, &QPushButton::clicked, this, &RegisterPage::onRegisterClicked);
}

RegisterPage::~RegisterPage()
{
    delete ui;
}

void RegisterPage::onRegisterClicked(bool)
{
    // TODO Submit/verify
    emit onSuccess();
    // No longer show window
    hide();
}
