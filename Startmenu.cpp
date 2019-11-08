// Startmenu.cpp : This file contains the functions and variables needed to Start the game.
#include "Startmenu.h"
#include <iostream>
#include <string>
using namespace std;

// Ask for a command until receiving a valid command
Command Startmenu::AskCommand() const
{
	string commandStr;
	do
	{
		// Print an error for typing invalid commands
		if (!commandStr.empty()) // If the command is not empty, this means the last command was invalid
		{
			cout << endl;
			cout << "------------------------------" << endl;
			cout << endl;
			cout << "That is not a valid command" << endl;
			cout << endl;
		}

		// Instruct the player as to what commands are valid
		cout << "To change your name, enter n" << endl;
		cout << "To view the highscores, enter h" << endl;
		cout << "To start the game, enter g" << endl;

		getline(cin, commandStr); // Ask for a command
	} while (commandStr != "n"
		&& commandStr != "h"
		&& commandStr != "g");

	// Convert the command string to an enum
	Command command;

	if (commandStr == "n")
		command = ChangeName;
	else if (commandStr == "h")
		command = ViewHighscores;
	else if (commandStr == "g")
		command = Play;
	else
		command = Quit;

	return command;
}