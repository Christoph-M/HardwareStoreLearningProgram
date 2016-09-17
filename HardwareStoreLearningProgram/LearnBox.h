#pragma once

#include "IMode.h"

#include <list>


class LearnBox : public IMode {
public:
	LearnBox(char**, int, int parts = 0);

	int NextWord();
	void Reset();
	void Save();

	~LearnBox();

private:
	void DisplayWord();
	void DisplayTips();
	void DisplayResult(bool);
	int  NextWordIndex();
	void DisplayPartitions();
	void UpdatePartitions(bool);

private:
	const int numWords;
	char** appliances;

	const int numParts;
	int curPart;

	std::list<int>* partitions;
};