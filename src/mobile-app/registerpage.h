#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include <QWidget>

namespace Ui {
class RegisterPage;
}

class RegisterPage : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterPage(QWidget *parent = 0);
    ~RegisterPage();

private:
    Ui::RegisterPage *ui;
private slots:
    void onRegisterClicked(bool checked);
signals:
    void onSuccess();
    void onCanceled();
};

#endif // REGISTERPAGE_H
