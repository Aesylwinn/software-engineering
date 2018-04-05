/*Written by Darius and Parker*/
#include "interestdata.h"
#include "ui_interestdata.h"
#include <QMessageBox>

using namespace base;

interestData::interestData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::interestData),
    mNetworkMgr(new ClientNetworkMgr(this)),
    mLoginRequest(-1),
    mCreateAccountRequest(-1),
    mCreateEventRequest(-1),
    mCreateHostRequest(-1),
    mSuggestEventsRequest(-1)
{
    // Connect to the server
    mNetworkMgr->connect(QString(SERVER_ADDRESS), SERVER_PORT);
    connect(mNetworkMgr, &ClientNetworkMgr::responseRecieved,
            this, &interestData::checkResponse);

    //Sets up what tab it is on and what is greyed out
    ui->setupUi(this);
    ui->tabWidget->setCurrentWidget(ui->tab);
    ui->tabWidget_2->setCurrentWidget(ui->tab_2);
    ui->tabWidget->setTabEnabled(1, false);
    ui->tabWidget->setTabEnabled(2, false);
    ui->tabWidget->setTabEnabled(3, false);

    //connects all the buttons to its certain actions
    connect(ui->get_started, SIGNAL(clicked()), this, SLOT(switchMainTabs()));
    connect(ui->Login, SIGNAL(clicked()), this, SLOT(switchLowTabs()));
    connect(ui->SignUp, SIGNAL(clicked()), this, SLOT(switchLowTabs()));
    connect(ui->togglePassword, SIGNAL(clicked()), this, SLOT(togglePassword()));
    connect(ui->togglePassword2, SIGNAL(clicked()), this, SLOT(togglePassword()));
    connect(ui->accept, SIGNAL(clicked()), this, SLOT(reverseLowTab()));
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(reverseLowTab()));
    connect(ui->createEvent, SIGNAL(clicked()), this, SLOT(popUpWindow()));
    connect(ui->GetVerifiedB, SIGNAL(clicked()), this, SLOT(popUpWindow()));
    connect(ui->matchB, SIGNAL(clicked()), this, SLOT(popUpWindow()));
    connect(ui->logout, SIGNAL(clicked()), this, SLOT(logout()));
    connect(ui->createHost, SIGNAL(clicked()), this, SLOT(switchLowTabs()));
    connect(ui->logoutHost, SIGNAL(clicked()), this, SLOT(logout()));
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
    ui->tabWidget_2->setTabEnabled(0, true);
    ui->tabWidget_2->setTabEnabled(1, false);
    ui->tabWidget->setTabEnabled(0, false);
}

void interestData::switchLowTabs()
{
    QObject* button = QObject::sender();    //allows us to see which button is pushed

    //just lets us grey out certain tabs that do not need to be used at that time
    if(button == ui->Login)
    {
        if (ui->usrName->text().isEmpty() || ui->password->text().isEmpty())
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Please insert username or password");
            messageBox.setFixedSize(500,200);
        }
        else
            login(ui->usrName->text(), ui->password->text());   //logins to the server to communicate
    }
    else if(button == ui->SignUp)
    {
        if (ui->newPass->text() != ui->confirmPass->text())
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","The passwords do not match!\n You shall not PASS!!!");
            messageBox.setFixedSize(500,200);
        }
        else
        {
            if (ui->lineEdit_FN->text().isEmpty() || ui->lineEdit_LN->text().isEmpty() || ui->newUsrName->text().isEmpty() || ui->newPass->text().isEmpty())
            {
                QMessageBox messageBox;
                messageBox.critical(0,"Error","Please fill out all fields: \nFirst name, Last name, Username, and Password");
                messageBox.setFixedSize(500,200);
            }
            else
                // Create the account
                createAccount();
        }
    }
    else
    {
       if (ui->userNameHostEd->text().isEmpty() || ui->passwordHostEd->text().isEmpty() || ui->hostDisplay->text().isEmpty())
       {
           QMessageBox messageBox;
           messageBox.critical(0,"Error","Please enter username, password, and display name");
           messageBox.setFixedSize(500,200);
       }
       else
           createHost();
    }
}

