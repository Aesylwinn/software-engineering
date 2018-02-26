#ifndef BASE_TIME_H
#define BASE_TIME_H

#include <string>
#include "baseapp.h"

namespace base {
    /* Implemented by Yianni and Jake */
    class Time {

      public:
    	Time();
    	//void getDate();
    	bool setStartTime(int hour, int minute);
    	bool setEndTime(int hour, int minute);
    	void setAllDay();
    	void setReoccurr(bool o);

    	void getStartTime();
    	void getEndTime();


      private:
    	struct timeInfo{
    		int hour;
    		int minute;
        };

        timeInfo start, end;

    	// need to find out what days you can make it reoccur on
    	// ex: Mon, Wed, Fri, weekly, consecutive, etc.
    	bool reoccurr;
    };
}

#endif
