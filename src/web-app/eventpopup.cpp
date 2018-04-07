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
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(setHostInfo()));

    ui->fromDate->setDateTime(QDateTime::currentDateTime());
    ui->toDate->setDateTime(QDateTime::currentDateTime());
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
    interestData *info = (interestData*)parent();
    QString categories = "Fun";
    base::Event tempEvent;
    base::venue tempVenue;
    // TODO: fix this
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++){
            if(ui->category->itemAt(i,j)->isSelected())
            {
                categories = ui->category->itemAt(i,j)->text(i);
            }
        }
    tempEvent.setName(ui->eventNameEd->text());
    tempEvent.setDescription(ui->descriptionText->toPlainText());
    tempEvent.setCategory(categories);
    tempEvent.setStartTime(ui->fromDate->dateTime());
    tempEvent.setEndTime(ui->toDate->dateTime());
    tempVenue.setAddress(ui->eventAddressEd->text());
    tempVenue.setPhoneNumber(ui->eventPhoneEd->text());
    tempEvent.setLocation(tempVenue);

    info->createEvent(tempEvent);
}
