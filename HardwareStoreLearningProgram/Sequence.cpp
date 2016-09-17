#include "Sequence.h"

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>

#include "Input.h"


Sequence::Sequence(char** appl, int words) :
	numWords((words < 1) ? 1 : ((words > 200) ? 200 : words)),
	appliances(appl),
	curWord(0)
{
	std::ifstream file;
	file.open("save\\save.sequence");

	if (file.is_open()) {
		curWord = file.get() - '0';
		file.close();
	}
}


int Sequence::NextWord() {
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
	if (result) ++curWord;

	this->DisplayResult(result);

	return (result) ? ((tip) ? TIP : RIGHT) : WRONG;
}

void Sequence::Reset() {
	curWord = 0;
}

void Sequence::Save() {
	std::ofstream file;
	file.open("save\\save.sequence", std::ios::out | std::ios::trunc);
		file.put(static_cast<char>(curWord) + '0');
	file.close();
}

void Sequence::DisplayWord() {
	puts(" What's the next appliance? (Press enter for tip)\n");
	printf(" ----------> %s <----------\n", appliances[curWord]);
}

void Sequence::DisplayTips() {
	int p = rand() % 5;
	int word = this->NextWordIndex();
	for (int i = 0; i < 5; ++i) {
		if (i == p) {
			printf(" -> %s\n", appliances[word]);
		} else {
			int r = rand() % numWords;
			printf(" -> %s\n", appliances[r]);
		}
	}
}

void Sequence::DisplayResult(bool result) {
	if (result) printf(" Correct!   ");
	else		printf(" Wrong!\n Correct answer: %s   ", appliances[this->NextWordIndex()]);
}

int Sequence::NextWordIndex() {
	return (numWords - 1 == curWord) ? 0 : curWord + 1;
}


Sequence::~Sequence() {

}