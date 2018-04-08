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
    QVector<base::UserProfile> uniqueMatches;
    for( int i = 0; i < match.size(); i++ )
    {
        if(!uniqueMatches.contains(match[i]))
        {
            uniqueMatches.push_back(match[i]);
        }
    }

    ui->tableWidget->setRowCount(uniqueMatches.size());
    for (int i = 0; i < uniqueMatches.size(); i++)
    {

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(uniqueMatches[i].getFirstName()+ " " +uniqueMatches[i].getLastName()));
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
