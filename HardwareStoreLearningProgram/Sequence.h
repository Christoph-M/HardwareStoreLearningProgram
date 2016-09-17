#pragma once

#include "IMode.h"


class Sequence : public IMode {
public:
	Sequence(char**, int);

	int NextWord();
	void Reset();
	void Save();

	~Sequence();

private:
	void DisplayWord();
	void DisplayTips();
	void DisplayResult(bool);
	int  NextWordIndex();

private:
	const int numWords;

	char** appliances;

	int curWord;
};