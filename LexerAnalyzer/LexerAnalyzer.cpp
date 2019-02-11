// LexerAnalyzer.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Author: Randy Le
Author's Email: 97randy.le@gmail.com
Class: CPSC 323 Compilers and Languages
Draft Due: Monday 2/18
Fina Due Date: Thursday 2/21
About:
*/

#include "pch.h"
#include <iostream>
#include <string>
#include <sstream>
#include "LexerAnalyzer.h"

// pre-initialized methods
void LexerAnalyzer(std::string str);

int main()
{
	std::string input;
	std::string stars = "*****";
	std::cout << stars << "Lexer Analyzer" << stars << std::endl;
	std::cout << ">>";
	std::getline(std::cin, input);
	LexerAnalyzer(input);
		return 0;
}

void LexerAnalyzer(std::string str) {
	std::stringstream ss(str);
	// storing the whole string into a string stream
	// ss << str;

	// running loop until the end of string
	std::string value;
	while (!ss.eof()) {
		// extracting word by word
		ss >> value;

		std::cout << value << std::endl;

		value = "";
	}

}

LexerAnalyzer::LexerAnalyzer()
{
}


LexerAnalyzer::~LexerAnalyzer()
{
}
