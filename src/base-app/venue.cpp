/* Implemented by Yianni and Jake */

#include <string>
#include "venue.h"

namespace base {
    venue::venue(QString n, QString addr){
    }
    venue::venue(QString n, QString addr, QString phone){
    }
    venue::venue(QString n, QString addr, double fee){
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
        return true;
    }
    bool venue::setPhoneNumber(QString n){
        return true;
    }
    bool venue::setName(QString n){
        return true;
    }
    bool venue::setEntryFee(double f){
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
