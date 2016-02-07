// SyntaxAnalysis.h: interface for the SyntaxAnalysis class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(_SA_)
#define _SA_

#include <iostream>
#include <string>
#include "LexicalAnalysis.h"

using namespace std;
/*
 Works for grammar
 EXPR ::= TERM {+ TERM}
 TERM ::= IDENT | INTEGER
 ...

 OR
 EXPR ::= (IDENT | INTEGER) {+ (IDENT | INTEGER)}


 */

class SyntaxAnalysis
{
public:
	void syntax();
	void setNewInput(string in);
	SyntaxAnalysis(string in);
	virtual ~SyntaxAnalysis();

private:
	void term();
	void expr();

private:
	LexicalAnalysis LA;
	int nextToken;
};

#endif
