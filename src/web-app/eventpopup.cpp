/*Written by Darius and Parker*/
#include "eventpopup.h"
#include "ui_eventpopup.h"
#include "interestdata.h"

eventPopUp::eventPopUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::eventPopUp)
{
    ui->setupUi(this);
    connect(ui->yes, SIGNAL(clicked()), this, SLOT(openingCalendar()));
    connect(ui->no, SIGNAL(clicked()), this, SLOT(openingCalendar()));
    
}



eventPopUp::~eventPopUp()
{
    delete ui;
}

void eventPopUp::openingCalendar()
{
    QObject* button = QObject::sender();
    if (ui->yes == button)
        ui->recurringDate->setEnabled(true);
    else
        ui->recurringDate->setEnabled(false);
}

void eventPopUp::setHostInfo()
{
    interestData *info;
    for(int i = 0; i < 6; i++)
        for(int j = 0; j < 6; j++){
            QString item = ui->category->itemAt(i,y);
        }
    QString item = ui->category->it
    ui->category->isItemSelected()
    info->createEvent(ui->eventName_2->text(), ,ui->descriptionText->toPlainText());
    
    
}
