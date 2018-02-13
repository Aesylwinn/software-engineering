#include "interestdata.h"
#include "ui_interestdata.h"

interestData::interestData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::interestData)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentWidget(ui->tab);
    ui->tabWidget_2->setCurrentWidget(ui->tab_2);
    connect(ui->get_started, SIGNAL(clicked()), this, SLOT(switchMainTabs()));
    connect(ui->Login, SIGNAL(clicked()), this, SLOT(switchLowTabs()));
    connect(ui->SignUp, SIGNAL(clicked()), this, SLOT(switchLowTabs()));
}

interestData::~interestData()
{
    delete ui;
}

void interestData::switchMainTabs()
{
    ui->tabWidget->setCurrentWidget(ui->signUp);
}

void interestData::switchLowTabs()
{
    QObject* button = QObject::sender();

    if(button == ui->Login){
        ui->tabWidget->setCurrentWidget(ui->tab_4);
    }
    else
        ui->tabWidget_2->setCurrentWidget(ui->tab_3);
}
