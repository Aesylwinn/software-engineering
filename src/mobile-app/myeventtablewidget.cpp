#include "myeventtablewidget.h"
#include "ui_myeventtablewidget.h"

MyEventTableWidget::MyEventTableWidget(base::Event evt, QWidget *parent)
    : QWidget(parent)
    , mUi(new Ui::MyEventTableWidget)
    , mEvent(evt)
{
    mUi->setupUi(this);
    mUi->eventName->setText(evt.getName());
    mUi->venueAddress->setText(evt.getLocation().getAddress());
    mUi->description->setText(evt.getDescription());

    connect(mUi->matchButton, &QPushButton::clicked, this, &MyEventTableWidget::onFindMatchClicked);
}

MyEventTableWidget::~MyEventTableWidget()
{
    delete mUi;
}

void MyEventTableWidget::onFindMatchClicked(bool)
{
    emit onFindMatch(mEvent);
}
