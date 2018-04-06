#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>

#include "../base-app/clientnetworkmgr.h"

namespace Ui {
class MainPage;
}

class MainPage : public QWidget
{
    Q_OBJECT

public:
    explicit MainPage(base::ClientNetworkMgr* mgr, QWidget *parent = 0);
    ~MainPage();

private:
    void showEvent(QShowEvent* event) override;

    void setMyEvents(QVector<base::Event> events);
    void setEvents(QVector<base::Event> events);

    Ui::MainPage *mUi;
    base::ClientNetworkMgr* mNetworkMgr;

    qint32 mSuggestTicket;
    qint32 mJoinTicket;
    qint32 mMyEventsTicket;
    qint32 mFindMatchTicket;

private slots:
    void onResponseReceived(base::NetworkObject obj);

    void onCreateEventClicked(bool);
    void onLogoutClicked(bool);
    void onViewMatchesClicked(bool);

    void onJoinEvent(base::Event evt);
    void onFindMatch(base::Event evt);

signals:
    void onCreateEvent();
    void onViewMatches();
    void onLogout();
};

#endif // MAINPAGE_H
