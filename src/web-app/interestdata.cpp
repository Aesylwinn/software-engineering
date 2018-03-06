/*Written by Darius and Parker*/
#include "interestdata.h"
#include "ui_interestdata.h"

using namespace base;

interestData::interestData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::interestData),
    mNetworkMgr(new ClientNetworkMgr(this)),
    mLoginRequest(-1)
{
    // Connect to the server
    mNetworkMgr->connect(QString(SERVER_ADDRESS), SERVER_PORT);
    connect(mNetworkMgr, &ClientNetworkMgr::responseRecieved,
            this, &interestData::checkResponse);

    ui->setupUi(this);
    ui->tabWidget->setCurrentWidget(ui->tab);
    ui->tabWidget_2->setCurrentWidget(ui->tab_2);
    ui->tabWidget->setTabEnabled(1, false);
    ui->tabWidget->setTabEnabled(2, false);

    connect(ui->get_started, SIGNAL(clicked()), this, SLOT(switchMainTabs()));
    connect(ui->Login, SIGNAL(clicked()), this, SLOT(switchLowTabs()));
    connect(ui->SignUp, SIGNAL(clicked()), this, SLOT(switchLowTabs()));
    connect(ui->togglePassword, SIGNAL(clicked()), this, SLOT(togglePassword()));
    connect(ui->togglePassword2, SIGNAL(clicked()), this, SLOT(togglePassword()));
    connect(ui->accept, SIGNAL(clicked()), this, SLOT(reverseLowTab()));
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(reverseLowTab()));
    connect(ui->createEvent, SIGNAL(clicked()), this, SLOT(popUpWindow()));
    connect(ui->GetVerifiedB, SIGNAL(clicked()), this, SLOT(popUpWindow()));
}

interestData::~interestData()
{
    // Note: mNetworkMgr memory is managed by Qt
    mNetworkMgr->disconnect();

    delete ui;
}

void interestData::switchMainTabs()
{
    ui->tabWidget->setTabEnabled(1, true);
    ui->tabWidget->setCurrentWidget(ui->signUp);
    ui->tabWidget_2->setTabEnabled(1, false);
    ui->tabWidget->setTabEnabled(0, false);
}

void interestData::switchLowTabs()
{
    QObject* button = QObject::sender();

    if(button == ui->Login){
        login("bob", "hatespasswords");
        ui->tabWidget->setCurrentWidget(ui->tab_4);
        ui->tabWidget->setTabEnabled(2, true);
        ui->tabWidget->setTabEnabled(1, false);
    }
    else{
        ui->tabWidget_2->setTabEnabled(1, true);
        ui->Nam_Display->setText(tr("Alright, %1!").arg(ui->lineEdit_FN->text()));
        ui->tabWidget_2->setCurrentWidget(ui->tab_3);
        ui->tabWidget_2->setTabEnabled(0, false);
    }
}

void interestData::reverseLowTab()
{
    QObject* button = QObject::sender();

    if(button == ui->accept){
        ui->tabWidget->setCurrentWidget(ui->tab_4);
        ui->tabWidget->setTabEnabled(2, true);
        ui->tabWidget->setTabEnabled(1, false);
    }
    else{
        ui->tabWidget_2->setTabEnabled(0, true);
        ui->tabWidget_2->setCurrentWidget(ui->tab_2);
        ui->tabWidget_2->setTabEnabled(1, false);
    }
}

void interestData::togglePassword()
{
    QObject* button = QObject::sender();
    if (button == ui->togglePassword)
    {
        if (ui->lineEdit_2->echoMode() == QLineEdit::Password)
            ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
        else
            ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    }
    else
    {
        if (ui->newPass->echoMode() == QLineEdit::Password)
        {
            ui->newPass->setEchoMode(QLineEdit::Normal);
            ui->confirmPass->setEchoMode(QLineEdit::Normal);
        }
        else
        {
            ui->newPass->setEchoMode(QLineEdit::Password);
            ui->confirmPass->setEchoMode(QLineEdit::Password);
        }
    }
}

void interestData::popUpWindow()
{
    QObject* button = QObject::sender();
    if (button == ui->createEvent)
    {
        eventPopUp* popInstance = new eventPopUp(this);
        popInstance->show();
    }
    else
    {
        Verified* popInstance = new Verified(this);
        popInstance->show();
//        ui->GetVerifiedB->setEnabled(false);
    }
}

void interestData::login(QString username, QString password)
{
    // Send request. The ticket will match to the response.
    NetworkObject request(NetworkObject::LoginRequest{ username, password });
    mLoginRequest = mNetworkMgr->sendRequest(request);
}

void interestData::checkResponse(base::NetworkObject response) {
    if (response.getTicket() == mLoginRequest) {
        // Reset ticket
        mLoginRequest = -1;
        // Handle response
        if (response.getPayloadType() == NetworkObject::PT_LoginResponse) {
            NetworkObject::LoginResponse info = response.getLoginResponse();
            qInfo("authenticated: %d msg: %s", info.valid, qUtf8Printable(info.details));
            // Handle here
        }
    }
}
