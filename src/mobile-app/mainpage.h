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

    void setMyEvents(QVector<base::event> events);
    void setEvents(QVector<base::event> events);

    Ui::MainPage *mUi;
    base::ClientNetworkMgr* mNetworkMgr;

    qint32 mSuggestTicket;
    qint32 mJoinTicket;

private slots:
    void onResponseReceived(base::NetworkObject obj);
    void onCreateEventClicked(bool);
    void onLogoutClicked(bool);
    void onJoinEvent(base::event evt);

signals:
    void onCreateEvent();
    void onLogout();
};

#endif // MAINPAGE_H
