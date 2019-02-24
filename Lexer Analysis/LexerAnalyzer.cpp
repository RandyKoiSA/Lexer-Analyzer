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
			case 0:
				break;
			}
		} while (!fin.eof());
	}
	else {
		printf("No FILES to analyze.\n");
	}
}

	/*
	Using a do-while to gaurantee it goes to state one
	*/


void LexerAnalyzer::stateOne() // the inital state
{
	cout << " @STATE 1\n";
	char ch = getNextCharacter();
	cout << ch << ": ";
	if (isOperator(ch)) {
		cout << "is operator\n";
		currentState = 1;
	}
	else if (isSeperator(ch)) {
		cout << "is seperator\n";
		currentState = 1;
	}
	else if (isalpha(ch)) {
		buffer[j++] = ch;
		cout << "Going to state 2\n";
		currentState = 2;
	}
	else if (isdigit(ch)) {
		cout << "is digit \n";
		currentState = 1;
	}
	else {
		cout << "Unknown character was inputed.\n";
	}

}

// State Two finds if the word is a identifier
void LexerAnalyzer::stateTwo()
{
	char ch = getNextCharacter();
	cout << ch << ": ";
	if (isalpha(ch)) {
		buffer[j++] = ch;
		cout << ch << " is a letter\n";
		currentState = 2;
	}
	else if (isalnum(ch)) {
		buffer[j++] = ch;
		cout << ch << " is a digit\n";
		currentState = 2;
	}
	else{
		buffer[j] = '\0';
		j = 0;
		cout << buffer << " is identifier\n";
		if (isSeperator(ch)) {
			cout << " is seperator\n";
		}
		else if (isOperator(ch)) {
			cout << " is operator\n";
		}
		else {
			cout << " undefined character\n";
		}
		currentState = 1;
	}
}

void LexerAnalyzer::stateThree()
{
	// end of identifying a identifier
	// check if identifier is a keyword
	// add seperator into token / tokentype
	cout << " is a digit(3)\n";
	currentState = 1;
}

void LexerAnalyzer::stateFour()
{
	cout << "is operator / seperators\n";
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


