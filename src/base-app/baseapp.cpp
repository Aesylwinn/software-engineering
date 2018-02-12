#include "baseapp.h"


BaseApp::BaseApp()
{
}

bool date::setDate(int m, int d, int y){
    bool validDate = true;
    if (y >= 0)
        year = y;
    else
        validDate = false;
    if (m > 0 && m < 13)
        month = m;
    else
        validDate = false;
    if (m == 1 || m == 3 || m == 5 || m == 7 || m ==8 || m == 10 || m == 12){
        if (d > 0 && d < 32)
            day = d;
    }
    else if(m == 4 || m == 6 || m ==9 || m == 11){
        if (d > 0 && d < 31)
            day = d;
    }
    else if (m == 2){
        if (y % 4 == 0) //if its a leap year
        {
            if (d > 0 && d < 30)
                day = d;
        }
        else
            if (d > 0 && d < 29)
                day = d;
    }
    else
        validDate = false;
        
    return validDate;
    
}
bool date::setTime(int h, int m){
    bool validTime = true;
    if (h > 0 && h < 25)
        hour = h;
    else
        validTime = false;
    if (m >= 0 && m < 60)
        minute = m;
    else
        validTime = false;
    return validTime;
}

void venue::setAddress(std::string a){
    address = a;
}
void venue::setPhoneNumber(int n){
    phoneNumber = n;
}

