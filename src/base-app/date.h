/* Implemented by Yianni and Jake */

#ifndef BASE_DATE_H
#define BASE_DATE_H

class date{
    public:
        bool setDate(int m, int d, int y);
        bool setTime(int h, int m);
    private:
        int day, month, year, hour, minute;
};

#endif
