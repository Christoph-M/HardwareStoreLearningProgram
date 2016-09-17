#include "Input.h"

#include <cstdio>
#include <iostream>


Input::Input(const int sz) :
	size(sz + 1),
	input(new char[size] { '\0' })
{ }


char* Input::GetInput() {
	printf("\n :> ");
	std::cin.getline(input, size);
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	puts("");

	return input;
}

bool Input::CheckInput(char* inpt, char* word) {
	if (*inpt == '\0') return false;

	bool correctAnswer = true;

	for (int i = 0; word[i] != '\0'; ++i)
		if (inpt[i] != word[i] || (inpt[i] == '\0' && word[i] != '\0')) {
			correctAnswer = false; break;
		}

	return correctAnswer;
}


Input::~Input() {
	delete[](input);
}