#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include <string>

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
#endif //TOKEN_H