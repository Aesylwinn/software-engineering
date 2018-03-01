#ifndef EVENTPOPUP_H
#define EVENTPOPUP_H

#include <QDialog>

namespace Ui {
class eventPopUp;
}

class eventPopUp : public QDialog
{
    Q_OBJECT

public:
    explicit eventPopUp(QWidget *parent = 0);
    ~eventPopUp();

public slots:
    void openingCalendar();

private:
    Ui::eventPopUp *ui;
};

#endif // EVENTPOPUP_H
