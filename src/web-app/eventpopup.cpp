#include "eventpopup.h"
#include "ui_eventpopup.h"

eventPopUp::eventPopUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::eventPopUp)
{
    ui->setupUi(this);
}

eventPopUp::~eventPopUp()
{
    delete ui;
}
