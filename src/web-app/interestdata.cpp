#include "interestdata.h"
#include "ui_interestdata.h"

interestData::interestData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::interestData)
{
    ui->setupUi(this);
    connect(ui->get_started, SIGNAL(clicked()), this, SLOT(switchTabs()));
}

interestData::~interestData()
{
    delete ui;
}

void interestData::switchTabs()
{
    ui->tabWidget->setCurrentWidget(ui->tab_2);
}
