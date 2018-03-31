#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>

namespace Ui {
class LoginPage;
}

class LoginPage : public QWidget
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = 0);
    ~LoginPage();

private:
    Ui::LoginPage *ui;
private slots:
    void onLoginClicked(bool);
    void onRegisterClicked(bool);
signals:
    void onSuccess();
    void onRegister();
};

#endif // LOGINPAGE_H
