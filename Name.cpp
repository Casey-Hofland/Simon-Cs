// Name.cpp : Handles storing, retreiving, and changing the name
#include "Name.h"
#include <iostream>
#include <string>
#include <fstream>
#include <boost/algorithm/string.hpp>
using namespace std;
using namespace boost;

// Retrieves the stored name
string Name::GetName() const
{
	ifstream input(filename);

	string name;
	input >> name;

	input.close();

	return name;
}

// Asks for a name until receiving a valid answer and a confirmation by the player
string Name::AskName() const
{
	string name;
	string confirmation;
	do
	{
		cout << "Please type in your name: ";
		getline(cin, name); // Ask for a name

		trim_left(name);
		trim_right(name);

		if (name.empty()) // Check if the name is valid
		{
			cout << "Your name can't be empty" << endl;
		}
		else // Ask for a confirmation
		{
			cout << "Your name is " << name << ". Type 'c' if this is correct." << endl;
			getline(cin, confirmation);
		}
		cout << endl;
	} while (name.empty() || confirmation != "c");

	ofstream output(filename);
	output << name;
	output.close();

	return name;
}