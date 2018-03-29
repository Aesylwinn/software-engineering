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
    QVector<QString> categories;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 5; j++){
            QString item = ui->category->itemAt(i,j)->text(i);
            categories.push_front(item);
        }

    info->createEvent(ui->eventNameEd->text(), categories ,ui->descriptionText->toPlainText());
    
    
}
