#pragma once
#include <string>
#include <iostream>

/*****************************************************************************
# Description: ConsoleIO is a class that has functions to help with
               handling console input and output.
#****************************************************************************/

class ConsoleIO
{
public:
	ConsoleIO();

	void addSpaces(int numSpaces);
	void addFill(const char fillChar, int fillAmount, int spacesBefore = 0);
	void addGap();
	int setTitle(const std::string& title, int spacesBefore = 0, char fillChar = '=');
	void displayMessage(const std::string& message, bool useEndline = true, int numSpaces = messageMargin);
	int getIntInput(const std::string& message, int minNumber, int maxNumber);
	char getCharInput(const std::string& message, const char choices[], int numChoices);

	void setMessageMargin(int marginSize);

protected:
	static int messageMargin;
};
