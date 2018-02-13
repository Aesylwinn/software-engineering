/* Implemented by Yianni and Jake */

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