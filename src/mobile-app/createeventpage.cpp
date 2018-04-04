#include "createeventpage.h"
#include "ui_createeventpage.h"

#include <exception>

#include <QMessageBox>

CreateEventPage::CreateEventPage(base::ClientNetworkMgr* mgr, QWidget *parent)
    : QWidget(parent)
    , mUi(new Ui::CreateEventPage)
    , mNetworkMgr(mgr)
    , mCreateEventTicket(-1)
{
    if (!mgr) {
        throw std::runtime_error("CreateEventPage requires network mgr");
    } else {
        connect(mgr, &base::ClientNetworkMgr::responseRecieved, this, &CreateEventPage::onResponseReceived);
    }

    mUi->setupUi(this);

    connect(mUi->submitButton, &QPushButton::clicked, this, &CreateEventPage::onSubmitClicked);
    connect(mUi->cancelButton, &QPushButton::clicked, this, &CreateEventPage::onCancelClicked);
}

CreateEventPage::~CreateEventPage()
{
    delete mUi;
}

void CreateEventPage::onResponseReceived(base::NetworkObject response)
{
    switch (response.getPayloadType()) {
    case base::PT_CreateEventResponse:
        if (response.getTicket() == mCreateEventTicket) {
            base::CreateEventResponse info = response.convert<base::CreateEventResponse>();
            qInfo("create event: %d msg: %s", info.valid, qUtf8Printable(info.details));

            if (info.valid) {
                emit onSuccess();
                hide();
            } else {
                QMessageBox messageBox;
                messageBox.critical(this, "Error", "Unable to create the event");
            }
        }
        break;

    default:
        // Do nothing
        break;
    }
}

void CreateEventPage::onSubmitClicked(bool)
{
    base::CreateEventRequest request;
    base::venue venue;

    request.data.setName(mUi->nameField->text());
    request.data.setCategory(mUi->categoryField->text());

    venue.setName(mUi->venueNameField->text());
    venue.setAddress(mUi->venueAddressField->text());
    venue.setPhoneNumber(mUi->venuePhoneField->text());
    request.data.setLocation(venue);

    request.data.setDescription(mUi->descriptionField->toPlainText());

    mCreateEventTicket = mNetworkMgr->sendRequest(base::NetworkObject(request));
}

void CreateEventPage::onCancelClicked(bool)
{
    emit onCanceled();
    hide();
}
