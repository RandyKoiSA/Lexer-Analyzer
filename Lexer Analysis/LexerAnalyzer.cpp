#include "pch.h"
#include "LexerAnalyzer.h"
#include <fstream>
#include <iostream>
#include <ctype.h>
#include <vector>
LexerAnalyzer::LexerAnalyzer()
{
	keywords = new string[19]{
		"function", "if", "ifend",
		"while", "whileend", "return",
		"int", "real", "boolean", "else",
		"elseend", "get", "put", "true", "false",
		"and", "or", "xor", "not"
	};
	seperators = new string[7]{
		"{", "}", "(", ")", "[", "]", ","
	};
	operators = new string[2]{
		">", "<"
	};
}


LexerAnalyzer::~LexerAnalyzer()
{
}

void LexerAnalyzer::setSourceCode(string textFile)
{
	fstream fin(textFile);
	// check if the file will open
	char ch;
	if (!fin.is_open()) {
		cerr << "error while opening the text file\n";
		return;
	}
	else {
		cout << "Successfully opened file\n";
	}

	while (!fin.eof()) {
		ch = fin.get();
		if (ch == ' ' || ch == '\n') {

		}
		else cout << ch << endl;
	}

	fin.close();
}
