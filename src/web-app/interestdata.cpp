#include "interestdata.h"
#include "ui_interestdata.h"

InterestData::InterestData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InterestData)
{
    ui->setupUi(this);
}

InterestData::~InterestData()
{
    delete ui;
}
