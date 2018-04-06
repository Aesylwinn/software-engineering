#ifndef MATCHESPAGE_H
#define MATCHESPAGE_H

#include <QWidget>

#include "../base-app/clientnetworkmgr.h"

namespace Ui {
class MatchesPage;
}

class MatchesPage : public QWidget
{
    Q_OBJECT

public:
    explicit MatchesPage(base::ClientNetworkMgr* mgr, QWidget *parent = 0);
    ~MatchesPage();

private:
    void showEvent(QShowEvent* event) override;
    void setMatches(QVector<base::UserProfile> profiles, QVector<base::Event> events);

    Ui::MatchesPage *mUi;
    base::ClientNetworkMgr* mNetworkMgr;

    qint32 mMatchesTicket;

private slots:
    void onBackClicked(bool);
    void onResponse(base::NetworkObject obj);

signals:
    void onBack();
};

#endif // MATCHESPAGE_H
