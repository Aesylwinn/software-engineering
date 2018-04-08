#ifndef CREATEEVENTPAGE_H
#define CREATEEVENTPAGE_H

#include <QWidget>

#include "../base-app/clientnetworkmgr.h"

namespace Ui {
class CreateEventPage;
}

/* Implemented by Darius and Kyle */
class CreateEventPage : public QWidget
{
    Q_OBJECT

public:
    explicit CreateEventPage(base::ClientNetworkMgr* mgr, QWidget *parent = 0);
    ~CreateEventPage();

private:
    Ui::CreateEventPage *mUi;
    base::ClientNetworkMgr* mNetworkMgr;

    qint32 mCreateEventTicket;

private slots:
    void onResponseReceived(base::NetworkObject response);
    void onSubmitClicked(bool);
    void onCancelClicked(bool);

signals:
    void onSuccess();
    void onCanceled();
};

#endif // CREATEEVENTPAGE_H
