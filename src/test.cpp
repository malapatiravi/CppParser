/* * test.cpp
 *
 *  Created on: Feb 1, 2016
 *      Author: malz*/

#include <iostream>
#include <fstream>
using namespace std;
#ifdef TEST1
int main()
{
	bool start = false;
	int i = 0;
	ifstream fin;
	fin.open("/home/malz/workspace/new_workspace/Tokenizer/src/Tokenizer.cpp",
			ios::in);
	char my_character;
	int number_of_line = 0;
	while (!fin.eof())
	{
		fin.get(my_character);

		start=true;
		if (start == true)
		{

			cout << my_character;
			if (std::isspace(my_character)&&my_character != '\n')
			cout<<"\n";
		}
		if (my_character == '\n')
			++number_of_line;

	}
	cout << "\n Number of Lines: " << number_of_line;
}

#define _TEST_
#if !defined(_TEST_)

#include <iostream>
#include <string>
#include "LexicalAnalysis.h"
#include "SyntaxAnalysis.h"

using namespace std;

string convertToken(int t);

int main(void)
{
	std::string fileSpec =
	"/home/malz/workspace/new_workspace/Tokenizer/src/Tokenizer.cpp";
	cout << "========== Testing lexical analyzer" << endl;
	int token = SPACE;

	//Testing LexicalAnalysis
	LexicalAnalysis LA(fileSpec);

	while (token != STOP)
	{
		token = LA.lex();
		cout << "lexeme: \"" << LA.lexeme << "\"   token: "
		<< convertToken(token) << endl;
	}

	cout << endl << "========== Testing syntax analyzer" << endl;

	//Testing SyntaxAnalysis
	SyntaxAnalysis SA("a3bc+223+vd3+ghg");
	SA.syntax();
	SA.setNewInput("a+");
	SA.syntax();
	return 0;
}
#endif
string convertToken(int t)
{
	switch (t)
	{
		case SPACE:
		return "SPACE";
		case LETTER:
		return "LETTER";
		case DIGIT:
		return "DIGIT";
		case IDENT:
		return "IDENT";
		case INT_LIT:
		return "INT_LIT";
		case ERROR:
		return "ERROR";
		case STOP:
		return "STOP";
		case PLUS_CODE:
		return "PLUS_CODE";
		default:
		return "UNKNOWN";
	}

}

#endif
