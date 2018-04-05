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
    interestData *info = new interestData(this);
    QString categories;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 5; j++){
            if(ui->category->itemAt(i,j)->isSelected())
            {
                categories = ui->category->itemAt(i,j)->text(i);
            }
        }

    info->createEvent(ui->eventNameEd->text(), categories ,ui->descriptionText->toPlainText(), ui->fromDate->dateTime(), ui->toDate->dateTime());
}
