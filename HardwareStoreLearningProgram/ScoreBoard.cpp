#include "ScoreBoard.h"

#include <cstdio>
#include <fstream>

#include "LearnBox.h"


ScoreBoard::ScoreBoard(int tip, int right, int wrong, int m) :
	score(0),
	tipScore(tip),
	rightScore(right),
	wrongScore(wrong),
	mode(m)
{
	char fileName[25] = { '\0' };
	std::snprintf(fileName, 25, "save\\save.myscore%d", mode);

	std::ifstream file;
	file.open(fileName);

	if (file.is_open()) {
		char charScore[7] = { '\0' };
		for (int i = 0; i < 7; ++i) charScore[i] = file.get() - '0';
		score = atoi(charScore);
		file.close();
	}
}


void ScoreBoard::DisplayScore() {
	printf("\n Current score: %06d\n", score);
}

void ScoreBoard::UpdateScore(int type) {
	switch (type) {
		case WRONG: score += wrongScore; printf("%+d Point(s)", wrongScore); break;
		case RIGHT: score += rightScore; printf("%+d Point(s)", rightScore); break;
		case TIP:	score += tipScore;	 printf("%+d Point(s)", tipScore);   break;
		default: printf("\n\n ##############################"
						  "\n # ERROR: Unknown score type! #\n"
							" ##############################\n\n"); break;
	}

	score = (score < 0) ? 0 : ((score > 999999) ? 999999 : score);

	printf(" -> %06d\n\n", score);
}

void ScoreBoard::Save() {
	char fileName[25] = { '\0' };
	std::snprintf(fileName, 25, "save\\save.myscore%d", mode);

	std::ofstream file;
	file.open(fileName, std::ios::out | std::ios::trunc);
		char charScore[7] = { '\0' };
		std::snprintf(charScore, 7, "%d", score);
		for (char digit : charScore) file.put(static_cast<char>(digit) + '0');
	file.close();
}


ScoreBoard::~ScoreBoard() {
	
}