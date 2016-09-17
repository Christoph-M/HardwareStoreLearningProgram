#include "ApplianceUtility.h"

#include <cstdio>
#include <iostream>
#include <time.h>


ApplianceUtility::ApplianceUtility(char** appl, int words) :
	numWords((words < 1) ? 1 : ((words > 200) ? 200 : words)),
	appliances(appl)
{
	srand((unsigned int)time(NULL));
}


char* ApplianceUtility::GetWord(int word) {
	return (word >= 0) ? (word < numWords) ? appliances[word] : appliances[numWords - 1] : appliances[0];
}

char* ApplianceUtility::GetNextWord(int word) {
	return this->GetWord(this->NextWordIndex(word));
}

void ApplianceUtility::DisplayWord(int word) {
	puts(" What's the next appliance? (Press enter for tip)\n");
	printf(" ----------> %s <----------\n", this->GetWord(word));
}

void ApplianceUtility::DisplayTips(int word) {
	int p = rand() % 5;
	for (int i = 0; i < 5; ++i) {
		if (i == p) {
			printf(" -> %s\n", this->GetNextWord(word));
		} else {
			int r = rand() % numWords;
			printf(" -> %s\n", this->GetWord(r));
		}
	}
}

void ApplianceUtility::DisplayResult(bool result, int word) {
	if (result) printf(" Correct!   ");
	else		printf(" Wrong!\n Correct answer: %s   ", this->GetNextWord(word));
}

int ApplianceUtility::NextWordIndex(int word) {
	return (word >= numWords - 1) ? 0 : word + 1;
}


ApplianceUtility::~ApplianceUtility() {

}