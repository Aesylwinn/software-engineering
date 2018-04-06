#ifndef MATCHES_H
#define MATCHES_H

#include <QDialog>
#include "../base-app/clientnetworkmgr.h"

namespace Ui {
class matches;
}

class matches : public QDialog
{
    Q_OBJECT

public:
    explicit matches(QWidget *parent, base::ClientNetworkMgr * mgi);
    ~matches();

public slots:
    void displayMatches(QVector<base::UserProfile> match, QVector<base::Event> event);
    void findMatches();

private slots:
    void onResponse(base::NetworkObject obj);

private:
    Ui::matches *ui;
    qint32 requestTicket;
    base::ClientNetworkMgr* networkMgr;
};

#endif // MATCHES_H
