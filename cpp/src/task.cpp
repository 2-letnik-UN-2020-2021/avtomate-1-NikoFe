// Vaja_0201.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "Token.h"
#include "Scanner.h"


int main(int argc, char** argv)
{
	std::ifstream ifs(argv[1]);
	std::string input;
	std::vector<Token>tokens;

	if (ifs.is_open()) {

		Scanner scan1(&ifs);

		do {
			tokens.push_back(scan1.getNextToken());
		} while (!tokens[tokens.size() - 1].getEof());


		for (int i = 0; i < tokens.size() - 1; i++) {
			std::cout << tokens[i].getToken() + "(\"" + tokens[i].getLexem() + "\") ";
		}
		std::cout << "\n" << std::endl;

	}
	else { std::cout << "Error was unable to open file!" << std::endl; }
	ifs.close();

}