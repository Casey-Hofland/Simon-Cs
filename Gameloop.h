#pragma once

#include <string>
using namespace std;

class Gameloop 
{
private:
	const char characters[4] = { 'A', 'B', 'C', 'D' };
	string displayedName;
	string addedWhitespace;
	char RandomChar() const;
	void RemoveWhitespace(string& str);
	string SeperateByWhitespace(string str);
	string HideSequence(string str, char hideChar);

public:
	Gameloop(string name);
	string Run();
};