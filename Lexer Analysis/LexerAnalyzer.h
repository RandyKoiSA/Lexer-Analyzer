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

	void analyzeLexeme();
	void stateOne();
	void stateTwo();
	void stateThree();
	void stateFour();

	bool isSeperator(char ch);
	bool isOperator(char ch);
	bool isKeyword(char buffer[]);

	void loadTextFile(string textFile);
	void isTextFileOpen();
	char getNextCharacter();
private:
	const int KEYWORDSIZE = 13;
	const int SEPERATORSIZE = 13;
	const int OPERATORSIZE = 8;

	const int MAXSTATES = 3;

	int section;
	int currentState;

	fstream fin;
	string currentFile;

	char *buffer;
	int j;
};

