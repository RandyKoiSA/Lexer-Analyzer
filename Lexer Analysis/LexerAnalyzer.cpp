#include "pch.h"
#include "LexerAnalyzer.h"
#include <fstream>
#include <iostream>
#include <ctype.h>

LexerAnalyzer::LexerAnalyzer()
{
	keywords = new string[19]{
		"function", "if", "ifend",
		"while", "whileend", "return",
		"int", "real", "boolean", "else",
		"elseend", "get", "put", "true", "false",
		"and", "or", "xor", "not"
	};
	seperators = new string[8]{
		"{", "}", "(", ")", "[", "]", ",", 
		"$$"
	};
	operators = new string[3]{
		">", "<", "<="
	};
}


LexerAnalyzer::~LexerAnalyzer()
{
}

void LexerAnalyzer::setSourceCode(string textFile)
{
	fstream fin(textFile);
	char ch;
	if (!fin.is_open()) {
		cerr << "error while opening the text file\n";
		exit(0);
	}
	else {
		cout << "Successfully opened file\n";
	}

	while (!fin.eof()) {
		ch = fin.get();
		cout << ch << endl;
	}

	fin.close();
}
