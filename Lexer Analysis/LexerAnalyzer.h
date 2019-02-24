#pragma once
#include <string>
#include <vector>
using namespace std;

class LexerAnalyzer
{
public:
	LexerAnalyzer();
	~LexerAnalyzer();

	void analyzeLexeme(string textFile);
	void stateOne(char ch);
	void stateTwo(char ch);
	void stateThree(char ch);
	void stateFour(char ch);

	bool isSeperator(char ch);
	bool isOperator(char ch);
private:
	string *keywords;
	string *seperators;
	string *operators;

	int state;
	int section;
	int currentState;

	int table[3][3] = {
		{2, 2, 3},
		{2, 2, 1},
		{3, 3, 3}
	};

	vector<string> tokens;
	vector<string> tokenType;

	vector<char> buffer;
};

