#ifndef INTERESTDATA_H
#define INTERESTDATA_H

#include <QDialog>
#include "eventpopup.h"
#include "verified.h"

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

private:
    Ui::interestData *ui;
};

#endif // INTERESTDATA_H
