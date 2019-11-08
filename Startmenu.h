#pragma once

#include <string>
using namespace std;

enum Command
{
	ChangeName,
	ViewHighscores,
	Play,
	Quit
};

class Startmenu
{
public:
	Command AskCommand() const;
};