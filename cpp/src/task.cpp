
#include <iostream>
#include <fstream>
#include <vector>
#include "Token.h"
#include "Scanner.h"
#include "Parser_.h"

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

		tokens.pop_back();
		////////////////////////////////// PARSER:

		Parser_ parse(scan1, tokens);

		if (parse.parse()) {
			std::cout << "accept" << std::endl;
		}
		else {
			std::cout << "reject" << std::endl;
		}

		//std::cout<<parse.parse()<<std::endl;

	}
	else { std::cout << "Error was unable to open file!" << std::endl; }
	ifs.close();
}