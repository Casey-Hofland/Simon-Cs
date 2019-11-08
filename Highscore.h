#pragma once

#include <string>
using namespace std;

struct Score
{
public:
	Score(string score);
	string score;
	string name;
	string sequence;
};

class Highscore
{
private:
	const string filename = "highscores.txt";
	static const int maxStoredScores = 5;
	int storedScores;
	int lowestScore;
	string ReadScore();
	string* GetScore();

public:
	Highscore();
	void SaveScore(string name, string sequence);
	void DisplayScore();
};