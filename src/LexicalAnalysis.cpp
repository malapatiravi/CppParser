
/////////////////////////////////////////////////////////////////////
// Tokenizer.cpp - read words from a std::stream                   //
// ver 3.2                                                         //
// Language:    Eclipse Mars                            //
// Application: Parser component, CSE687 - Object Oriented Design  //
// Author:      Ravichandra Malapati, Syracuse University, CST 4-174        //
//              rmalapat@syr.edu                              //
/////////////////////////////////////////////////////////////////////
// LexicalAnalysis.cpp: implementation of the LexicalAnalysis class.
//
//////////////////////////////////////////////////////////////////////

#include "LexicalAnalysis.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LexicalAnalysis::LexicalAnalysis(string in) :
		input(in), charClass(ERROR), nextChar(' '), lexeme("")
{
	getChar();
}

LexicalAnalysis::~LexicalAnalysis()
{

}

void LexicalAnalysis::setNewInput(string in)
{
	input = in;
	getChar();

}

void LexicalAnalysis::getChar()
{
	if (input.size() > 0)
	{
		nextChar = input[0];
		input.erase(0, 1);
	}
	else
		nextChar = '$';

	charClass = ERROR;

	if ((nextChar > 64 && nextChar < 91) || (nextChar > 96 && nextChar < 123))
		charClass = LETTER;

	if (nextChar > 47 && nextChar < 58)
		charClass = DIGIT;

	if (nextChar == ' ')
		charClass = SPACE;
	if (nextChar == '$')
		charClass = STOP;
	if (nextChar == '+')
		charClass = PLUS_CODE;

}

void LexicalAnalysis::addChar()
{
	lexeme += nextChar;
}

int LexicalAnalysis::lex()
{

	lexeme = "";

	while (charClass == SPACE)
		getChar();

	if (charClass == ERROR)
	{
		addChar();
		getChar();
		return ERROR;
	}
	if (charClass == STOP)
	{
		return STOP;
	}

	switch (charClass)
	{
	case LETTER:
		addChar();
		getChar();
		while (charClass == LETTER || charClass == DIGIT)
		{
			addChar();
			getChar();
		}
		return IDENT;
		break;
	case DIGIT:
		addChar();
		getChar();
		while (charClass == DIGIT)
		{
			addChar();
			getChar();
		}
		return INT_LIT;
		break;
	case PLUS_CODE:
		addChar();
		getChar();
		return PLUS_CODE;
		break;
	}

}
