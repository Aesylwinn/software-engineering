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
    void displayEvents(QVector<base::Event> interest);
    void displayMyEvents(QVector<base::Event> myEvent);
    void createHost();
    void createEvent(QString eName, QString categories, QString desc, QDateTime start, QDateTime end);
    void getMyInterests();
    void requestEvents();
    void requestMyEvents();
    void findMatches();
    void joiningEvents(int row, int col);

private:
    Ui::interestData *ui;
    base::ClientNetworkMgr *mNetworkMgr;
    QVector<base::event> globalMyEvents;
    QVector<base::event> globalInterest;
    qint32 mLoginRequest;
	qint32 mCreateAccountRequest;
    qint32 mCreateEventRequest;
    qint32 mCreateHostRequest;
    qint32 mSuggestEventsRequest;
    qint32 mJoinEventRequest;
    qint32 mRetrieveMyEvents;
    qint32 mSetInterestsRequest;
    qint32 mFindMatchesRequest;
};

#endif // INTERESTDATA_H
