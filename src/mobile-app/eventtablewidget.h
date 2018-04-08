#ifndef EVENTTABLEWIDGET_H
#define EVENTTABLEWIDGET_H

#include <QWidget>

#include "../base-app/event.h"

namespace Ui {
class EventTableWidget;
}

/* Implemented by Kyle and Darius */
class EventTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EventTableWidget(base::Event evt, QWidget *parent = 0);
    ~EventTableWidget();

private:
    Ui::EventTableWidget *mUi;
    base::Event mEvent;

private slots:
    void onJoinClicked(bool);

signals:
    void onJoinEvent(base::Event evt);
};

#endif // EVENTTABLEWIDGET_H
