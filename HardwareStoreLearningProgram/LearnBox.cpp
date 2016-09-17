#include "LearnBox.h"

#include <cstdio>
#include <iostream>
#include <fstream>

#include "Input.h"
#include "ApplianceUtility.h"


LearnBox::LearnBox(ApplianceUtility* app, int parts) :
	appUtil(app),
	numParts((parts < 1) ? 1 : ((parts > 99) ? 99 : parts)),
	curPart(0),
	partitions(new std::list<int>[numParts])
{
	std::ifstream file;
	file.open("save\\save.learnbox");

	if (file.is_open()) {
		curPart = file.get() - '0';
		
		int part = 0;
		for (int i = 0; i < appUtil->NumWords() + numParts; ++i) {
			char word = '\0';
			file.get(word);

			if (word == '\n') ++part;
			else partitions[part].push_back(static_cast<int>(word) - '0');
		}

		file.close();
	} else {
		for (int i = 0; i < appUtil->NumWords(); ++i) partitions[curPart].push_back(i);
	}
}


int LearnBox::NextWord() {
	int curWord = partitions[curPart].front();

	this->DisplayPartitions();
	appUtil->DisplayWord(curWord);

	Input inpt(100);
	char* input = inpt.GetInput();

	bool tip = false;
	if (input[0] == '\0') {
		tip = true;
		appUtil->DisplayTips(curWord);
		input = inpt.GetInput();
	}

	bool result = inpt.CheckInput(input, appUtil->GetNextWord(curWord));

	appUtil->DisplayResult(result, curWord);
	this->UpdatePartitions(result);

	return (result) ? ((tip) ? TIP : RIGHT) : WRONG;
}

void LearnBox::Reset() {
	delete[](partitions);

	partitions = new std::list<int>[numParts];

	for (int i = 0; i < appUtil->NumWords(); ++i) partitions[curPart].push_back(i);
}

void LearnBox::Save() {
	std::ofstream file;
	file.open("save\\save.learnbox");
		file.put(static_cast<char>(curPart) + '0');
		for (int i = 0; i < numParts; ++i) {
			for (int word : partitions[i]) file.put(static_cast<char>(word) + '0');

			file.put('\n');
		}
	file.close();
}

void LearnBox::DisplayPartitions() {
	printf(" Current partition: %02d           Words left in partition %02d: %03zd\n", curPart + 1, 1, partitions[0].size());
	for (int i = 1; i < numParts; ++i) printf("                                 Words left in partition %02d: %03zd\n", i + 1, partitions[i].size());
	puts("");
}

void LearnBox::UpdatePartitions(bool result) {
	if (result) partitions[(curPart > numParts - 2) ? curPart : curPart + 1].push_back(partitions[curPart].front());
	else		partitions[0].push_back(partitions[curPart].front());

	partitions[curPart].pop_front();

	if (partitions[curPart].size() <= 0) {
		curPart = 0;

		while (partitions[curPart].size() <= 0) ++curPart;
	}
}


LearnBox::~LearnBox() {
	delete[](partitions);
}