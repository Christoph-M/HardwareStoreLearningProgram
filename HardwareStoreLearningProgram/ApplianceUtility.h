#pragma once


class ApplianceUtility {
public:
	ApplianceUtility(char**, int);

	int NumWords() { return numWords; }
	char* GetWord(int word = 0);
	char* GetNextWord(int word = 0);
	void DisplayWord(int word = 0);
	void DisplayTips(int word = 0);
	void DisplayResult(bool, int word = 0);
	int NextWordIndex(int word = 0);

	~ApplianceUtility();

private:
	const int numWords;

	char** appliances;
};