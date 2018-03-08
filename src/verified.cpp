/*Written by Darius and Parker*/
#include "verified.h"
#include "ui_verified.h"


Verified::Verified(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Verified)
{
    ui->setupUi(this);

}

Verified::~Verified()
{
    delete ui;
}
