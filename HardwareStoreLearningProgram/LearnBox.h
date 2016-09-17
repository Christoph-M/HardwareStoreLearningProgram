#pragma once

#include "IMode.h"

#include <list>


class LearnBox : public IMode {
public:
	LearnBox(class ApplianceUtility*, int parts = 0);

	int NextWord();
	void Reset();
	void Save();

	~LearnBox();

private:
	void DisplayPartitions();
	void UpdatePartitions(bool);

private:
	class ApplianceUtility* appUtil;

	const int numParts;
	int curPart;

	std::list<int>* partitions;
};