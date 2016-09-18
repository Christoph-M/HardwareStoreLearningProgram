#pragma once

#include "IMode.h"

#include <list>


class LearnBox : public IMode {
public:
	LearnBox(class ApplianceUtility*, int parts = 1, bool ran = false);

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

	bool random;

	std::list<int>* partitions;
};