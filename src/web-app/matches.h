#ifndef MATCHES_H
#define MATCHES_H

#include <QDialog>

namespace Ui {
class matches;
}

class matches : public QDialog
{
    Q_OBJECT

public:
    explicit matches(QWidget *parent = 0);
    ~matches();

private:
    Ui::matches *ui;
};

#endif // MATCHES_H
