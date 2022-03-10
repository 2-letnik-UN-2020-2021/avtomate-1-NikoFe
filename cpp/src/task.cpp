// Vaja_0201.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>



class Token
{
private:
	std::string lexem;
	std::string token;
	bool eof;


public:
	Token(const std::string lexemp, std::string tokenp, bool eofp) :lexem(lexemp), token(tokenp), eof(eofp) {};

	Token() : lexem(""), token(""), eof(false) {};

	std::string getLexem() {
		return this->lexem;
	}
	std::string getToken() {
		return this->token;
	}
	bool getEof() {
		return this->eof;
	}


};

//std::vector<Token>tokens;

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

		/*for (int i = 0; i < noOfStates; i++) {
			for (int j = 0; j < 256; j++) {
				std::cout << automat[i][j] << " ";

			}
			std::cout << "\n";
		}*/

		////////////////////////////////////////////////
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
						//	char current;
						while (file->peek() != '\n') {
							//	current = file->peek();
							file->get();
						}
						//current = file->peek();
						file->get();
						//current = file->peek();
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


std::string typeFileName() {
	std::string name;
	std::cout << "Please type in the file name:" << std::endl;
	std::cin >> name;
	return name;
}



int main(int argc, char** argv)
{
	std::ifstream ifs(argv[1]);
	std::string input;
	//std::ifstream ifs("email.txt");
	//ifs >> input;
	//std::cout << input << std::endl;


	std::vector<Token>tokens;
	//std::string fileName = typeFileName();
	//std::ifstream file(fileName);

	if (ifs.is_open()) {

		Scanner scan1(&ifs);

		do {
			tokens.push_back(scan1.getNextToken());
		} while (!tokens[tokens.size() - 1].getEof());

		//std::cout << "Made it inside!" << std::endl;

		for (int i = 0; i < tokens.size() - 1; i++) {
			std::cout << tokens[i].getToken() + "(\"" + tokens[i].getLexem() + "\") ";
		}
		std::cout << "\n" << std::endl;

	}
	else { std::cout << "Error was unable to open file!" << std::endl; }
	ifs.close();



}

