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
    connect(ui->category, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(setInterest(QTreeWidgetItem*,int)));

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

void eventPopUp::setInterest(QTreeWidgetItem *item, int col)
{
    if(item->checkState(col) == Qt::Checked)
        category = item->text(col);
}

void eventPopUp::setHostInfo()
{
    interestData *info = (interestData*)parent();
    base::Event tempEvent;
    base::venue tempVenue;

    tempEvent.setName(ui->eventNameEd->text());
    tempEvent.setDescription(ui->descriptionText->toPlainText());
    tempEvent.setCategory(category);
    tempEvent.setStartTime(ui->fromDate->dateTime());
    tempEvent.setEndTime(ui->toDate->dateTime());
    tempVenue.setAddress(ui->eventAddressEd->text());
    tempVenue.setPhoneNumber(ui->eventPhoneEd->text());
    tempEvent.setLocation(tempVenue);

    info->createEvent(tempEvent);
}
