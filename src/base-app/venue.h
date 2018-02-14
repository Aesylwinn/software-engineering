/* Implemented by Yianni and Jake */

#ifndef BASE_VENUE_H
#define BASE_VENUE_H

#include <string>

class venue{
    public:
        void setAddress(std::string a);
        void setPhoneNumber(int n);
    private:
        std::string address;
        int phoneNumber;
};

#endif