void interestData::reverseLowTab()
{
    QObject* button = QObject::sender();

    //just lets us grey out certain tabs that do not need to be used at that time
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
        if (ui->password->echoMode() == QLineEdit::Password)
            ui->password->setEchoMode(QLineEdit::Normal);
        else
            ui->password->setEchoMode(QLineEdit::Password);
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
    if (button == ui->GetVerifiedB)
    {
        Verified* popInstance = new Verified(this);
        popInstance->show();
    }

    if (button == ui->matchB)
    {
        matches* popInstance = new matches(this);
        popInstance->show();

    }
}
//sets the whole application to the default state
void interestData::logout()
{
    ui->tabWidget->setCurrentWidget(ui->tab);
    ui->tabWidget->setTabEnabled(0, true);
    ui->tabWidget->setTabEnabled(1, false);
    ui->tabWidget->setTabEnabled(2, false);
    ui->tabWidget->setTabEnabled(3, false);
    ui->usrName->clear();
    ui->password->clear();
    ui->lineEdit_FN->clear();
    ui->lineEdit_LN->clear();
    ui->newEmail->clear();
    ui->newUsrName->clear();
    ui->newPass->clear();
    ui->confirmPass->clear();
    ui->userNameHostEd->clear();
    ui->passwordHostEd->clear();
    ui->hostDisplay->clear();
    ui->hostBusiness->clear();
    ui->hostBio->clear();
    ui->interestStream->clear();
    ui->eventStream->clear();
}

void interestData::login(QString username, QString password)
{
    // Send request. The ticket will match to the response.
    NetworkObject request(LoginRequest{ username, password });
    mLoginRequest = mNetworkMgr->sendRequest(request);
}

void interestData::createAccount()
{
    CreateAccountRequest data;
    data.username = ui->newUsrName->text();
    data.password = ui->confirmPass->text();
    // the other fields filled out
    data.email = ui->newEmail->text();
    data.firstName = ui->lineEdit_FN->text();
    data.lastName = ui->lineEdit_LN->text();
    if (ui->malebutt->isChecked())
        data.gender = ui->malebutt->text();
    else
        data.gender = ui->febutt->text();

    NetworkObject request(data);
    mCreateAccountRequest = mNetworkMgr->sendRequest(request);
}

void interestData::displayEvents(QVector<base::event> interest)
{
    int temp = 0;
    ui->interestStream->setRowCount(interest.size());
    for (int i = 0; i < interest.size(); i++)
    {
            ui->interestStream->setItem(i, temp, new QTableWidgetItem(interest[i].getName()));
            ui->interestStream->setItem(i, temp+1, new QTableWidgetItem(interest[i].getLocation().getAddress()));
            ui->interestStream->setItem(i, temp+2, new QTableWidgetItem(interest[i].getName()));        //date
            ui->interestStream->setItem(i, temp+3, new QTableWidgetItem(interest[i].getName()));        //time
            ui->interestStream->setItem(i, temp+4, new QTableWidgetItem(interest[i].getDescription()));
    }

}

void interestData::displayMyEvents(QVector<base::event> myEvent)
{
    int temp = 0;
    ui->eventStream->setRowCount(myEvent.size());
    for(int i = 0; i < myEvent.size(); i++)
    {
        ui->eventStream->setItem(i, temp, new QTableWidgetItem(myEvent[i].getName()));
        ui->eventStream->setItem(i, temp+1, new QTableWidgetItem(myEvent[i].getLocation().getAddress()));
        ui->eventStream->setItem(i, temp+2, new QTableWidgetItem(myEvent[i].getName()));            //date
        ui->eventStream->setItem(i, temp+3, new QTableWidgetItem(myEvent[i].getName()));            //time
        ui->eventStream->setItem(i, temp+4, new QTableWidgetItem(myEvent[i].getDescription()));
    }
}

void interestData::createHost()
{
    CreateHostRequest data;
    data.username = ui->userNameHostEd->text();
    data.password = ui->passwordHostEd->text();
    data.displayName = ui->hostDisplay->text();
    data.businessName = ui->hostBusiness->text();
    data.bio = ui->hostBio->toPlainText();

    mCreateHostRequest = mNetworkMgr->sendRequest(NetworkObject(data));
}

