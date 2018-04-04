#ifndef EVENTTABLEWIDGET_H
#define EVENTTABLEWIDGET_H

#include <QWidget>

#include "../base-app/event.h"

namespace Ui {
class EventTableWidget;
}

class EventTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EventTableWidget(base::event evt, QWidget *parent = 0);
    ~EventTableWidget();

private:
    Ui::EventTableWidget *mUi;
    base::event mEvent;

private slots:
    void onJoinClicked(bool);

signals:
    void onJoinEvent(base::event evt);
};

#endif // EVENTTABLEWIDGET_H
