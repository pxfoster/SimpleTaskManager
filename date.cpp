#include "date.h"
#include <regex>


// Name:   Date()
// Desc:   Default constructor.
// Param:  None
// Return: None
Date::Date()
	: month(0), day(0), year(0)
{

}

// Name:   Date(int month, int day, int year)
// Desc:   Constructor that takes in separate integers
//         for month, day, and year.
// Param:  month: An integer representing the month.
//         day:   An integer representing the day.
//         year:  An integer representing the year.
// Return: None
Date::Date(int month, int day, int year)
	: month(month), day(day), year(year)
{
	if (month < 1 || month > 12)
		month = 0;

	if (day < 1 || day > 31)
		day = 0;

	if (year < 1970)
		year = 0;
}

// Name:   Date(string& date)
// Desc:   Constructor that takes in a string for the date.
// Param:  date: A string representing the date.
// Return: None
Date::Date(std::string& date)
{
	if (Date::validateDate(date))
	{
		setMonth(atoi(date.substr(0, 2).c_str()));
		setDay(atoi(date.substr(3, 2).c_str()));
		setYear(atoi(date.substr(6, 4).c_str()));
	}
	else
	{
		month = 0;
		day = 0;
		year = 0;
	}
}

// Name:   setMonth(int month)
// Desc:   Sets a value for the month member.
// Param:  month: An integer representing the month.
// Return: boolean: true if successful, false if not.
bool Date::setMonth(int month)
{
	if (month < 1 || month > 12)
		return false;

	this->month = month;

	return true;
}

// Name:   setDay(int day)
// Desc:   Sets a value for the day member.
// Param:  day: An integer representing the day.
// Return: boolean: true if successful, false if not.
bool Date::setDay(int day)
{
	if (day < 1 || day > 31)
		return false;

	this->day = day;

	return true;
}

// Name:   setYear(int year)
// Desc:   Sets a value for the year member.
// Param:  year: An integer representing the year.
// Return: boolean: true if successful, false if not.
bool Date::setYear(int year)
{
	if (year < 1970)
		return false;

	this->year = year;

	return true;
}

// Name:   getMonth()
// Desc:   Retrieves the value for the month member.
// Param:  None
// Return: month: An integer representing the month.
const int Date::getMonth() const
{
	return month;
}

// Name:   getDay()
// Desc:   Retrieves the value for the day member.
// Param:  None
// Return: day: An integer representing the day.
const int Date::getDay() const
{
	return day;
}

// Name:   getYear()
// Desc:   Retrieves the value for the year member.
// Param:  None
// Return: year: An integer representing the year.
const int Date::getYear() const
{
	return year;
}

// Name:   validateDate(string& date)
// Desc:   Validates a string's format to make sure it is correct for a
//         date. The string can be modified if it is only missing a 0
//         in front of the month or the day.
// Param:  date: A string that holds a date.
// Return: boolean: true if successful, false if not.
bool Date::validateDate(std::string& date)
{
	// Month and day can be only 1 digit, year has to be 4 digits
	if (date.length() < 8)
	{
		return false;
	}
	else if (date.length() == 8)
	{
		// Check if the date length is only 8, add 0 to front of month and front of day
		date.insert(0, 1, '0');
		date.insert(3, 1, '0');
	}
	else if (date.length() == 9)
	{
		// If the length is 9, then check to see
		// if the month or day is missing a 0 in front
		const std::regex number("[0][1-9]");
		if (!std::regex_match(date.substr(0, 2), number))
			date.insert(0, 1, '0');
		else if (!std::regex_match(date.substr(3, 2), number))
			date.insert(3, 1, '0');
	}

	const std::regex dateFormat("(([0][1-9])|([1][0-2]))(/|-)(([0][1-9])|([1-2][0-9])|([3][0-1]))(/|-)(([1][9][7-9][0-9])|([2][0-1][0-9][0-9]))");
	const std::string month = date.substr(0, 2);
	const std::string day = date.substr(3, 2);
	int year = atoi(date.substr(6, 4).c_str());

	// Check date format is mm/dd/yyyy or mm-dd-yyyy
	if (!std::regex_match(date, dateFormat))
		return false;

	// Checking February: See if the year is a leap year first
	if (month == "02")
	{
		if ((year % 100 != 0 && year % 4 == 0) || (year % 100 == 0 && year % 400 == 0))
		{
			if (day > "29")
				return false;
		}
		else if (day > "28")
			return false;
	}

	// Make sure the months with only 30 days does not allow 31
	if (month == "04" || month == "06" || month == "09" || month == "11")
		return false;

	return true;
}
