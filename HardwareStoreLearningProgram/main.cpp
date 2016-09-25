#include <cstdio>
#include <Windows.h>

#pragma comment(lib, "winmm.lib")


#include "Header.h"
#include "Sequence.h"
#include "LearnBox.h"
#include "ApplianceUtility.h"
#include "ScoreBoard.h"
#include "Input.h"


void ModeSelect();
void RunMode(IMode&, ScoreBoard&);
bool Continue(IMode&, ScoreBoard&);
void Reset(IMode&, ScoreBoard&);
void Save(IMode&, ScoreBoard&);


bool running = true;


int main() {
	CreateDirectory(L"save", NULL);

	while (running) ModeSelect();

	return 0;
}


void ModeSelect() {
	ApplianceUtility appUtil(appliances, sizeof(appliances) / sizeof(appliances[0]));

	system("cls");
	std::puts("\n Choose mode. (1: Learn Box   |  2: Random Learn Box)\n"
			    "              (3: Sequential  |  4: Random Sequential)");

	switch (*Input(1).GetInput()) {
		case '1': default: RunMode(LearnBox(&appUtil, 5, false), ScoreBoard(1, 5, -1, 1)); break;
		case '2':		   RunMode(LearnBox(&appUtil, 5, true ), ScoreBoard(1, 5, -1, 2)); break;
		case '3':		   RunMode(Sequence(&appUtil, false),	 ScoreBoard(1, 5, -1, 3)); break;
		case '4':		   RunMode(Sequence(&appUtil, true ),	 ScoreBoard(1, 5, -1, 4)); break;
	}
}

void RunMode(IMode& mode, ScoreBoard& board) {
	do {
		system("cls");

		board.DisplayScore();
		board.UpdateScore(mode.NextWord());
	} while (Continue(mode, board));
}

bool Continue(IMode& mode, ScoreBoard& board) {
	Save(mode, board);

	std::puts(" Continue? (Enter: Continue  |  P: Play Music  |  R: Reset)\n"
			  "           (M: Mode Select   |  Q: Quit)");
	
	switch (*Input(1).GetInput()) {
		case 'Q': case 'q': running = false;
		case 'M': case 'm': return false;
		case 'P': case 'p': PlaySound(L"hardware_store.wav", NULL, SND_FILENAME | SND_ASYNC); return true;
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