#pragma once
#include <string>
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
	string *tokens;
	string *tokenType;

};

