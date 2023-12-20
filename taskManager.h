#pragma once
#include "task.h"

/*****************************************************************************
# Description: A node structure for use with a linked list.
               The TaskManager class handles operations for a
			   linked list of tasks.
#****************************************************************************/

struct Node
{
	Node(std::string name, const Date& dueDate, bool completed)
		: task(name, dueDate, completed), next(nullptr)
	{
	}

	Task task;
	Node* next;
};

class TaskManager
{
public:
	TaskManager();
	TaskManager(const TaskManager& origTaskManager);
	const TaskManager& operator=(const TaskManager& origTaskManager);
	~TaskManager();

	void emptyTasks();
	bool addTask(const std::string& name, const Date& dueDate);
	bool deleteTask(int taskNum);
	void completeTask(int taskNum);
	int getNumTasks() const;
	const Node* getTasks() const;
	bool loadFromFile(const std::string& fileName);
	bool saveToFile(const std::string& fileName) const;
	bool checkFileExists(const std::string& fileName);

private:
	void addTask(const std::string& name, const Date& dueDate, bool completed);
	Task* getTaskNodeByNum(int taskNum);

	Node* head;
	int numNodes;
};
