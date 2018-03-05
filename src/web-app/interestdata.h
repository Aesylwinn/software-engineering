/*Written by Darius and Parker*/
#ifndef INTERESTDATA_H
#define INTERESTDATA_H

#include <QDialog>
#include "eventpopup.h"
#include "verified.h"

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
    //void sendAccount();
    //void grabFromDatabase();
    //void verifyAccount();

    void login(QString username, QString password);
    void checkResponse(base::NetworkObject response);

private:
    Ui::interestData *ui;
    base::ClientNetworkMgr *mNetworkMgr;
    qint32 mLoginRequest;
};

#endif // INTERESTDATA_H
