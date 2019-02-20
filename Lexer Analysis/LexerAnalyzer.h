#pragma once
#include <string>
#include <vector>
using namespace std;
class LexerAnalyzer
{
public:
	LexerAnalyzer();
	~LexerAnalyzer();

	void setSourceCode(string textFile);
private:
	string *keywords;
	string *seperators;
	string *operators;
	vector<string> tokens;
	vector<string> tokenType;
	int currentState;
};

