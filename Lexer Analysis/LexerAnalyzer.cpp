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

/*
 CONSTRUCTOR
 */
LexerAnalyzer::LexerAnalyzer()
{
	currentState = 1;
	buffer = new char[1000];
	j = 0;
}

/*
 DECONSTRUCTOR
*/
LexerAnalyzer::~LexerAnalyzer()
{
}

/*
 ANALYZE LEXEME
 This is the main function of the Lexeme Analysis.
*/
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
			case 7:
				stateSeven();
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

/*
 PRINTING LEXEME RESULT METHOD
 After text file has completely scanned, it will display the
 tokens along with the tokens type.
*/
void LexerAnalyzer::printLexeme()
{
	printf("========LEXEME========\n");
	for (int i = 0; i < tokens.size(); i++) {
		cout << tokens[i] << "\t" << tokensType[i] << endl;
	}
}

/*
 STATE ONE METHOD
 State one is the initial state.
 Retrieves next character of the text file.
 Character determines what state it goes to.
*/
void LexerAnalyzer::stateOne()
{
	ch = getNextCharacter();
	if (isOperator(ch)) {
		currentState = 5;
	}
	else if (isSeperator(ch)) {
		currentState = 4;
	}
	else if (isalpha(ch)) {
		buffer[j++] = ch;
		currentState = 2;
	}
	else if (isdigit(ch)) {
		currentState = 6;
	}
	else if (ch == '!') {
		currentState = 7;
	}
}

/*
 STATE TWO METHOD
 A letter was detected.
 Scans for more letter / digits after it until seperator or operator shows.
*/
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
	else if (ch == '$') {
		buffer[j++] = ch;
		currentState = 2;
	}
	else{
		currentState = 3;
	}
}

/*
 STATE THREE METHOD
 The end of finding a identifier.
 Checks if the identifier is a keyword.
 Adds the following seperator / operator to the token / tokentype.
 Then, returns back to one.
*/
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

	if (isSeperator(ch)) {
		tokens.push_back(string(1, ch));
		tokensType.push_back("seperator");
	}
	else if (isOperator(ch)) {
		tokens.push_back(string(1, ch));
		tokensType.push_back("operator");
	}
	currentState = 1;
}

/*
 STATE FOUR METHOD
 A seperator character was found.
 Putting character in token / tokenType as a seperator.
 Then returns back to state one.
*/
void LexerAnalyzer::stateFour()
{
	// cout << "is operator / seperators\n";
	tokens.push_back(string(1, ch));
	tokensType.push_back("seperator");
	currentState = 1;
}

/*
 STATE FIVE METHOD
 An operator character was found.
 Putting the character in token / tokenType as a operator.
 Then returns back to state one.
*/
// state five is when a operator is found
void LexerAnalyzer::stateFive()
{
	tokens.push_back(string(1, ch));
	tokensType.push_back("operator");
	currentState = 1;
}


/*
 STATE SIX METHOD
 A digit character was found.
 Scans for any others digits following it.
 Then returns back to state one.
*/
void LexerAnalyzer::stateSix()
{
	currentState = 1;
}

/*
 STATE SEVEN METHOD
 detected a comment. scans for all comment character.
 Then returns back to state one.
*/
void LexerAnalyzer::stateSeven()
{
}

/*
 IS CHARACTER A SEPERATOR METHOD
 checks if the following chracter is part of the seperator list
*/
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

/*
 IS CHARATER A OPERATOR METHOD
 checks if the following character is part of the operator list
*/
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

/*
 IS IDENTIFIER A KEYWORD METHOD
 checks if the following string(buffer) is part of the keyword list.
*/
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

/*
 LOAD TEXT FILE METHOD
 loads a text file to read. If text file doesn't exist, it will display an error.
*/
void LexerAnalyzer::loadTextFile(string textFile)
{
	fin.open(textFile);
	if (!fin.is_open()) printf("Unable to open file: %s \n", textFile.c_str());
	else {
		printf("Successfully opened file: %s \n", textFile.c_str());
		currentFile = textFile;
	}
}

/*
 IS TEXT FILE OPEN? METHOD
 validates if there is a textfile loaded.
*/
void LexerAnalyzer::isTextFileOpen()
{
	if (fin.is_open()) printf("text file %s is currently open", currentFile.c_str());
	else printf("no text file loaded yet");
}

/*
 GET NEXT CHARACTER METHOD
 scans for the the next character of the loaded file.
*/
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


