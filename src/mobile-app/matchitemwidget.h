#ifndef MATCHITEMWIDGET_H
#define MATCHITEMWIDGET_H

#include <QWidget>

#include "../base-app/event.h"
#include "../base-app/userprofile.h"

namespace Ui {
class MatchItemWidget;
}

class MatchItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MatchItemWidget(base::UserProfile profile, base::Event evt, QWidget *parent = 0);
    ~MatchItemWidget();

private:
    Ui::MatchItemWidget *mUi;
    base::UserProfile mProfile;
    base::Event mEvent;
};

#endif // MATCHITEMWIDGET_H
