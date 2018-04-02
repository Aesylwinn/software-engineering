#include "mainpage.h"
#include "ui_mainpage.h"

#include <QShowEvent>

#include <exception>

MainPage::MainPage(base::ClientNetworkMgr* mgr, QWidget *parent)
    : QWidget(parent)
    , mUi(new Ui::MainPage)
    , mNetworkMgr(mgr)
    , mSuggestTicket(-1)
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

void MainPage::onResponseReceived(base::NetworkObject obj) {
    switch (obj.getPayloadType()) {
    case base::NetworkObject::PT_SuggestEventsResponse:
        if (obj.getTicket() == mSuggestTicket) {
            // Convert
            base::SuggestEventsResponse info = obj.getSuggestEventsResponse();
            qInfo("suggested events: %d", info.events.count());

            // Update list
            mUi->eventsListView->clear();
            mUi->eventsListView->setRowCount(info.events.count());
            for (int i = 0; i < info.events.count(); ++i) {
                int column = 0;
                mUi->eventsListView->setItem(i, column++, new QTableWidgetItem(info.events[i].getName()));
                mUi->eventsListView->setItem(i, column++, new QTableWidgetItem(info.events[i].getLocation().getAddress()));
                mUi->eventsListView->setItem(i, column++, new QTableWidgetItem(info.events[i].getDescription()));
            }
        }
        break;

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
