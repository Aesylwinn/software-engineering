/* Implemented by Yianni and Jake */

#include <QVector>
#include <QStringList>
#include <QDebug> // for iterator
#include "venue.h"

namespace base {
    venue::venue(){
        initialize("", "", "", -1);
    }
    venue::venue(QString n, QString addr){
        initialize(n, addr, "", -1);
    }
    venue::venue(QString n, QString addr, QString phone){
        initialize(n, addr, phone, -1);
    }
    venue::venue(QString n, QString addr, double fee){
        initialize(n, addr, "", fee);
    }
    venue::venue(QString n, QString addr, QString phone, double fee){
        initialize(n, addr, phone, fee);
    }
    venue::venue(QString data){
        // assumes data == "name, address, phone, fee" in order
        initialize("", "", "", -1);

        QStringList list = data.split(',');
        int i = 0;
        for(QStringList::iterator it = list.begin(); it != list.end(); it++) {
            QString temp = *it;
            temp = temp.simplified();
            switch(i++) {
                case 0: name = temp;
                case 1: address = temp;
                case 2: phoneNumber = temp;
                case 3: entryFee = temp.toDouble();
            }
        }
    }   //conversion constructor

    //utility
    QString venue::toString(){
        return name;
    }

    //setters
    bool venue::setAddress(QString a){
        if (a.isEmpty())
            return false;
        address = a;
        return true;
    }
    bool venue::setPhoneNumber(QString n){
        if (n.isEmpty())
            return false;
        phoneNumber = n;
        return true;
    }
    bool venue::setName(QString n){
        if (n.isEmpty())
            return false;
        name = n;
        return true;
    }
    bool venue::setEntryFee(double f){
        if (f < 0)
            return false;
        entryFee = f;
        return true;
    }

    //getters
    QString venue::getAddress(){
        return address;
    }
    QString venue::getPhoneNumber(){
        return phoneNumber;
    }
    QString venue::getName(){
        return name;
    }
    double venue::getEntryFee(){
        return entryFee;
    }

    //helper class
    void venue::initialize(QString n, QString addr, QString phone, double fee){
        if (n.isEmpty())
                name = "";
        else
            setName(n);
        if (addr.isEmpty())
            addr = "";
        else
            setAddress(addr);
        if (phone.isEmpty())
            phoneNumber = "867-5309";
        else
            setPhoneNumber(phone);
        if (fee < 0)
            entryFee = 0;
        else
            setEntryFee(fee);
    }
 }
