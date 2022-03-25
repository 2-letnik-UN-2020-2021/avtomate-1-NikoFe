#pragma once
#ifndef SCANNER_H
#define SCANNER_H
#include "Token.h"
#include <iostream>
#include <string>
#include <fstream>

class Scanner {

private:

	std::ifstream* file;
	int row;
	int columm;
	Token currentToken;
	const int static noOfStates = 13;
	const int startState = 0;
	const int deadEnd = -1;
	const int lexError = -2;

	int automat[noOfStates][256];
	std::string finalStates[noOfStates];

	void initAutomat() {

		for (int i = 0; i < noOfStates; i++) {
			for (int j = 0; j < 256; j++) {
				automat[i][j] = deadEnd;

			}
		}
		////////////////////////////////////////////////

		for (int i = '0'; i <= '9'; i++) {

			automat[0][i] = 8;
			automat[8][i] = 8;
			automat[9][i] = 10;
			automat[10][i] = 10;
			automat[11][i] = 12;
			automat[12][i] = 12;
		}

		automat[0]['+'] = 1;
		automat[0]['-'] = 2;
		automat[0]['*'] = 3;
		automat[0]['/'] = 4;
		automat[0]['^'] = 5;
		automat[0]['('] = 6;
		automat[0][')'] = 7;

		for (int i = 97; i < 122; i++) {

			automat[0][i] = 11;
			automat[0][i - 32] = 11;
			automat[11][i] = 11;
			automat[11][i - 32] = 11;

		}

		automat[8]['.'] = 9;

		finalStates[0] = "lexError";
		finalStates[1] = "plus";
		finalStates[2] = "minus";
		finalStates[3] = "times";
		finalStates[4] = "divide";
		finalStates[5] = "pow";
		finalStates[6] = "lparen";
		finalStates[7] = "rparen";
		finalStates[8] = "float";
		finalStates[9] = "lexError";
		finalStates[10] = "float";
		finalStates[11] = "variable";
		finalStates[12] = "variable";

	}
public:
	Scanner(std::ifstream* filep) {
		file = filep;
		row = 1;
		columm = 1;
		initAutomat();
	}

	Token getNextToken() {
		int currentState = startState;
		int tempState;
		int peek = file->peek();
		bool eof = false;

		if (peek == -1) {
			tempState = deadEnd;
			eof = true;
			return Token("", "lexError", eof);
		}

		std::string newLex = "";

		do {
			char current = file->peek();
			tempState = automat[currentState][file->peek()];


			if (tempState != deadEnd) {

				if (automat[currentState][file->peek()] == 4) {
					file->get();
					if (file->peek() == '/') {
						while (file->peek() != '\n') {
							file->get();
						}
						file->get();
						return getNextToken();
					}
					else file->unget();
				}
				newLex += file->get();
				// dve črti (komentar v kodi!)
				currentState = tempState;
			}
			else if (finalStates[currentState] != "lexError") {

				return Token(newLex, finalStates[currentState], eof);

			}
			else {
				file->get();
				return getNextToken();
			}


		} while (true);

	}
};
#endif //SCANNER_H
