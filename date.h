#pragma once
#include <string>

/*****************************************************************************
# Description: Custom class for handling dates.
#****************************************************************************/

class Date
{
public:
	static bool validateDate(std::string& date);

	Date();
	Date(int month, int day, int year);
	Date(std::string& date);

	bool setMonth(int month);
	bool setDay(int day);
	bool setYear(int year);

	const int getMonth() const;
	const int getDay() const;
	const int getYear() const;
		
private:
	int month;
	int day;
	int year;
};
