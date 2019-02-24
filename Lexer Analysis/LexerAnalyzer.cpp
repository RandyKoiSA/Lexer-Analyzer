#include "pch.h"
#include "LexerAnalyzer.h"
#include <fstream>
#include <iostream>
#include <ctype.h>
#include <vector>
#include <stdio.h>

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
	buffer = new char[1000];
	j = 0;
}

/* Deconstructor */
LexerAnalyzer::~LexerAnalyzer()
{
}

void LexerAnalyzer::analyzeLexeme()
{
	if (fin.is_open()) {
		do {
			switch (currentState) {
			case 1:
				stateOne();
				break;
			case 2:
				stateTwo();
				break;
			case 3:
				stateThree();
				break;
			case 4:
				stateFour();
				break;
			case 5:
				stateFive();
			case 6:
				stateSix();
			case 0:
				break;
			}
		} while (!fin.eof());
		printLexeme();
	}
	else {
		printf("No FILES to analyze.\n");
	}
}

void LexerAnalyzer::printLexeme()
{
	printf("========LEXEME========\n");
	for (int i = 0; i < tokens.size(); i++) {
		cout << tokens[i] << "\t" << tokensType[i] << endl;
	}
}

void LexerAnalyzer::stateOne() // the inital state
{
	// cout << " @STATE 1\n";
	ch = getNextCharacter();
	// cout << ch << ": ";
	if (isOperator(ch)) {
		// cout << "is operator\n";
		currentState = 5;
	}
	else if (isSeperator(ch)) {
		// cout << "is seperator\n";
		currentState = 4;
	}
	else if (isalpha(ch)) {
		buffer[j++] = ch;
		// cout << "Going to state 2\n";
		currentState = 2;
	}
	else if (isdigit(ch)) {
		// cout << "is digit \n";
		currentState = 6;
	}
}

// State Two finds if the word is a identifier
void LexerAnalyzer::stateTwo()
{
	ch = getNextCharacter();
	// cout << ch << ": ";
	if (isalpha(ch)) {
		buffer[j++] = ch;
		// cout << ch << " is a letter\n";
		currentState = 2;
	}
	else if (isalnum(ch)) {
		buffer[j++] = ch;
		// cout << ch << " is a digit\n";
		currentState = 2;
	}
	else{
		currentState = 3;
	}
}

// state three is the end of finding an identifier / keyword
void LexerAnalyzer::stateThree()
{
	// check if identifier is a keyword
	buffer[j] = '\0';
	j = 0;
	// cout << buffer;
	tokens.push_back(buffer);
	if (isKeyword(buffer)) {
		// cout << " is keyword";
		tokensType.push_back("keyword");
	}
	else {
		// cout << " is identifier";
		tokensType.push_back("identifier");
	}

	if (isSeperator(ch)) currentState = 4;
	else if (isOperator(ch)) currentState = 5;
	else currentState = 1;
}

// state four is when a seperator is found
void LexerAnalyzer::stateFour()
{
	// cout << "is operator / seperators\n";
	tokens.push_back(string(1, ch));
	tokensType.push_back("seperator");
	currentState = 1;
}

// state five is when a operator is found
void LexerAnalyzer::stateFive()
{
	tokens.push_back(string(1, ch));
	tokensType.push_back("operator");
	currentState = 1;
}

// state six is when a digit is found
void LexerAnalyzer::stateSix()
{
	currentState = 1;
}


bool LexerAnalyzer::isSeperator(char ch)
{
	char seperators[13] {
		'(', ')', '\'', '{', '}',
		'[', ']', ',', '.', ':',
		';', '!', ' '
	};

	for (int i = 0; i < 13; i++)
		if (ch == seperators[i]) return true;
	return false;
}

bool LexerAnalyzer::isOperator(char ch)
{
	char operators[8]{
		'*', '+', '-', '=', '/',
			'>', '<', '%'
	};
	
	for (int i = 0; i < 8; i++)
		if (ch == operators[i]) return true;
	return false;
}

bool LexerAnalyzer::isKeyword(char buffer[])
{
	char keywords[13][10]{
	"int", "float", "bool", "if", "else",
	"do", "while", "whileend", "doend", "for",
	"and", "or", "function"
	};

	for (int i = 0; i < 13; i++)
		if (strcmp(buffer, keywords[i]) == 0) return true;
	return false;
}

void LexerAnalyzer::loadTextFile(string textFile)
{
	fin.open(textFile);
	if (!fin.is_open()) printf("Unable to open file: %s \n", textFile.c_str());
	else {
		printf("Successfully opened file: %s \n", textFile.c_str());
		currentFile = textFile;
	}
}

// may remove
void LexerAnalyzer::isTextFileOpen()
{
	if (fin.is_open()) printf("text file %s is currently open", currentFile.c_str());
	else printf("no text file loaded yet");
}

char LexerAnalyzer::getNextCharacter()
{
	if (!fin.eof()) {
		return fin.get();
	}
	else {
		printf("Reached the end of the file or file did not exist.\n");
		fin.close();
		return NULL;
	}
}


