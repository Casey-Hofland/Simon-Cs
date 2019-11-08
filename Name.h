#pragma once

#include <string>
using namespace std;

class Name
{
private:
	const string filename = "name.txt";

public:
	string GetName() const;
	string AskName() const;
};