#pragma once
#include "consoleIO.h"
#include "taskManager.h"

/*****************************************************************************
# Description: An enum of states that are used to determine which
               state the program should be in.
			   The SimpleTaskManager class is the main program and
			   is derived from ConsoleIO.
#****************************************************************************/

enum STATES { MENU, DISPLAY, ADD, COMPLETE, REMOVE, CHANGEFILE, LOAD, SAVE, QUIT };

class SimpleTaskManager : public ConsoleIO
{
public:
	SimpleTaskManager();
	void programLoop();

private:
	void stateDisplay();
	void stateAdd();
	void stateComplete();
	void stateRemove();
	void stateSave();
	void stateLoad();
	void stateChangeFile();
	void stateQuit();
	void showMainMenu();
	void displayTasks(const Node* currNode);

	TaskManager manager;
	STATES currState;
	std::string currFile;
	bool running;
	bool fileModified;
};
