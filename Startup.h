#pragma once

#include <string>
using namespace std;

enum Command
{
	ChangeName,
	ViewHighscores,
	Play,
};

class Startmenu
{
private:

public:
	Command AskCommand() const;
};