/*Written by Darius and Parker*/
#ifndef VERIFIED_H
#define VERIFIED_H

#include <QDialog>

namespace Ui {
class Verified;
}

/*Written by Darius and Parker*/
class Verified : public QDialog
{
    Q_OBJECT

public:
    explicit Verified(QWidget *parent = 0);
    ~Verified();

private:
    Ui::Verified *ui;
};

#endif // VERIFIED_H
