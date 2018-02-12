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

#ifndef date_h
#define date_h

class date{
    public:
        bool setDate(int m, int d, int y);
        bool setTime(int h, int m);
    private:
        int day, month, year, hour, minute;
};
#endif

#ifndef venue_h
#define venue_h

class venue{
    public:
        void setAddress(std::string a);
        void setPhoneNumber(int ns);
    private:
        std::string address;
        int phoneNumber;
};
#endif
