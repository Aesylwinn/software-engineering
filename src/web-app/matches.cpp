/* Written by Parker and Darius */
#include "matches.h"
#include "ui_matches.h"

matches::matches(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::matches)
{
    ui->setupUi(this);
}

matches::~matches()
{
    delete ui;
}
