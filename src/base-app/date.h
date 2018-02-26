#ifndef BASE_DATE_H
#define BASE_DATE_H

namespace base {
    /* Implemented by Yianni and Jake */
    class date{
        public:
            bool setDate(int m, int d, int y);
            bool setTime(int h, int m);
        private:
            int day, month, year, hour, minute;
    };
}

#endif
