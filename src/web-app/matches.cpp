/* Written by Parker and Darius */
#include "matches.h"
#include "ui_matches.h"

matches::matches(QWidget *parent, base::ClientNetworkMgr*mgi) :
    QDialog(parent),
    ui(new Ui::matches),networkMgr(mgi)
{
    connect(networkMgr, &base::ClientNetworkMgr::responseRecieved, this, &matches::onResponse);
    findMatches();
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(findMatches()));
}

matches::~matches()
{
    delete ui;
}

void matches::displayMatches(QVector<base::UserProfile> match, QVector<base::Event> event)
{
    ui->tableWidget->setRowCount(match.size());
    for (int i = 0; i < match.size(); i++)
    {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(match[i].getFirstName()+ " " +match[i].getLastName()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(event[i].getName()));
    }
}

void matches::findMatches()
{
    base::RetrieveMatchesRequest data = {};
    requestTicket = networkMgr->sendRequest(base::NetworkObject(data));
}

void matches::onResponse(base::NetworkObject obj)
{
    switch (obj.getPayloadType()) {
    case base::PT_RetrieveMatchesResponse:
        if (obj.getTicket() == requestTicket)
        {
            auto info = obj.convert<base::RetrieveMatchesResponse>();
            displayMatches(info.matches, info.events);
        }
        break;
    default:
        break;
    }
}
