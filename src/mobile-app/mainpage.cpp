#include "mainpage.h"
#include "ui_mainpage.h"

#include <QMessageBox>
#include <QShowEvent>
#include <exception>

#include "eventtablewidget.h"
#include "myeventtablewidget.h"

MainPage::MainPage(base::ClientNetworkMgr* mgr, QWidget *parent)
    : QWidget(parent)
    , mUi(new Ui::MainPage)
    , mNetworkMgr(mgr)
    , mSuggestTicket(-1)
    , mJoinTicket(-1)
    , mMyEventsTicket(-1)
    , mFindMatchTicket(-1)
{
    if (!mgr) {
        throw std::runtime_error("MainPage requires network mgr");
    } else {
        connect(mgr, &base::ClientNetworkMgr::responseRecieved, this, &MainPage::onResponseReceived);
    }

    mUi->setupUi(this);

    connect(mUi->createEventButton, &QPushButton::clicked, this, &MainPage::onCreateEventClicked);
    connect(mUi->matchesButton, &QPushButton::clicked, this, &MainPage::onViewMatchesClicked);
    connect(mUi->logoutButton, &QPushButton::clicked, this, &MainPage::onLogoutClicked);
    connect(mUi->refreshButton, &QPushButton::clicked, this, &MainPage::onRefreshClicked);
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
    refresh();
}

void MainPage::setMyEvents(QVector<base::Event> events)
{
    // Recreate list
    mUi->myEventsListView->clear();
    for (int i = 0; i < events.count(); ++i) {
        // List item
        MyEventTableWidget* itemWidget = new MyEventTableWidget(events[i]);
        connect(itemWidget, &MyEventTableWidget::onFindMatch, this, &MainPage::onFindMatch);

        // Dummy container
        QListWidgetItem* item = new QListWidgetItem();
        item->setSizeHint(itemWidget->sizeHint());

        mUi->myEventsListView->addItem(item);
        mUi->myEventsListView->setItemWidget(item, itemWidget);
    }
}

void MainPage::setEvents(QVector<base::Event> events)
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
    case base::PT_SuggestEventsResponse:
        if (obj.getTicket() == mSuggestTicket) {
            // Convert
            base::SuggestEventsResponse info = obj.convert<base::SuggestEventsResponse>();
            qInfo("suggested events: %d", info.events.count());

            setEvents(info.events);
        }
        break;

    case base::PT_JoinEventResponse:
        if (obj.getTicket() == mJoinTicket) {
            // Convert
            base::JoinEventResponse info = obj.convert<base::JoinEventResponse>();
            qInfo("join event: %d msg: %s", info.valid, qUtf8Printable(info.details));

            if (info.valid) {
                QMessageBox::information(this, "Success", "Joined event");
            } else {
                QMessageBox::critical(this, "Error", "Failed to join event");
            }
        }
        break;

    case base::PT_RetrieveMyEventsResponse:
        if (obj.getTicket() == mMyEventsTicket) {
            // Convert
            base::RetrieveMyEventsResponse info = obj.convert<base::RetrieveMyEventsResponse>();
            qInfo("my events: %d", info.events.count());

            setMyEvents(info.events);
        }
        break;
    case base::PT_FindMatchResponse:
        if (obj.getTicket() == mFindMatchTicket) {
            // Convert
            base::FindMatchResponse info = obj.convert<base::FindMatchResponse>();
            qInfo("match: %d msg: %s", info.valid, qUtf8Printable(info.details));
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

void MainPage::onViewMatchesClicked(bool)
{
    emit onViewMatches();
}

void MainPage::onRefreshClicked(bool)
{
    refresh();
}

void MainPage::onJoinEvent(base::Event evt)
{
    qInfo("Join event: %s", qUtf8Printable(evt.getName()));
    base::NetworkObject request(base::JoinEventRequest{ evt.getID() });
    mJoinTicket = mNetworkMgr->sendRequest(request);
}

void MainPage::onFindMatch(base::Event evt)
{
    qInfo("Find match: %s", qUtf8Printable(evt.getName()));
    base::NetworkObject request(base::FindMatchRequest{ evt.getID() });
    mFindMatchTicket = mNetworkMgr->sendRequest(request);
}

void MainPage::refresh()
{
    const qint32 NumEvents = 10;
    mSuggestTicket = mNetworkMgr->sendRequest(base::NetworkObject(base::SuggestEventsRequest{ NumEvents }));
    mMyEventsTicket = mNetworkMgr->sendRequest(base::NetworkObject(base::RetrieveMyEventsRequest{ NumEvents }));
}
