#ifndef INTERESTDATA_H
#define INTERESTDATA_H

#include <QDialog>

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
    void switchTabs();

private:
    Ui::interestData *ui;
};

#endif // INTERESTDATA_H
