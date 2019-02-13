// Lexer Analysis.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <sstream>
#include "LexerAnalyzer.h"

using namespace std;
int main()
{
	string input;
	cout << "*****Lexer Analysis****" << endl;
	while (input != "quit") {
		cout << ">> Enter File Name: ";
		getline(cin, input);


		LexerAnalyzer la;
		la.setSourceCode(input);
	}
	return 0;
}
