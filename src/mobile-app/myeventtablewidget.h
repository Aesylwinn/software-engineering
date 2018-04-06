#ifndef MYEVENTTABLEWIDGET_H
#define MYEVENTTABLEWIDGET_H

#include <QWidget>

#include "../base-app/event.h"

namespace Ui {
class MyEventTableWidget;
}

class MyEventTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyEventTableWidget(base::Event evt, QWidget *parent = 0);
    ~MyEventTableWidget();

private:
    Ui::MyEventTableWidget *mUi;
    base::Event mEvent;

private slots:
    void onFindMatchClicked(bool);

signals:
    void onFindMatch(base::Event event);
};

#endif // MYEVENTTABLEWIDGET_H
