/* Implemented by Yianni and Jake */

#ifndef venue.h
#define venue.h

#include <string>

class venue{
    public
        void setAddress(string a);
        void setPhoneNumber(int n);
    private:
        string address;
        int phoneNumber;
}
#endif