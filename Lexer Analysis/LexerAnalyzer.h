#pragma once
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class LexerAnalyzer
{
public:
	LexerAnalyzer();
	~LexerAnalyzer();

	// main methods
	void analyzeLexeme();
	void printLexeme();

	// state methods
	void stateOne();
	void stateTwo();
	void stateThree();
	void stateFour();
	void stateFive();
	void stateSix();
	void stateSeven();

	bool isSeperator(char ch);
	bool isOperator(char ch);
	bool isKeyword(char buffer[]);

	void loadTextFile(string textFile);
	void isTextFileOpen();
	char getNextCharacter();
private:
	int section;
	int currentState;

	int table[10][5] = {
		2, 6, 5, 4, 7,
		2, 2, 3, 3, 3,
		1, 1, 1, 1, 1,
		1, 1, 1, 1, 1,
		1, 1, 1, 1, 1,
		8, 6, 8, 8, 8,
		7, 7, 7, 7, 9,
		1, 1, 1, 1, 1,
		1, 1, 1, 1, 1,
		1, 1, 1, 1, 1
		
	};
	fstream fin;
	string currentFile;

	vector<string> tokens;
	vector<string> tokensType;

	char *buffer;
	int j;
	char ch;

	bool hasStartedOnce;
};

