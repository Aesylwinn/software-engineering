#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include <QWidget>

#include "../base-app/clientnetworkmgr.h"

namespace Ui {
class RegisterPage;
}

class RegisterPage : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterPage(base::ClientNetworkMgr* mgr, QWidget *parent = 0);
    ~RegisterPage();

private:
    Ui::RegisterPage *mUi;
    base::ClientNetworkMgr* mNetworkMgr;

private slots:
    void onRegisterClicked(bool checked);
    void onResponseRecieved(base::NetworkObject response);

signals:
    void onSuccess();
    void onCanceled();
};

#endif // REGISTERPAGE_H