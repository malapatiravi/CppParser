// LexicalAnalysis.h: interface for the LexicalAnalysis class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(_LA_)
#define _LA_

#include <iostream>
#include <string>


using namespace std;

enum {DIGIT, LETTER, IDENT, INT_LIT, ERROR, SPACE, STOP, PLUS_CODE};

class LexicalAnalysis  
{

public:
	char nextChar;
	int charClass;
	string lexeme;

private:
	string input;

public:
	int lex();
	void setNewInput(string in);
	LexicalAnalysis(string in="");
	virtual ~LexicalAnalysis();




private:
	void addChar();
	void getChar();
};


#endif