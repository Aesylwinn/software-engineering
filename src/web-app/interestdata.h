#ifndef INTERESTDATA_H
#define INTERESTDATA_H

#include <QDialog>

namespace Ui {
class InterestData;
}

class InterestData : public QDialog
{
    Q_OBJECT

public:
    explicit InterestData(QWidget *parent = 0);
    ~InterestData();

private:
    Ui::InterestData *ui;
};

#endif // INTERESTDATA_H