void interestData::createEvent(QString eName, QString categories, QString desc, QDateTime start, QDateTime end) {
    CreateEventRequest request;
    request.data.setName(eName);
    if (ui->usrName->text().isEmpty())
        request.data.setHost(ui->userNameHostEd->text());
    else
        request.data.setHost(ui->usrName->text());
    request.data.setDescription(desc);
    request.data.setCategory(categories);
    request.data.setStartTime(start);
    request.data.setEndTime(end);

    mCreateEventRequest = mNetworkMgr->sendRequest(NetworkObject(request));
}

void interestData::requestEvents() {
    SuggestEventsRequest data;
    data.count = 10;

    mSuggestEventsRequest = mNetworkMgr->sendRequest(NetworkObject(data));
}

void interestData::requestMyEvents() {
    // TODO
}

void interestData::checkResponse(NetworkObject response) {
    if (response.getTicket() == mLoginRequest) {
        // Reset ticket
        mLoginRequest = -1;
        // Handle response
        if (response.getPayloadType() == PT_LoginResponse) {
            LoginResponse info = response.convert<LoginResponse>();
            qInfo("authenticated: %d msg: %s", info.valid, qUtf8Printable(info.details));
            if (info.valid && info.isHost)
            {
                ui->tabWidget->setCurrentWidget(ui->tab_4);
                ui->tabWidget->setTabEnabled(2,true);
                ui->tabWidget->setTabEnabled(3, true);
                ui->tabWidget->setTabEnabled(1, false);
            }
            else if (info.valid)
            {
                ui->tabWidget->setCurrentWidget(ui->tab_4);
                ui->tabWidget->setTabEnabled(2, true);
                ui->tabWidget->setTabEnabled(1, false);
            }
            else
            {
                QMessageBox messageBox;
                messageBox.critical(0,"Error","Sorry the username isn't valid");
                messageBox.setFixedSize(500,200);
            }
        }
    }
    else if (response.getTicket() == mCreateAccountRequest) {
        mCreateAccountRequest = -1;
        if (response.getPayloadType() == PT_CreateAccountResponse) {
            CreateAccountResponse info = response.convert<CreateAccountResponse>();
            qInfo("account created: %d msg: %s", info.valid, qUtf8Printable(info.details));
            if (info.valid) {
                ui->tabWidget_2->setTabEnabled(1, true);
                ui->Nam_Display->setText(tr("Alright, %1!").arg(ui->lineEdit_FN->text()));
                ui->tabWidget_2->setCurrentWidget(ui->tab_3);
                ui->tabWidget_2->setTabEnabled(0, false);
            } else {
                QMessageBox messageBox;
                messageBox.critical(0,"Error","Sorry that username is already taken");
                messageBox.setFixedSize(500,200);
            }
        }
    }
    else if (response.getTicket() == mCreateHostRequest) { //will grab events
        mCreateHostRequest = -1;
        if (response.getPayloadType() == PT_CreateHostResponse) {
            CreateHostResponse info = response.convert<CreateHostResponse>();
            qInfo("host created: %d", info.valid);
            if (info.valid) {
                ui->tabWidget->setCurrentWidget(ui->tab_5);	
                ui->tabWidget->setTabEnabled(3, true);
                ui->tabWidget->setTabEnabled(1, false);
            } else {
                QMessageBox messageBox;
                messageBox.critical(0, "Error", "Unable to create host account\nYou must first create a regular account and use THAT username and password for the new host account");
                messageBox.setFixedSize(500, 200);
            }
        }
    }
    else if (response.getTicket() == mCreateEventRequest) {
        mCreateEventRequest = -1;
        if (response.getPayloadType() == PT_CreateEventRequest) {
            CreateEventResponse info = response.convert<CreateEventResponse>();
            qInfo("event created: %d msg %s", info.valid, qUtf8Printable(info.details));
            if (info.valid) {
                QMessageBox messageBox;
                messageBox.information(0, "Success", "Event successfully created!");
                messageBox.setFixedSize(500, 200);
            } else {
                QMessageBox messageBox;
                messageBox.critical(0, "Error", "Unable to create event");
                messageBox.setFixedSize(500, 200);
            }
        }
    }
    else if (response.getTicket() == mSuggestEventsRequest) {
        mSuggestEventsRequest = -1;
        if (response.getPayloadType() == PT_SuggestEventsRequest) {
            SuggestEventsResponse info = response.convert<SuggestEventsResponse>();
            qInfo("events recieved: %d", info.events.count());
            displayEvents(info.events);
        }
    }
}
