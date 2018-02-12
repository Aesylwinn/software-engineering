/* Implemented by Yianni and Jake */

#include <iostream>
#include <string>
#include "Time.h"

Time::Time(){
	start.hour = 0;
	start.minute = 0;
	end.hour = 0;
	end.minute = 0;
	reoccurring = false;
}

/*
void Time::getDate(){
	
}
*/

bool Time::setStartTime(int hour, int minute){
	start.hour = hour;
	start.minute = minute;
}

bool Time::setEndTime(int hour, int minute){
// events must be at least 30 minutes long
// 
// if event carries over to the next day, increment the date

	end.hour = hour;
	end.minute = minute;
}

void setReoccurring(bool o){
	reoccurr = o;
}

void setAllDay(){
	start.hour = 0;
	start.minute = 0;
	end.hour = 23;
	end.minute = 59;
}