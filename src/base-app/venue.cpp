/* Implemented by Yianni and Jake */

#include "venue.h"

namespace base {
    venue::venue(){
        initialize("", "", "", -1);
    }
    venue::venue(QString n, QString addr, QString phone, double fee){
        initialize(n, addr, phone, fee);
    }
    venue::venue(QString data){ //Data means "name,address,phone,fee"
        QStringList theList = data.split(",");
        setName(theList[0]);
        setAddress(theList[1]);
        setPhoneNumber(theList[2]);
        setEntryFee(theList[3].toDouble());
    }    //conversion constructor

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

    venue venue::operator=(const QString& data){ //data = "name,address,phone,fee"
        venue newVenue(data);
        setName(newVenue.getName());
        setAddress(newVenue.getAddress());
        setPhoneNumber(newVenue.getPhoneNumber());
        setEntryFee(newVenue.getEntryFee());
        return *this;
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
