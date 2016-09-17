#pragma once


class ScoreBoard {
public:
	ScoreBoard(int, int, int, int m = 1);

	void DisplayScore();
	void UpdateScore(int);
	void Reset() { score = 0; }
	void Save();

	~ScoreBoard();

private:
	int score;
	int tipScore;
	int rightScore;
	int wrongScore;

	int mode;
};