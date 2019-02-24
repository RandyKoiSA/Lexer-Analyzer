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

	bool isSeperator(char ch);
	bool isOperator(char ch);
	bool isKeyword(char buffer[]);

	void loadTextFile(string textFile);
	void isTextFileOpen();
	char getNextCharacter();
private:
	int section;
	int currentState;

	fstream fin;
	string currentFile;

	vector<string> tokens;
	vector<string> tokensType;

	char *buffer;
	int j;
	char ch;
};

