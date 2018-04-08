#include "matchespage.h"
#include "ui_matchespage.h"

#include <QShowEvent>

#include "matchitemwidget.h"

MatchesPage::MatchesPage(base::ClientNetworkMgr* mgr, QWidget *parent)
    : QWidget(parent)
    , mUi(new Ui::MatchesPage)
    , mNetworkMgr(mgr)
    , mMatchesTicket(-1)
{
    mUi->setupUi(this);

    connect(mNetworkMgr, &base::ClientNetworkMgr::responseRecieved, this, &MatchesPage::onResponse);
    connect(mUi->backButton, &QPushButton::clicked, this, &MatchesPage::onBackClicked);
}

MatchesPage::~MatchesPage()
{
    delete mUi;
}

void MatchesPage::showEvent(QShowEvent *evt)
{
    mMatchesTicket = mNetworkMgr->sendRequest(base::NetworkObject(base::RetrieveMatchesRequest{}));
}

void MatchesPage::setMatches(QVector<base::UserProfile> profiles, QVector<base::Event> events)
{
    QVector<base::UserProfile> uniqueMatches;
    QVector<base::Event> uniqueEvents;
    for( int i = 0; i < events.size(); i++ )
    {
        if(!uniqueEvents.contains(events[i]))
        {
            uniqueMatches.push_back(profiles[i]);
            uniqueEvents.push_back(events[i]);
        }
    }

    // Update list of matches
    mUi->matchesList->clear();
    for (int i = 0; i < uniqueMatches.size() && i < uniqueEvents.size(); ++i) {
        // List entry
        MatchItemWidget* itemWidget = new MatchItemWidget(uniqueMatches[i], uniqueEvents[i]);
        // Dummy container
        QListWidgetItem* item = new QListWidgetItem();
        item->setSizeHint(itemWidget->sizeHint());

        mUi->matchesList->addItem(item);
        mUi->matchesList->setItemWidget(item, itemWidget);
    }
}

void MatchesPage::onBackClicked(bool)
{
    emit onBack();
    hide();
}

void MatchesPage::onResponse(base::NetworkObject obj)
{
    switch (obj.getPayloadType()) {
    case base::PT_RetrieveMatchesResponse:
        if (obj.getTicket() == mMatchesTicket) {
            auto response = obj.convert<base::RetrieveMatchesResponse>();
            qInfo("current matches: %d", response.matches.count());

            setMatches(response.matches, response.events);
        }
        break;
    default:
        // Do nothing
        break;
    }
}
