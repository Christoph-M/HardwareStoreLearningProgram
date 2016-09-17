#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <time.h>


#include "Header.h"
#include "Sequence.h"
#include "LearnBox.h"
#include "ApplianceUtility.h"
#include "ScoreBoard.h"
#include "Input.h"


void ModeSelect();
void ModeLearnBox(bool ran = false);
void ModeSequence(bool ran = false);
bool Continue(IMode&, ScoreBoard&);
void Reset(IMode&, ScoreBoard&);
void Save(IMode&, ScoreBoard&);


bool running = true;


int main() {
	while (running) ModeSelect();

	return 0;
}


void ModeSelect() {
	system("cls");
	std::puts("\n Choose mode. (1: Learn Box   |  2: Random Learn Box)\n"
			    "              (3: Sequential  |  4: Random Sequential)");

	switch (*Input(1).GetInput()) {
		case '1': default: ModeLearnBox();	   break;
		case '2':		   ModeLearnBox(true); break;
		case '3':		   ModeSequence();	   break;
		case '4':		   ModeSequence(true); break;
	}
}

void ModeLearnBox(bool ran) {
	const int length = (sizeof(appliances) / sizeof(appliances[0]));

	ApplianceUtility appUtil(appliances, length);
	LearnBox learnBox(&appUtil, 5, ran);
	ScoreBoard scoreBoard(1, 5, -1);

	do {
		system("cls");

		scoreBoard.DisplayScore();
		scoreBoard.UpdateScore(learnBox.NextWord());
	} while (Continue(learnBox, scoreBoard));
}

void ModeSequence(bool ran) {
	const int length = (sizeof(appliances) / sizeof(appliances[0]));

	ApplianceUtility appUtil(appliances, length);
	Sequence sequence(&appUtil, ran);
	ScoreBoard scoreBoard(1, 5, -1, 2);

	do {
		system("cls");

		scoreBoard.DisplayScore();
		scoreBoard.UpdateScore(sequence.NextWord());
	} while (Continue(sequence, scoreBoard));
}

bool Continue(IMode& mode, ScoreBoard& board) {
	Save(mode, board);

	std::puts(" Continue? (Enter: Continue  |  R: Reset  |  M: Mode Select  |  Q: Quit)");
	
	switch (*Input(1).GetInput()) {
		case 'Q': case 'q': running = false;
		case 'M': case 'm': return false;
		case 'R': case 'r': Reset(mode, board);
		default: return true;
	}
}

void Reset(IMode& mode, ScoreBoard& board) {
	mode.Reset();
	board.Reset();
}

void Save(IMode& mode, ScoreBoard& board) {
	mode.Save();
	board.Save();
}