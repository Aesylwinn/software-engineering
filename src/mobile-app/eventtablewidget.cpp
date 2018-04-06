#include "eventtablewidget.h"
#include "ui_eventtablewidget.h"

EventTableWidget::EventTableWidget(base::Event evt, QWidget *parent)
    : QWidget(parent)
    , mUi(new Ui::EventTableWidget)
    , mEvent(evt)
{
    mUi->setupUi(this);
    mUi->eventName->setText(evt.getName());
    mUi->venueName->setText(evt.getLocation().getName());
    mUi->venueAddress->setText(evt.getLocation().getAddress());
    mUi->description->setText(evt.getDescription());

    connect(mUi->joinButton, &QPushButton::clicked, this, &EventTableWidget::onJoinClicked);
}

EventTableWidget::~EventTableWidget()
{
    delete mUi;
}

void EventTableWidget::onJoinClicked(bool)
{
    emit onJoinEvent(mEvent);
}
