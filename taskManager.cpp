#include "taskManager.h"
#include <fstream>
#include <filesystem>

// Name:   TaskManager()
// Desc:   Default constructor.
// Param:  None
// Return: None
TaskManager::TaskManager()
{
	head = nullptr;
	numNodes = 0;
}

// Name:   TaskManager(TaskManager& origTaskManager)
// Desc:   Copy constructor.
// Param:  origTaskManager: A reference to a TaskManager object.
// Return: None
TaskManager::TaskManager(const TaskManager& origTaskManager)
{
	head = nullptr;
	numNodes = 0;

	*this = origTaskManager;
}

// Name:   operator=()
// Desc:   Allow the TaskManager class to use the assignment operator.
// Param:  origTaskmanager: A reference to a task manager object.
// Return: A constant reference to this object.
const TaskManager& TaskManager::operator=(const TaskManager& origTaskManager)
{
	if (this != &origTaskManager)
	{
		emptyTasks();

		Node* currNode = origTaskManager.head;

		while (currNode)
		{
			addTask(currNode->task.getName(), currNode->task.getDueDate(), currNode->task.getCompleted());
			currNode = currNode->next;
		}
	}

	return *this;
}

// Name:   ~TaskManager()
// Desc:   Destructor.
// Param:  None
// Return: None
TaskManager::~TaskManager()
{
	emptyTasks();
}

// Name:   emptyTasks()
// Desc:   Empty the task linked list.
// Param:  None
// Return: None
void TaskManager::emptyTasks()
{
	if (!head)
		return;

	while (head)
	{
		Node* tempNode = head->next;
		delete head;
		head = tempNode;
	}

	head = nullptr;
	numNodes = 0;
}

// Name:   addTask(const string& name, Date& dueDate)
// Desc:   Add a new task to the linked list.
// Param:  name: A string that holds the task name.
//         dueDate: A Date object that holds the task's due date.
//         completed: A boolean to determine if the task is completed.
// Return: A boolean: True if adding succeeds, false otherwise.
bool TaskManager::addTask(const std::string& name, const Date& dueDate)
{
	addTask(name, dueDate, false);

	return true;
}

// Name:   addTask(const string& name, Date& dueDate, bool completed)
// Desc:   Recursive function that finds the location where the new task
//         should be inserted.
// Param:  name: A string that holds the task name.
//         dueDate: A Date object that holds the task's due date.
//         completed: A boolean to determine if the task is completed.
// Return: None
void TaskManager::addTask(const std::string& name, const Date& dueDate, bool completed)
{
	if (!head)
	{
		head = new Node(name, dueDate, completed);
	}
	else
	{
		Node* currNode = head;

		while (currNode->next)
		{
			currNode = currNode->next;
		}

		currNode->next = new Node(name, dueDate, completed);
	}

	numNodes++;
}

// Name:   deleteTask(int taskNum)
// Desc:   Remove the chosen task from the task list.
// Param:  taskNum: An integer that represents the location of the task to remove.
// Return: A boolean: True if removing succeeds, false otherwise.
bool TaskManager::deleteTask(int taskNum)
{
	if (taskNum >= 1 && taskNum <= numNodes)
	{
		Node* currTask = head;
		Node* prevTask = nullptr;
		int currNum = 1;

		while (currTask->next && currNum != taskNum)
		{
			prevTask = currTask;
			currTask = currTask->next;
			currNum++;
		}

		if (currTask == head)
		{
			head = currTask->next;
			delete currTask;
			currTask = nullptr;
			numNodes--;
		}
		else
		{
			prevTask->next = currTask->next;
			delete currTask;
			currTask = nullptr;
			numNodes--;
		}

		return true;
	}

	return false;
}

// Name:   completeTask(int taskNum)
// Desc:   Mark the chosen task as completed.
// Param:  taskNum: An integer that represents the location of the task to complete.
// Return: None
void TaskManager::completeTask(int taskNum)
{
	Task* task = getTaskNodeByNum(taskNum);

	if (task)
		task->setComplete();
}

// Name:   getTaskNodeByNum(int taskNum)
// Desc:   Retrieve the chosen task.
// Param:  taskNum: An integer that represents the location of the task to retrieve.
// Return: A pointer to the task the user wanted to retrieve.
Task* TaskManager::getTaskNodeByNum(int taskNum)
{
	Task* task = nullptr;
	
	if (taskNum >= 1 && taskNum <= numNodes)
	{
		Node* currTask = head;
		int currNum = 1;

		while (currTask->next && currNum != taskNum)
		{
			currTask = currTask->next;
			currNum++;
		}

		if (currTask)
			task = &currTask->task;
	}

	return task;
}

// Name:   getNumTasks()
// Desc:   Retrieve the number of stored tasks.
// Param:  None
// Return: An integer representing the number of tasks in the linked list.
int TaskManager::getNumTasks() const
{
	return numNodes;
}

// Name:   getTasks()
// Desc:   Retrieve the list of tasks.
// Param:  None
// Return: A constant pointer to the head of the linked list.
const Node* TaskManager::getTasks() const
{
	return head;
}

// Name:   loadFromFile(const string& fileName)
// Desc:   Load a list of tasks from a file.
// Param:  fileName: A string that holds a file name.
// Return: A boolean: True if loading was successful, false otherwise.
bool TaskManager::loadFromFile(const std::string& fileName)
{
	std::ifstream file;
	file.open(fileName);

	if (!file.is_open())
		return false;

	emptyTasks();

	std::string name;
	int month = 0;
	int day = 0;
	int year = 0;
	bool completed = 0;

	while (!file.eof())
	{
		std::getline(file, name, ',');
		file >> month;
		file.ignore(1);
		file >> day;
		file.ignore(1);
		file >> year;
		file.ignore(1);
		file >> completed;
		file.ignore(1);

		addTask(name, Date(month, day, year), completed);
	}

	file.close();

	return true;
}

// Name:   saveToFile(const string& fileName)
// Desc:   Save the linked list to a file.
// Param:  fileName: A string that holds a file name.
// Return: A boolean: True if saving is successful, false otherwise.
bool TaskManager::saveToFile(const std::string& fileName) const
{
	std::ofstream file;
	file.open(fileName);

	if (!file.is_open())
		return false;

	Node* currNode = head;

	while (currNode)
	{
		file << currNode->task.getName() << "," << currNode->task.getDueDate().getMonth()
			<< "," << currNode->task.getDueDate().getDay() << "," << currNode->task.getDueDate().getYear()
			<< "," << currNode->task.getCompleted();

		if (currNode->next)
			file << std::endl;

		currNode = currNode->next;
	}

	file.close();

	return true;
}

// Name:   checkFileExists(const string& fileName)
// Desc:   Check if a file exists.
// Param:  fileName: A string that holds a file name.
// Return: A boolean: True if file exists, false otherwise.
bool TaskManager::checkFileExists(const std::string& fileName)
{
	return std::filesystem::exists(fileName);
}
