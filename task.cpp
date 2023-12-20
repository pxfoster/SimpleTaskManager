#include "task.h"

// Name:   Task(string name, Date& dueDate, bool completed)
// Desc:   Constructor that takes in parameters.
// Param:  name: A string that holds the task name.
//         dueDate: The date that the task is due.
//         completed: A boolean representing if the task is completed.
// Return: None
Task::Task(const std::string name, const Date& dueDate, bool completed)
	: name(name), dueDate(dueDate), completed(completed)
{
}

// Name:   getname()
// Desc:   Retrieve the name of the task.
// Param:  None
// Return: The name member as a constant string.
const std::string& Task::getName() const
{
	return name;
}

// Name:   getDueDate()
// Desc:   Retrieve the due date of the task.
// Param:  None
// Return: The dueDate member as a constant Date object.
const Date& Task::getDueDate() const
{
	return dueDate;
}

// Name:   getCompleted()
// Desc:   Retrieve the completed status of the task.
// Param:  None
// Return: The completed member as a boolean.
bool Task::getCompleted() const
{
	return completed;
}

// Name:   setComplete()
// Desc:   Set the task as completed.
// Param:  None
// Return: None
void Task::setComplete()
{
	completed = true;
}
