#ifndef BASEAPP_H
#define BASEAPP_H

#include "base-app_global.h"
#include <string>

class BASEAPPSHARED_EXPORT BaseApp
{

public:
    BaseApp();
};

#endif // BASEAPP_H

#ifndef date.h
#define date.h

class date{
    public:
        bool setDate(int m, int d, int y);
        bool setTime(int h, int m);
    private:
        int day, month, year, hour, minute;
}
#endif

#ifndef venue.h
#define venue.h

class venue{
    public
        void setAddress(string a);
        void setPhoneNumber(int ns);
    private:
        string address;
        int phoneNumber;
}
#endif