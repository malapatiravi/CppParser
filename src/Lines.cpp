/////////////////////////////////////////////////////////////////////
// Tokenizer.cpp - read words from a std::stream                   //
// ver 3.2                                                         //
// Language:    Eclipse Mars                            //
// Application: Parser component, CSE687 - Object Oriented Design  //
// Author:       Ravichandra Malapati, Syracuse University, CST 4-174        //
//              rmalapat@syr.edu                              //
/////////////////////////////////////////////////////////////////////

//#define TEST_LINES

#include "Lines.h"
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <exception>
#include "Tokenizer.h"

using namespace Scanner;

Lines::Lines(Toker* pToker) :
		_pToker
		{ pToker }
{

}

void Lines::show()
{
	std::cout << "\n  ";
	for (auto token : _tokens)
		if (token != "\n")
			std::cout << token << " ";
	std::cout << "\n";
}

bool Lines::get()
{
	bool start = false;
	_tokens.clear();
	while (true)
	{
		std::string token = _pToker->getTok();
		if (token == "}")
		{
			_tokens.push_back(token);
			start = false;
			return true;
		}

		else if (token == "{")
		{
			start = true;
			_tokens.push_back(token);

		}
		else if (start == true)
			_tokens.push_back(token);
	}
	return false;

}

Token Lines::operator [](size_t n)
{
	if (n < 0 || n >= _tokens.size())
		throw(std::invalid_argument("index out of range"));
	return _tokens[n];
}
size_t Lines::length()
{
	return _tokens.size();
}
#ifdef TEST_LINES

int main()
{
	Toker toker;
	std::string fileSpec =
			"/home/malz/workspace/new_workspace/Tokenizer/src/Tokenizer.cpp";
	std::fstream in(fileSpec);
	if (!in.good())
	{
		std::cout << "\n  can't open file " << fileSpec << "\n\n";
		return 1;
	}

	toker.attach(&in);

	Lines semi(&toker);

	while (semi.get())
	{
		std::cout << "\n  -- statements --";
		semi.show();
	}

	/* May have collected tokens, but reached end of stream
	 before finding SemiExp terminator.*/

	if (semi.length() > 0)
	{
		std::cout << "\n  -- statements --";
		semi.show();
		std::cout << "\n\n";
	}
	return 0;
}
#endif
