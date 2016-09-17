#include "LearnBox.h"

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>

#include "Input.h"


LearnBox::LearnBox(char** appl, int words, int parts) :
	numWords((words < 1) ? 1 : ((words > 200) ? 200 : words)),
	appliances(appl),
	numParts((parts < 1) ? 1 : ((parts > 99) ? 99 : parts)),
	curPart(0),
	partitions(new std::list<int>[numParts])
{
	std::ifstream file;
	file.open("save\\save.learnbox");

	if (file.is_open()) {
		curPart = file.get() - '0';
		
		int part = 0;
		for (int i = 0; i < numWords + numParts; ++i) {
			char word = '\0';
			file.get(word);

			if (word == '\n') ++part;
			else partitions[part].push_back(static_cast<int>(word) - '0');
		}

		file.close();
	} else {
		for (int i = 0; i < numWords; ++i) partitions[curPart].push_back(i);
	}
	
	srand((unsigned int)time(NULL));
}


int LearnBox::NextWord() {
	this->DisplayWord();

	Input inpt(100);
	char* input = inpt.GetInput();

	bool tip = false;
	if (input[0] == '\0') {
		tip = true;
		this->DisplayTips();
		input = inpt.GetInput();
	}

	bool result = inpt.CheckInput(input, appliances[this->NextWordIndex()]);

	this->DisplayResult(result);
	this->UpdatePartitions(result);

	return (result) ? ((tip) ? TIP : RIGHT) : WRONG;
}

void LearnBox::Reset() {
	delete[](partitions);

	partitions = new std::list<int>[numParts];

	for (int i = 0; i < numWords; ++i) partitions[curPart].push_back(i);
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

void LearnBox::DisplayWord() {
	puts(" What's the next appliance? (Press enter for tip)\n");
	printf(" ----------> %s <----------\n", appliances[partitions[curPart].front()]);
}

void LearnBox::DisplayTips() {
	int p = rand() % 5;
	int word = this->NextWordIndex();
	for (int i = 0; i < 5; ++i) {
		if (i == p) {
			printf(" -> %s\n", appliances[word]);
		}
		else {
			int r = rand() % numWords;
			printf(" -> %s\n", appliances[r]);
		}
	}
}

void LearnBox::DisplayResult(bool result) {
	if (result) printf(" Correct!   ");
	else		printf(" Wrong!\n Correct answer: %s   ", appliances[this->NextWordIndex()]);
}

int LearnBox::NextWordIndex() {
	return (numWords - 1 == partitions[curPart].front()) ? 0 : partitions[curPart].front() + 1;
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