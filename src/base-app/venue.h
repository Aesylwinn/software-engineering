/* Implemented by Yianni and Anthony */

#ifndef BASE_VENUE_H
#define BASE_VENUE_H

#include <QString>
#include <QStringList>

#include "base-app_global.h"

namespace base {
    class BASEAPPSHARED_EXPORT venue{
        public:
            venue();
            venue(QString n, QString addr, QString phone, double fee);
            venue(QString data);    //conversion constructor

            //utility
            QString toString();

            //setters
            bool setAddress(QString a);
            bool setPhoneNumber(QString n);
            bool setName(QString n);
            bool setEntryFee(double f);

            //getters
            QString getAddress() const;
            QString getPhoneNumber() const;
            QString getName() const;
            double getEntryFee() const;

            venue operator=(const QString& data);
            bool operator==(const venue &rhs) const;
        private:
            QString name;
            QString address;
            QString phoneNumber;
            double entryFee;
            void initialize(QString n, QString addr, QString phone, double fee);
    };
}

#endif
