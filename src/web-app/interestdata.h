/*Written by Darius and Parker*/
#ifndef INTERESTDATA_H
#define INTERESTDATA_H

#include <QDialog>
#include "eventpopup.h"
#include "verified.h"
#include "matches.h"

#include "../base-app/clientnetworkmgr.h"

namespace Ui {
class interestData;
}

class interestData : public QDialog
{
    Q_OBJECT

public:
    explicit interestData(QWidget *parent = 0);
    ~interestData();

public slots:
    void switchMainTabs();
    void switchLowTabs();
    void reverseLowTab();
    void togglePassword();
    void popUpWindow();
    void logout();

    void login(QString username, QString password);
    void checkResponse(base::NetworkObject response);
    void createAccount();
    void displayEvents(QVector<base::event> interest);				//will need to have a server function that grabs events from database. I think i wrote a starter struct in
																//networkingobject.h for the events but it might be wrong

private:
    Ui::interestData *ui;
    base::ClientNetworkMgr *mNetworkMgr;
    qint32 mLoginRequest;
	qint32 mCreateAccountRequest;
	//qint32 mEventRequest;
};

#endif // INTERESTDATA_H
