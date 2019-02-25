// Lexer Analysis.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <sstream>
#include "LexerAnalyzer.h"

using namespace std;

void helpDisplay() {
	cout << "*****HELP*****" << endl;
}

int main()
{
	string input;
	cout << "*****Lexer Analysis****" << endl;
	while (input != "quit") {
		cout << ">> Enter File Name: ";
		getline(cin, input);

		if (input == "help") {
			helpDisplay();
		}
		else {
			LexerAnalyzer la;
			la.loadTextFile(input);
			la.analyzeLexeme();
		}
	}
	return 0;
}
