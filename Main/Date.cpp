#include "stdafx.h"
#include "Date.h"
#include <time.h>
#include <sstream>

Date::Date()
{
	time_t ctime = time(0);
	tm tim = *localtime(&ctime);
	this->day = tim.tm_mday;
	this->month = tim.tm_mon;
	this->year = tim.tm_year;	
}

std::string Date::getBDate()
{
	std::stringstream strDate;
	strDate << (year + 1990) << "/" << (month + 1) << "/" << day;
	return strDate.str();
}

std::string Date::getRDate()
{
	int rMonth = month + 2;
	if (rMonth == 13)
	{
		year += 1;
		rMonth = 1;
	}
	std::stringstream strDate;
	strDate << (year + 1990) << "/" << rMonth << "/" << day;
	return strDate.str();
}
