#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <time.h>


#include "Header.h"
#include "Sequence.h"
#include "LearnBox.h"
#include "ScoreBoard.h"
#include "Input.h"


void ModeSelect();
void ModeLearnBox();
void ModeSequence();
bool Continue(IMode&, ScoreBoard&);
void Reset(IMode&, ScoreBoard&);
void Save(IMode&, ScoreBoard&);


int main() {
	ModeSelect();

	return 0;
}


void ModeSelect() {
	system("cls");
	std::puts("\n Choose mode. (1: Learn Box  |  2: Sequential)");

	switch (*Input(1).GetInput()) {
	case '1': default:
		ModeLearnBox(); break;

	case '2':
		ModeSequence(); break;
	}
}

void ModeLearnBox() {
	const int length = (sizeof(appliances) / sizeof(appliances[0]));

	LearnBox learnBox = LearnBox(appliances, length, 5);
	ScoreBoard scoreBoard = ScoreBoard(1, 5, -1);

	do {
		system("cls");

		scoreBoard.DisplayScore();
		scoreBoard.UpdateScore(learnBox.NextWord());
	} while (Continue(learnBox, scoreBoard));
}

void ModeSequence() {
	const int length = (sizeof(appliances) / sizeof(appliances[0]));

	Sequence sequence = Sequence(appliances, length);
	ScoreBoard scoreBoard = ScoreBoard(1, 5, -1, 2);

	do {
		system("cls");

		scoreBoard.DisplayScore();
		scoreBoard.UpdateScore(sequence.NextWord());
	} while (Continue(sequence, scoreBoard));
}

bool Continue(IMode& box, ScoreBoard& board) {
	Save(box, board);

	std::puts(" Continue? (Enter: Continue  |  R: Reset  |  M: Mode Select  |  Q: Quit)");
	
	switch (*Input(1).GetInput()) {
		case 'M': case 'm': ModeSelect();	// Gobshite, I fecking banjaxed this bombay shitehawk, jaysus!
		case 'Q': case 'q': return false;
		case 'R': case 'r': Reset(box, board);
		default: return true;
	}
}

void Reset(IMode& box, ScoreBoard& board) {
	box.Reset();
	board.Reset();
}

void Save(IMode& box, ScoreBoard& board) {
	box.Save();
	board.Save();
}