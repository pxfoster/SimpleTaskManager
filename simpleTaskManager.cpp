#include "simpleTaskManager.h"

// Name:   SimpleTaskManager()
// Desc:   Default constructor that initializes the members.
// Param:  None
// Return: None
SimpleTaskManager::SimpleTaskManager()
	: currState(STATES::MENU), currFile("None"), running(true), fileModified(false)
{
	messageMargin = 4;
}

// Name:   programLoop()
// Desc:   The main loop of the program.
// Param:  None
// Return: None
void SimpleTaskManager::programLoop()
{
	while (running)
	{
		switch (currState)
		{
			case STATES::MENU:
				showMainMenu();
				addGap();
				break;

			case STATES::DISPLAY:
				stateDisplay();
				break;

			case STATES::ADD:
				stateAdd();
				break;

			case STATES::COMPLETE:
				stateComplete();
				break;

			case STATES::REMOVE:
				stateRemove();
				break;

			case STATES::CHANGEFILE:
				stateChangeFile();
				break;

			case STATES::LOAD:
				stateLoad();
				break;

			case STATES::SAVE:
				stateSave();
				break;

			case STATES::QUIT:
				stateQuit();
				break;

			default:
				displayMessage("You shouldn't be here.");
				running = false;
				break;
		}

		if (running)
		{
			addGap();
			displayMessage("(Main Menu)");
			currState = (STATES)getIntInput("Choice (0 for menu): ", STATES::MENU, STATES::QUIT);
		}
	}

	addGap();
	displayMessage("Program is shutting down, have a nice day!");
}

// Name:   stateDisplay()
// Desc:   Display the tasks to the console.
// Param:  None
// Return: None
void SimpleTaskManager::stateDisplay()
{
	addGap();
	if (manager.getNumTasks() > 0)
	{
		displayMessage("Tasks (Task Name | Due Date | Status):");
		displayTasks(manager.getTasks());
	}
	else
		displayMessage("There are no tasks in your list!");
}

// Name:   stateAdd()
// Desc:   Add a task to the task list.
// Param:  None
// Return: None
void SimpleTaskManager::stateAdd()
{
	std::string name;
	std::string tempDate;
	bool validDate = false;

	addGap();
	displayMessage("Enter task name: ", false);
	std::getline(std::cin, name, '\n');

	while (!validDate)
	{
		displayMessage("Enter due date as mm/dd/yyyy: ", false);
		std::getline(std::cin, tempDate, '\n');

		if (Date::validateDate(tempDate))
			validDate = true;
		else
			displayMessage("Invalid date!");
	}

	manager.addTask(name, Date(tempDate));
	fileModified = true;
	displayMessage("Task was added!");
}

// Name:   stateComplete()
// Desc:   Complete a task.
// Param:  None
// Return: None
void SimpleTaskManager::stateComplete()
{
	int userChoice = 0;
	int maxTaskNum = manager.getNumTasks();

	addGap();
	if (maxTaskNum < 1)
	{
		displayMessage("There are no tasks to complete!");
		return;
	}

	displayMessage("Your current list:");
	displayTasks(manager.getTasks());
	addGap();
	userChoice = getIntInput("Choose a task to complete (0 to cancel): ", 0, maxTaskNum);

	while (!std::cin || userChoice < 0 || userChoice > manager.getNumTasks())
	{
		std::cin.clear();
		std::cin.ignore(100, '\n');
		userChoice = getIntInput("Choose a task to complete (0 to cancel): ", 0, maxTaskNum);
	}

	if (userChoice != 0)
	{
		manager.completeTask(userChoice);
		displayMessage("Task has been completed!");
		fileModified = true;
	}
}

// Name:   stateRemove()
// Desc:   Remove a task.
// Param:  None
// Return: None
void SimpleTaskManager::stateRemove()
{
	int userChoice = 0;
	int maxTaskNum = manager.getNumTasks();

	addGap();
	if (maxTaskNum < 1)
	{
		displayMessage("There are no tasks to remove!");
		return;
	}

	displayMessage("Your current list:");
	displayTasks(manager.getTasks());
	addGap();
	userChoice = getIntInput("Choose a task to remove (0 to cancel): ", 0, maxTaskNum);

	while (!std::cin || userChoice < 0 || userChoice > manager.getNumTasks())
	{
		std::cin.clear();
		std::cin.ignore(100, '\n');
		displayMessage("Invalid Input!");
		userChoice = getIntInput("Choose a task to remove (0 to cancel): ", 0, maxTaskNum);
	}

	if (userChoice != 0)
	{
		manager.deleteTask(userChoice);
		displayMessage("Task has been removed!");
		fileModified = true;
	}
}

