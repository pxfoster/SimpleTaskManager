#include "consoleIO.h"
#include <iomanip>

int ConsoleIO::messageMargin = 0;

// Name:   ConsoleIO()
// Desc:   Default constructor.
// Param:  None
// Return: None
ConsoleIO::ConsoleIO()
{
}

// Name:   addSpaces(int numSpaces)
// Desc:   Put spaces into a cout console operation.
// Param:  numSpaces: An integer for the number of spaces to put in.
// Return: None
void ConsoleIO::addSpaces(int numSpaces)
{
	if (numSpaces > 0)
		std::cout << std::setw(numSpaces) << " ";
}

// Name:   addFill(char fillChar, int fillAmount, int spacesBefore)
// Desc:   Adds a certain amount of a chosen char into a cout console operation.
// Param:  fillChar: The character to use.
//         fillAmount: The number of characters to use.
//         spacesBefore: The number of spaces to place before the first character.
// Return: None
void ConsoleIO::addFill(const char fillChar, int fillAmount, int spacesBefore)
{
	if (spacesBefore > 0)
		std::cout << std::setw(spacesBefore) << " " << std::setfill(fillChar) << std::setw(fillAmount) << fillChar << std::setfill(' ');
	else
		std::cout << std::setfill(fillChar) << std::setw(fillAmount) << fillChar << std::setfill(' ');
}

// Name:   addGap()
// Desc:   Add an end of line to the cout console operation.
// Param:  None
// Return: None
void ConsoleIO::addGap()
{
	std::cout << std::endl;
}

// Name:   setTitle(const string& title, int spacesBefore, char fillChar)
// Desc:   Sets and displays a title to the console.
// Param:  title: A string that holds the title name.
//         spacesBefore: The amount of spaces before the title.
//         fillChar: The character to use for the borders of the title.
// Return: An integer for the length of the border.
int ConsoleIO::setTitle(const std::string& title, int spacesBefore, char fillChar)
{
	int borderLength = title.length() + 16;

	std::cout << std::endl;
	addFill(fillChar, borderLength, spacesBefore);
	addGap();
	addSpaces(spacesBefore);
	std::cout << "|       " << title << "       |\n";
	addFill(fillChar, borderLength, spacesBefore);
	addGap();

	return borderLength;
}

// Name:   displayMessage(const string& message, bool useEndline, numSpaces)
// Desc:   Display a message to the console.
// Param:  message: A string that holds the message to display.
//         useEndline: A boolean to determine if a new line should be after the message.
//         numSpaces: The number of spaces before the message.
// Return: None
void ConsoleIO::displayMessage(const std::string& message, bool useEndline, int numSpaces)
{
	addSpaces(numSpaces);
	std::cout << message;

	if (useEndline)
		addGap();
}

// Name:   getIntInput(const string& message, int minNumber, int maxNumber)
// Desc:   Get an integer value from the user.
// Param:  message: A string that holds a statement for the user.
//         minNumber: An integer for the lowest value a number can be.
//         maxNumber: An integer for the highest value a number can be.
// Return: The integer that the user chose.
int ConsoleIO::getIntInput(const std::string& message, int minNumber, int maxNumber)
{
	int choice = 0;

	displayMessage(message, false);
	std::cin >> choice;

	while (!std::cin || choice < minNumber || choice > maxNumber)
	{
		std::cin.clear();
		std::cin.ignore(100, '\n');
		displayMessage("Invalid Input!");
		displayMessage(message, false);
		std::cin >> choice;
	}

	std::cin.clear();
	std::cin.ignore(100, '\n');

	return choice;
}

// Name:   getCharInput(const string& message, const char choices[], int numChoices)
// Desc:   Get a char value from the user.
// Param:  message: A string that holds a statement for the user.
//         choices: An array that holds valid choices.
//         numChoices: An integer for the number of possible choices.
// Return: The char that the user chose.
char ConsoleIO::getCharInput(const std::string& message, const char choices[], int numChoices)
{
	char choice = '0';
	bool validChoice = false;

	displayMessage(message, false);
	std::cin >> choice;

	while (!validChoice)
	{
		for (int i = 0; i < numChoices; i++)
		{
			if (choice == choices[i])
			{
				validChoice = true;
				break;
			}
		}

		if (!validChoice)
		{
			std::cin.clear();
			std::cin.ignore(100, '\n');
			displayMessage("Invalid Input!");
			displayMessage(message, false);
			std::cin >> choice;
		}
	}
	std::cin.clear();
	std::cin.ignore(100, '\n');

	return choice;
}

// Name:   setMessageMargin(int marginSize)
// Desc:   Set the size of the margin for a message.
// Param:  marginSize: An integer for the size of the margin.
// Return: None
void ConsoleIO::setMessageMargin(int marginSize)
{
	messageMargin = marginSize;
}
