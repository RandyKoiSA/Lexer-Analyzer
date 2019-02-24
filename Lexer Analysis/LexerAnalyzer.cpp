#include "pch.h"
#include "LexerAnalyzer.h"
#include <fstream>
#include <iostream>
#include <ctype.h>
#include <vector>

/*
epsilon = { l, d, others }
states = { 1, 2, 3 }
initalState = {1}
finalState = {3}
N = 
+===+===+===+========+
|   | l | d | others |
+===+===+===+========+
| 1 | 2 | 2 | 3      |
+===+===+===+========+
| 2 | 2 | 2 | 1      |
+===+===+===+========+
| 3 | ? | ? | ?      |
+===+===+===+========+
*/

/* Constructor */
LexerAnalyzer::LexerAnalyzer()
{
	currentState = 1;
	section = NULL;	
	keywords = new string[13]{
		"int", "float", "bool", "if", "else",
		"do", "while", "whileend", "doend", "for",
		"and", "or", "function"
	};

	seperators = new string[13]{
		"(", ")", "'", "{", "}",
		"[", "]", ",", ".", ":",
		";", "!", " "
	};
	operators = new string[8]{
		"*", "+", "-", "=", "/",
		">", "<", "%"
	};
}

/* Deconstructor */
LexerAnalyzer::~LexerAnalyzer()
{
}

void LexerAnalyzer::analyzeLexeme(string textFile)
{
	fstream fin(textFile);
	char ch;

	// check if the file exist
	if (!fin.is_open()) {
		cerr << "error while opening the text file\n";
		return;
	}
	else {
		cout << "Successfully opened file\n";
	}

	// continues to run until the end n
	while (!fin.eof()) {
		ch = fin.get();

		/* IMPLEMENT A 2D ARRAY HERE TO FIND OUT WHICH STATE TO GO TO WHEN
		 CERTAIN CHARACTER SHOWS UP
		 */

		switch (currentState) {
			case 1: // check if letter | number | operator | seperator
				stateOne(ch);
				break;
			case 2: 
				stateTwo(ch);
				break;
			case 3:
				stateThree(ch);
				break;
		}
	}

	fin.close();
}

void LexerAnalyzer::stateOne(char ch)
{
	if (isalpha(ch)) {
		currentState = 2;
		buffer.push_back(ch);
	}
	else if(isalnum(ch)) {
		currentState = 2;
	}
	else {
		currentState = 3;
	}

}

// State Two finds if the word is a identifier
void LexerAnalyzer::stateTwo(char ch)
{
	if (isalpha(ch) || isalnum(ch)) {
		currentState = 2;
		buffer.push_back(ch);
		cout << ch;
	}
	else {
		currentState = 3;
	}
}

void LexerAnalyzer::stateThree(char ch)
{
	// end of identifying a identifier
	// check if identifier is a keyword
	// add seperator into token / tokentype
	cout << "Seperator" << endl;
	currentState = 1;
}

void LexerAnalyzer::stateFour(char ch)
{
}

bool LexerAnalyzer::isSeperator(char ch)
{

	return false;
}

bool LexerAnalyzer::isOperator(char ch)
{
	return false;
}
