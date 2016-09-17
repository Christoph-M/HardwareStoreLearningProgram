#pragma once

#include "IMode.h"


class Sequence : public IMode {
public:
	Sequence(class ApplianceUtility*, bool ran = false);

	int NextWord();
	void Reset();
	void Save();

	~Sequence();

private:
	class ApplianceUtility* appUtil;

	int curWord;

	bool random;
};