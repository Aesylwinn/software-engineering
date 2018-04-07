/*Written by Darius and Parker*/
#ifndef EVENTPOPUP_H
#define EVENTPOPUP_H

#include <QDialog>
#include <QTreeWidgetItem>

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
    void setInterest(QTreeWidgetItem *item, int col);
    void setHostInfo();

private:
    Ui::eventPopUp *ui;
    QString category;
};

#endif // EVENTPOPUP_H