// Name:   stateSave()
// Desc:   Save the task list to a file.
// Param:  None
// Return: None
void SimpleTaskManager::stateSave()
{
	const char choices[] = { 'y', 'n' };
	char answer = 'y';

	if (manager.getNumTasks() < 1)
	{
		answer = getCharInput("You have no tasks to save. Do you still want to save (y/n)? ", choices, sizeof(choices));
	}

	if (answer == 'y')
	{
		if (currFile == "None")
		{
			displayMessage("Enter a name for your file: ", false);
			std::getline(std::cin, currFile, '\n');
			currFile.append(".txt");
		}

		manager.saveToFile(currFile);
		displayMessage("File was saved!");
		fileModified = false;
	}
	else
		displayMessage("File not saved!");
}

// Name:   stateLoad()
// Desc:   Load a task list from a file.
// Param:  None
// Return: None
void SimpleTaskManager::stateLoad()
{
	if (currFile == "None")
	{
		displayMessage("Please choose a file from the main menu.");
		return;
	}

	if (manager.checkFileExists(currFile))
	{
		manager.loadFromFile(currFile);
		displayMessage("File was loaded!");
		fileModified = false;
	}
	else
		displayMessage("File does not exist!");
}

// Name:   stateChangeFile()
// Desc:   Change the file name to use for saving and loading.
// Param:  None
// Return: None
void SimpleTaskManager::stateChangeFile()
{
	displayMessage("Enter a name for your file: ", false);
	std::getline(std::cin, currFile, '\n');
	currFile.append(".txt");
	displayMessage("Filename changed to: " + currFile);
	fileModified = false;
}

// Name:   stateQuit()
// Desc:   Quit the program.
// Param:  None
// Return: None
void SimpleTaskManager::stateQuit()
{
	const char choices[] = { 'y', 'n' };
	char answer = 'y';

	if (fileModified)
	{
		displayMessage("You have an unsaved file.");
		answer = getCharInput("Are you sure you want to quit (y/n)? ", choices, sizeof(choices));
	}

	if (answer == 'y')
		running = false;
}

// Name:   showMainMenu()
// Desc:   Display the main menu to the console.
// Param:  None
// Return: None
void SimpleTaskManager::showMainMenu()
{
	std::string tempString;
	int borderLength = setTitle("Main Menu", ConsoleIO::messageMargin);
	displayMessage("Opened Task File: " + currFile, false);
	if (fileModified)
		displayMessage("*", false, 0);
	addGap();
	addFill('-', borderLength, ConsoleIO::messageMargin);
	addGap();
	addSpaces(1);
	displayMessage("Choose an option:");
	addSpaces(ConsoleIO::messageMargin + 5);
	std::cout << STATES::DISPLAY << ". Display Tasks" << std::endl;
	addSpaces(ConsoleIO::messageMargin + 5);
	std::cout << STATES::ADD << ". Add Task" << std::endl;
	addSpaces(ConsoleIO::messageMargin + 5);
	std::cout << STATES::COMPLETE << ". Complete Task" << std::endl;
	addSpaces(ConsoleIO::messageMargin + 5);
	std::cout << STATES::REMOVE << ". Remove Task" << std::endl;
	addSpaces(ConsoleIO::messageMargin + 5);
	std::cout << STATES::CHANGEFILE << ". Change File" << std::endl;
	addSpaces(ConsoleIO::messageMargin + 5);
	std::cout << STATES::LOAD << ". Load File" << std::endl;
	addSpaces(ConsoleIO::messageMargin + 5);
	std::cout << STATES::SAVE << ". Save File" << std::endl;
	addSpaces(ConsoleIO::messageMargin + 5);
	std::cout << STATES::QUIT << ". Quit" << std::endl;
	addFill('-', borderLength, ConsoleIO::messageMargin);
}

// Name:   displayTasks(const Node* currNode)
// Desc:   Display the list of tasks to the console.
// Param:  currNode: A Node pointer that points to the head of the list.
// Return: None
void SimpleTaskManager::displayTasks(const Node* currNode)
{
	int counter = 1;

	while (currNode)
	{
		addSpaces(8);
		std::cout << counter << ". " << currNode->task.getName() << " | "
			<< currNode->task.getDueDate().getMonth() << "/"
			<< currNode->task.getDueDate().getDay() << "/"
			<< currNode->task.getDueDate().getYear() << " | ";

		if (currNode->task.getCompleted())
			std::cout << "Completed";
		else
			std::cout << "Incomplete";

		addGap();
		currNode = currNode->next;
		counter++;
	}
}
