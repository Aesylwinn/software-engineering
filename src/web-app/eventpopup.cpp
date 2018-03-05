/*Written by Darius and Parker*/
#include "eventpopup.h"
#include "ui_eventpopup.h"

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
