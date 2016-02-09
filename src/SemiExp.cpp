/*
 * SemiExp.cpp
 *
 *  Created on: Feb 2, 2016
 *      Author: malz
 */

/////////////////////////////////////////////////////////////////////
// Tokenizer.cpp - read words from a std::stream                   //
// ver 3.2                                                         //
// Language:    Eclipse Mars                            //
// Application: Parser component, CSE687 - Object Oriented Design  //
// Author:       Ravichandra Malapati, Syracuse University, CST 4-174        //
//              rmalapat@syr.edu                              //
/////////////////////////////////////////////////////////////////////
#define TEST_SEMI
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <exception>
#include "SemiExp.h"
#include "Tokenizer.h"
#include "ITokCollection.h"

using namespace Scanner;

SemiExp::SemiExp(Toker* pToker) :
		_pToker(pToker)
{

}
struct ITokColl: ITokCollection
{
public:
	bool get(bool clear = true)
	{
		return 0;

	}
	size_t length()
	{
		return 0;
	}
	std::string& operator[](int n)
	{
		string str = "xyz";
		return str;
	}
	size_t find(const std::string& tok)
	{

	}

	void push_back(const std::string& tok)
	{

	}
	bool merge(const std::string& firstTok, const std::string& secondTok)
	{

	}
	bool remove(const std::string& tok)
	{

	}
	bool remove(size_t i)
	{

	}
	void toLower()
	{

	}
	void trimFront()
	{

	}
	void clear()
	{

	}
	std::string show(bool showNewLines = false)
	{
		return "xyz";
	}

};

bool SemiExp::get()
{
	if (_pToker == nullptr)
		throw(std::logic_error("no Toker reference"));
	_tokens.clear();
	while (true)
	{
		std::string* tokens;
		tokens = _pToker->getToks();
		//std::string token = _pToker->getTok();
		if (tokens[0] == "#")
		{
			tokens = _pToker->getToks();
		}
		if (tokens[0] == "")
			break;
		_tokens.push_back(tokens[0]);

		if (tokens[0] == "{")
			return true;
	}
	return false;
}

Token SemiExp::operator[](size_t n)
{
	if (n < 0 || n >= _tokens.size())
		throw(std::invalid_argument("index out of range"));
	return _tokens[n];
}

size_t SemiExp::length()
{
	return _tokens.size();
}

void SemiExp::show()
{
	std::cout << "\n  ";
	for (auto token : _tokens)
		if (token != "\n")
			std::cout << token << " ";
	std::cout << "\n";
}

#ifdef TEST_SEMI
int main()
{
	Toker toker;
	std::string fileSpec =
			"/home/malz/workspace/new_workspace/testtok.cpp";
	std::fstream in(fileSpec);
	if (!in.good())
	{
		std::cout << "\n  can't open file " << fileSpec << "\n\n";
		return 1;
	}
	toker.attach(&in);

	SemiExp semi(&toker);
	while (semi.get())
	{
		std::cout << "\n  -- semiExpression --";
		semi.show();
		cout<<"\nLine number is:"<<semi.getLineSemi();

	}
	/*
	 May have collected tokens, but reached end of stream
	 before finding SemiExp terminator.
	 */
	if (semi.length() > 0)
	{
		std::cout << "\n  -- semiExpression --";
		semi.show();
		std::cout << "\n\n";
	}
	return 0;
}
#endif



int SemiExp::getLineSemi()
{
	 if (_pToker == nullptr)
	    return 0;
	return _pToker->getLineToker();
}