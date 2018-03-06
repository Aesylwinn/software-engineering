/* Implemented by Yianni and Jake */

#include <string>
#include "venue.h"

namespace base {
    venue::venue(QString n, QString addr){
        setName(n);
        setAddress(addr);
        phoneNumber = "867-5309";
        entryFee = 0;
    }
    venue::venue(QString n, QString addr, QString phone){
        setName(n);
        setAddress(addr);
        setPhoneNumber(phone);
        entryFee = 0;
    }
    venue::venue(QString n, QString addr, double fee){
        setName(n);
        setAddress(addr);
        phoneNumber = "867-5309";
        setEntryFee(fee);
    }
    venue::venue(QString n, QString addr, QString phone, double fee){
    }
    venue::venue(QString data){
    }    //conversion constructor

    //utility
    QString venue::toString(){
        return "";
    }

    //setters
    bool venue::setAddress(QString a){
        if (a == NULL)
            return false;
        address = a;
        return true;
    }
    bool venue::setPhoneNumber(QString n){
        if (n == NULL)
            return false;
        phoneNumber = n;
        return true;
    }
    bool venue::setName(QString n){
        if (n = NULL)
            return false;
        name = n;
        return true;
    }
    bool venue::setEntryFee(double f){
        if (f == NULL)
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
 }
