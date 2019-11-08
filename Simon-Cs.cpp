// Simon-Cs.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "Name.h"
#include "Startmenu.h"
#include "Gameloop.h"
#include "Highscore.h"
#include <iostream>
#include <ctime>
using namespace std;

void ClearConsole() 
{
	system("cls");
}

int main()
{
	srand(time(NULL)); // Set a new seed for the random class
	bool welcomeBack = true;

	// Retrieves the name of the player or sets it if there is none
	Name nameHandler;
	string name = nameHandler.GetName();
	if (name.empty())
	{
		cout << "We see that this is your first time playing" << endl;
		cout << endl;
		welcomeBack = false;
		name = nameHandler.AskName();
		ClearConsole();
	}

	// Initialize Components
	Startmenu startmenu;
	Gameloop gameloop = Gameloop(name);
	Highscore highscore;

	Command command;
	string lastSequence;
	do
	{
		// Greet the player
		cout << "Simons Cs" << endl;
		cout << endl;
		cout << "Welcome " << ((welcomeBack) ? "back, " : "") << name << endl;
		cout << endl;
		welcomeBack = false;

		// Ask for a command
		command = startmenu.AskCommand();
		ClearConsole();

		// Execute the command
		switch (command)
		{
		case ChangeName:
			name = nameHandler.AskName();
			break;
		case ViewHighscores:
			highscore.DisplayScore();
			break;
		case Play:
			lastSequence = gameloop.Run();
			highscore.SaveScore(name, lastSequence);
			highscore.DisplayScore();
			break;
		default:
			break;
		}

		ClearConsole();
	} while (command != Quit);

	cout << "Quit Game" << '\n';

	return 0;
}