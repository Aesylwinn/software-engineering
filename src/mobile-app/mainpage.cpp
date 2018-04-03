#include "mainpage.h"
#include "ui_mainpage.h"

#include <QMessageBox>
#include <QShowEvent>
#include <exception>

#include "eventtablewidget.h"

MainPage::MainPage(base::ClientNetworkMgr* mgr, QWidget *parent)
    : QWidget(parent)
    , mUi(new Ui::MainPage)
    , mNetworkMgr(mgr)
    , mSuggestTicket(-1)
    , mJoinTicket(-1)
{
    if (!mgr) {
        throw std::runtime_error("MainPage requires network mgr");
    } else {
        connect(mgr, &base::ClientNetworkMgr::responseRecieved, this, &MainPage::onResponseReceived);
    }

    mUi->setupUi(this);

    connect(mUi->createEventButton, &QPushButton::clicked, this, &MainPage::onCreateEventClicked);
    connect(mUi->logoutButton, &QPushButton::clicked, this, &MainPage::onLogoutClicked);
}

MainPage::~MainPage()
{
    delete mUi;
}

void MainPage::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);

    if (event->spontaneous())
        return;

    // Update list of events
    const qint32 NumEvents = 10;
    mSuggestTicket = mNetworkMgr->sendRequest(base::NetworkObject(base::SuggestEventsRequest{ NumEvents }));
}

void MainPage::setMyEvents(QVector<base::event> events)
{
    // TODO
}

void MainPage::setEvents(QVector<base::event> events)
{
    // Update list
    mUi->eventListView->clear();
    for (int i = 0; i < events.count(); ++i) {
        // List item
        EventTableWidget* itemWidget = new EventTableWidget(events[i]);
        connect(itemWidget, &EventTableWidget::onJoinEvent, this, &MainPage::onJoinEvent);

        // Dummy container
        QListWidgetItem* item = new QListWidgetItem();
        item->setSizeHint(itemWidget->sizeHint());

        // Add to list
        mUi->eventListView->addItem(item);
        mUi->eventListView->setItemWidget(item, itemWidget);
    }
}

void MainPage::onResponseReceived(base::NetworkObject obj) {
    switch (obj.getPayloadType()) {
    case base::NetworkObject::PT_SuggestEventsResponse:
        if (obj.getTicket() == mSuggestTicket) {
            // Convert
            base::SuggestEventsResponse info = obj.getSuggestEventsResponse();
            qInfo("suggested events: %d", info.events.count());

            setEvents(info.events);
        }
        break;

    case base::NetworkObject::PT_JointEventResponse:
        if (obj.getTicket() == mJoinTicket) {
            // Convert
            base::JoinEventResponse info = obj.getJoinEventResponse();
            qInfo("join event: %d msg: %s", info.valid, qUtf8Printable(info.details));

            if (info.valid) {
                QMessageBox::information(this, "Success", "Joined event");
            } else {
                QMessageBox::critical(this, "Error", "Failed to join event");
            }
        }

    default:
        // Do nothing
        break;
    }
}

void MainPage::onCreateEventClicked(bool) {
    emit onCreateEvent();
}

void MainPage::onLogoutClicked(bool) {
    emit onLogout();
    hide();
}

void MainPage::onJoinEvent(base::event evt)
{
    qInfo("Join event: %s", qUtf8Printable(evt.getName()));
    base::NetworkObject request(base::JoinEventRequest{ evt.getID() });
    mJoinTicket = mNetworkMgr->sendRequest(request);
}
