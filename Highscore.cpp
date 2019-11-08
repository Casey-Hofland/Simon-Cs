// Highscore.cpp : This file saves, loads and displays the highscore(s).
#include "Highscore.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>
using namespace std;
using namespace boost;

Score::Score(string score)
{
	this->score = score;

	// Seperates the name from the sequence
	int lastDashIndex = score.rfind('-');
	name = score.substr(0, lastDashIndex);
	sequence = score.substr(lastDashIndex + 1, score.size());
}

Highscore::Highscore()
{
	// Determine the current size of the highscore list and the current lowest score
	string scores = ReadScore();
	if (scores.empty())
	{
		storedScores = 0;
		lowestScore = 0;
		return;
	}

	vector<string> temp;
	split(temp, scores, is_any_of("\n"));
	storedScores = temp.size();

	Score score = Score(temp.back());
	lowestScore = score.sequence.size();
}

void Highscore::DisplayScore() 
{
	string* score = GetScore();

	cout << "Highscores: " << endl;
	for (int i = 0; i < storedScores; i++)
	{
		Score thisScore = Score(*(score + i));
		cout << thisScore.sequence.size() << " - " << thisScore.name << ": " << thisScore.sequence << endl;
	}
	cout << endl;

	system("pause");
	cout << endl;
}

void Highscore::SaveScore(string name, string sequence)
{
	if (sequence.empty())
		return;

	if (storedScores < maxStoredScores
		|| sequence.size() >= lowestScore)
	{
		// Increment the score size (if possible)
		storedScores = min(storedScores + 1, maxStoredScores);

		// Update the score by incrementing the list where applicable
		Score lastScore = Score(name + "-" + sequence);
		string* score = GetScore();
		for (int i = 0; i < storedScores; i++)
		{
			Score thisScore = Score(*(score + i));

			if (lastScore.sequence.size() >= thisScore.sequence.size())
			{
				*(score + i) = lastScore.score;
				lastScore = thisScore;
			}
		}

		lowestScore = lastScore.sequence.size();

		// Save the new score
		ofstream output(filename);
		for (int i = 0; i < storedScores; i++)
			output << *(score + i) << '\n';
		output.close();
	}
}

string Highscore::ReadScore()
{
	ifstream input(filename);

	string str;
	string scores;
	while (getline(input, str))
	{
		scores += str;
		scores.push_back('\n');
	}

	if (!scores.empty())
		scores = scores.substr(0, scores.size() - 1);

	return scores;
}

string* Highscore::GetScore()
{
	string scores = ReadScore();

	vector<string> temp;
	split(temp, scores, is_any_of("\n"));

	static string result[maxStoredScores];
	copy(temp.begin(), temp.end(), result);

	return result;
}