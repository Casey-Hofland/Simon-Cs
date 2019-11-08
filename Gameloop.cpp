// Gameloop.cpp : This file runs the gameloop and itterates through it.
#include "Gameloop.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <chrono>
#include <thread>
using namespace std;
using namespace boost;
using namespace this_thread;
using namespace chrono;

Gameloop::Gameloop(string name) 
{
	int targetSize = size("Computer") - 1;
	displayedName = name.substr(0, targetSize);

	for (int i = displayedName.size(); i < targetSize; i++)
		addedWhitespace += ' ';
}

string Gameloop::Run() 
{
	string sequence;
	string guess;

	do 
	{
		// If there is a guess, it means it was correct and we want to hide it so the player 
		// can't cheat by looking at his last correct sequence.
		if (!guess.empty())
		{
			cout << "\x1b[A" << '\r' << displayedName + ": " + addedWhitespace << 
				HideSequence(SeperateByWhitespace(guess), '!') << '\n';
			sleep_for(seconds(1));
		}

		sequence += RandomChar(); // Add a new char to the sequence

		// The first cout enables the user to anticipate the sequence.
		// The second cout shows the sequence.
		// The third cout hides the sequence.
		string displayedSequence = SeperateByWhitespace(sequence);
		cout << "Computer: ";
		sleep_for(seconds(1));
		cout << displayedSequence << '\r';
		sleep_for(seconds(1));
		string hiddenSequence = HideSequence(displayedSequence, '?');
		cout << "Computer: " << hiddenSequence << '\n';

		// Asks the player to guess the sequence
		cout << displayedName + ": " + addedWhitespace;
		getline(cin, guess);
		RemoveWhitespace(guess);
		to_upper(guess);
	} while (sequence == guess); // Check if the guess equals the sequence

	cout << endl;
	cout << "Oh No! The correct sequence was: " << sequence << endl;
	cout << "You guessed:                     " << guess << endl;
	cout << endl;

	return sequence.substr(0, sequence.size() - 1);
}

char Gameloop::RandomChar() const
{
	return characters[rand() % size(characters)];
}

void Gameloop::RemoveWhitespace(string& str) 
{
	str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
}

// Seperate every character in a string with whitespace
string Gameloop::SeperateByWhitespace(string str)
{
	string output = "";
	for (int i = 0; i < str.size(); i++) 
	{
		output += str.at(i);
		output += ' ';
	}

	if (output.size() > 0)
		output = output.substr(0, output.size() - 1);
	
	return output;
}

// Replace every character in a string with the hideChar
string Gameloop::HideSequence(string str, char hideChar)
{
	string output = str;
	replace_if(output.begin(), output.end(), [&](char c) {return c != ' '; }, hideChar);
	return output;
}