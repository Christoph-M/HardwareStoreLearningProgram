#pragma once


class Input {
public:
	Input(const int sz = 100);

	char* GetInput();
	bool CheckInput(char*, char*);

	~Input();

private:
	const int size;
	char* input;
};