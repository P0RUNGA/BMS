#pragma once
#ifndef __DATE_H__
#define __DATE_H__
#include <string>

class Date
{
public:
	int day;
	int month;
	int year;
	Date();
	std::string getBDate();
	std::string getRDate();
};

#endif	//__DATE_H__
