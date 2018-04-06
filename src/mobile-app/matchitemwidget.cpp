#include "matchitemwidget.h"
#include "ui_matchitemwidget.h"

MatchItemWidget::MatchItemWidget(base::UserProfile profile, base::Event evt, QWidget *parent)
    :QWidget(parent)
    , mUi(new Ui::MatchItemWidget)
{
    mUi->setupUi(this);
    mUi->userName->setText(profile.getFirstName() + " " + profile.getLastName());
    mUi->eventName->setText(evt.getName());
}

MatchItemWidget::~MatchItemWidget()
{
    delete mUi;
}
