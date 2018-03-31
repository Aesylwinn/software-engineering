#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>

#include "../base-app/clientnetworkmgr.h"

namespace Ui {
class LoginPage;
}

class LoginPage : public QWidget
{
    Q_OBJECT

public:
    explicit LoginPage(base::ClientNetworkMgr* mgr, QWidget *parent = 0);
    ~LoginPage();

private:
    Ui::LoginPage *mUi;
    base::ClientNetworkMgr* mNetworkMgr;

private slots:
    void onLoginClicked(bool);
    void onRegisterClicked(bool);

signals:
    void onSuccess();
    void onRegister();
};

#endif // LOGINPAGE_H
