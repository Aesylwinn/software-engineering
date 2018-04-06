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
    if (evt->spontaneous())
        return;

    mMatchesTicket = mNetworkMgr->sendRequest(base::NetworkObject(base::RetrieveMatchesRequest{}));
}

void MatchesPage::setMatches(QVector<base::UserProfile> profiles, QVector<base::Event> events)
{
    // Update list of matches
    mUi->matchesList->clear();
    for (int i = 0; i < profiles.size() && i < events.size(); ++i) {
        // List entry
        MatchItemWidget* itemWidget = new MatchItemWidget(profiles[i], events[i]);
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
