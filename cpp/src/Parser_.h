#pragma once
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Token.h"
#include "Scanner.h"

class Parser_ {

private:
	Scanner scan;
	std::vector<Token>tokens;
	int tokenIndex = 0;
	bool stop = false;

public:
	Parser_(Scanner scanp, std::vector<Token> tokensp) :scan(scanp), tokens(tokensp) {};
	//	this->scan = scanp
		//	this->tokens = tokensp;


	bool parse() {
		try{
			callE();
		}
		catch (std::exception e) {
			if (tokenIndex == tokens.size()) {
				return true;
			}
			else return false;
		}
	}

		void callE() {
			try{
			callT();
			callEE();
			}catch(std::exception e){}
		}

		void callEE() {
			try{
			if (tokens.at(tokenIndex).getToken() == "plus") {
				tokenIndex++;
				callT();
				callEE();
			}
			if (tokens.at(tokenIndex).getToken() == "minus") {
				tokenIndex++;
				callT();
				callEE();
			}
			}catch(std::exception e){}
		}

		void callT() {
			try{
			callF();
			callTT();
			}catch(std::exception e){}
		}

		void callTT() {
			try{
			if (tokens.at(tokenIndex).getToken() == "times") {
				tokenIndex++;
				callF();
				callTT();

			}
			if (tokens.at(tokenIndex).getToken() == "divide") {
				tokenIndex++;
				callF();
				callTT();

			}
			if (tokens.at(tokenIndex).getToken() == "pow") {
				tokenIndex++;
				callF();
				callTT();

			}
			}catch(std::exception e){}
		}

		void callF() {
			try{
			if (tokens.at(tokenIndex).getToken() == "lparen") {
				tokenIndex++;
				callE();
				if (tokens.at(tokenIndex).getToken() == "rparen") {
					tokenIndex++;

				}
				else   throw "Exit!";

			
			}
			else if (tokens.at(tokenIndex).getToken() == "float") {
				tokenIndex++;
			}
			else if (tokenIndex + 1 < tokens.size() && tokens.at(tokenIndex).getToken() == "minus") {
				if (tokens.at(tokenIndex + 1).getToken() == "float") {
					tokenIndex += 2;
				}

			}

			else if (tokens.at(tokenIndex).getToken() == "variable") {
				tokenIndex++;
			}
			else { throw "Exit!"; }
			}
			catch(std::exception e){}
		}

};