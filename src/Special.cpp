/////////////////////////////////////////////////////////////////////
// Tokenizer.cpp - read words from a std::stream                   //
// ver 3.2                                                         //
// Language:    Eclipse Mars                            //
// Application: Parser component, CSE687 - Object Oriented Design  //
// Author:       Ravichandra Malapati, Syracuse University, CST 4-174        //
//              rmalapat@syr.edu                              //
/////////////////////////////////////////////////////////////////////

//#define TEST_SPECIAL
#include "Special.h"
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <exception>
#include "Tokenizer.h"

using namespace Scanner;

Special::Special(Toker* pToker) :
		_pToker
		{ pToker }
{

}

bool Special::get()
{
	bool check = false;
	_tokens.clear();
	int x = 0;
	while (true)
	{
		std::string token = _pToker->getTok();

		if (token == start || check == true)
		{
			check = true;
			std::cout << "\n is: " << token;
		}

		/*if (token == end)
		 {
		 _tokens.push_back(token);
		 check = false;
		 return true;
		 }

		 else if (token == start)
		 {
		 check = true;
		 _tokens.push_back(token);

		 }
		 else if (check == true)
		 _tokens.push_back(token);
		 if(start==end)
		 start="";*/
		x++;
		if (x == 500)
			return false;
	}
	return false;
}

Token Special::operator[](size_t n)
{
	if (n < 0 || n >= _tokens.size())
		throw(std::invalid_argument("index out of range"));
	return _tokens[n];
}

size_t Special::length()
{
	return _tokens.size();
}

void Special::show()
{
	std::cout << "\n  ";
	for (auto token : _tokens)
		if (token != "\n")
			std::cout << token << " ";
	std::cout << "\n";
}

bool Special::setSpecialCharspairs(std::string pair, bool two_or_not)
{
	if (two_or_not == true)
	{
		start.assign(pair, 0, 2);

		end.assign(pair, 2, 2);
	}
	if (two_or_not == false)
	{
		start.assign(pair, 0, 1);

		end.assign(pair, 1, 1);
	}
	std::cout << "\n set char start :" << start;
	std::cout << "\n set char end: " << end;

	return true;
}
#ifdef TEST_SPECIAL

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
	Special spec(&toker);

	toker.attach(&in);
	spec.setSpecialCharspairs("\"\"", false);
	while (spec.get())
	{
		std::cout << "\n  -- statements --";
		spec.show();
	}

	if (spec.length() > 0)
	{
		std::cout << "\n  -- statements --";
		spec.show();
		std::cout << "\n\n";
	}
	return 0;

}
#endif

