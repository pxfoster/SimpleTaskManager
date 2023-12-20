#pragma once
#include <string>
#include "date.h"

/*****************************************************************************
# Description: A class that holds information for a task.
#****************************************************************************/

class Task
{
public:
	Task(const std::string name, const Date& dueDate, bool completed = false);

	const std::string& getName() const;
	const Date& getDueDate() const;
	bool getCompleted() const;

	void setComplete();

private:
	std::string name;
	Date dueDate;
	bool completed;
};
