#include "Sequence.h"

#include <fstream>
#include <time.h>

#include "Input.h"
#include "ApplianceUtility.h"


Sequence::Sequence(ApplianceUtility* app, bool ran) :
	appUtil(app),
	curWord(0),
	random(ran)
{
	std::ifstream file;
	file.open("save\\save.sequence");

	if (file.is_open()) {
		curWord = file.get() - '0';
		file.close();
	} else if (random) {
		srand((unsigned int)time(NULL));
		curWord = rand() % appUtil->NumWords();
	}
}


int Sequence::NextWord() {
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
	if (result) curWord = (random) ? rand() % appUtil->NumWords() : appUtil->NextWordIndex(curWord);

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


Sequence::~Sequence() {

}