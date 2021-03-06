/*
 * SemiExp.cpp
 *
 *  Created on: Feb 2, 2016
 *      Author: malz
 */

/////////////////////////////////////////////////////////////////////
// SemiExp.cpp.cpp - read words from a std::stream                   //
// ver 3.2                                                         //
// Language:    Eclipse Mars                            //
// Application: Parser component, CSE687 - Object Oriented Design  //
// Author:       Ravichandra Malapati, Syracuse University, CST 4-174        //
//              rmalapat@syr.edu                              //
/////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
// SemiExpression.cpp - collect tokens for analysis                  //
// ver 3.1                                                           //
// Language:    C++, Visual Studio 2015                              //
// Application: Parser component, CSE687 - Object Oriented Design    //
// Author:      Jim Fawcett, Syracuse University, CST 4-187          //
//              jfawcett@twcny.rr.com                                //
///////////////////////////////////////////////////////////////////////

//#define TEST_SEMI
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
		_pToker(pToker) {

}

std::string& SemiExp::operator[](int n) {
	string str = "xyz";
	return str;
}
size_t SemiExp::find(const std::string& tok) {
	for (size_t i = 0; i < length(); ++i)
		if (_tokens[i] == tok)
			return i;
	return length();
}

void SemiExp::push_back(const std::string& tok) {
	_tokens.push_back(tok);
}
bool SemiExp::merge(const std::string& firstTok, const std::string& secondTok) {
/*this is not required as per the requirment*/
}
bool SemiExp::remove(const std::string& tok) {
int l=find(tok);
return true;
}
bool SemiExp::remove(size_t i) {
	if (i < 0 || i >= length())
		return false;
	std::vector<Token>::iterator iter = _tokens.begin() + i;
	_tokens.erase(iter);
	return true;
}
void SemiExp::toLower() {

}
void SemiExp::trimFront() {
	while (length() > 1) {
		if (_tokens[0] == "\n")
			remove(0);
		else
			break;
	}
}
void SemiExp::clear() {
	_tokens.clear();

}
bool SemiExp::forLoop(Token tok) {
	//_tokens.push_back(tok);
	//cout << "\n" << tok;
	Token* _tok = _pToker->getToks();

	while (_tok[0] != "{") {
		//cout<<"\n"<<_tok[0];
		_tokens.push_back(_tok[0]);
		_tok = _pToker->getToks();
	}
	if (_tok[0] == "{")
		_tokens.push_back(_tok[0]);
	if (find(";") == 0)
		return false;
	return true;
}

bool SemiExp::analyse(Token tok) {
	if (tok == "{" || tok == "}" || tok == ";")
		return true;
	if (tok == "\n") {
		//trimFront();
		if (_tokens[0] == "#")
			return true;
	}
	if (length() < 2)
		return false;

	if (tok == ":" && length() > 0 && _tokens[length() - 2] == "public")
		return true;
	if (tok == ":" && length() > 0 && _tokens[length() - 2] == "protected")
		return true;
	if (tok == ":" && length() > 0 && _tokens[length() - 2] == "private")
		return true;
	return false;
}
bool SemiExp::get1(bool clear1) {
	if (clear1)
		clear();
	if (_pToker == nullptr)
		throw(std::logic_error("no Toker reference"));
	while (true) {
		Token* token = _pToker->getToks();
		if (token[0] == "")
			break;
		push_back(token[0]);
		if (token[0] == "for") {
			if (forLoop(token[0]))
				return true;
		}
		if (token[1] == "CppComment-Req4.5" || token[1] == "C Comment-Req4.4")
			return true;
		if (token[0] == "{" || token[0] == "}" || token[0] == ";")
			return true;
		if (token[0] == "\n") {
			if (_tokens[0] == "#")
				return true;
			if (_tokens[0] == "\n")
			 remove(0);
			 else
			 break;
		}
		if (token[0] == ":" && length() > 0
				&& _tokens[length() - 2] == "public")
			return true;
		if (token[0] == ":" && length() > 0
				&& _tokens[length() - 2] == "protected")
			return true;
		if (token[0] == ":" && length() > 0
				&& _tokens[length() - 2] == "private")
			return true;
	}

	return true;
}
bool SemiExp::get() {
	int temp = 0;
	isFor = false;
	if (_pToker == nullptr)
		throw(std::logic_error("no Toker reference"));
	_tokens.clear();
	while (true) {
		Token* _tok;
		_tok = _pToker->getToks(); //_tokens.push_back(_tok[0]);
		if (_tok[1] != "NewLine")
			_tokens.push_back(_tok[0]);
		else
			return true;
		if (_tok[0] == "")
			break;
		if (_tok[1] == "CppComment-Req4.5" || _tok[1] == "C Comment-Req4.4")
			return true;
		if (_tok[0] == "for") {
			isFor = true;
			while (_tok[0] != "{") {
				if (_tok[1] != "NewLine")
					_tokens.push_back(_tok[0]);
				else
					return true;
				_tok = _pToker->getToks(); //_tokens.push_back(_tok[0]);

			}
			_tokens.push_back(_tok[0]);
		}
		if (_tok[0] == "{" || _tok[0] == "}" || _tok[0] == ";")
			return true;
		if (_tok[0] == "\n") {
			if (_tokens[0] == "#")
				return true;
			if (_tokens[0] == "\n")
				remove(0);
			else
				break;
		}
		if (_tok[0] == ":" && length() > 0 && _tokens[length() - 2] == "public")
			return true;
		if (_tok[0] == ":" && length() > 0
				&& _tokens[length() - 2] == "protected")
			return true;
		if (_tok[0] == ":" && length() > 0
				&& _tokens[length() - 2] == "private")
			if (_tok[0] == "")
				break;
	}
	return false;
}

Token SemiExp::operator[](size_t n) {
	if (n < 0 || n >= _tokens.size())
		throw(std::invalid_argument("index out of range"));
	return _tokens[n];
}

size_t SemiExp::length() {
	return _tokens.size();
}

void SemiExp::show() {
	std::cout << "\n  ";
	for (auto token : _tokens)
		//if (token != "\n")
		std::cout << token << " ";

}
Token SemiExp::show1(bool showNewLines) {
	/*Token str="\n";

	 for(int i=0;i<_tokens.size();i++)
	 {str+=_tokens[i];
	// cout<<str;

	 }

	 return str;*/
	Token dispSemiexp = "\n  ";
	for (int i=0;i<_tokens.size();i++)
		if (_tokens[i] != "\n" || showNewLines == true)
			dispSemiexp += _tokens[i] + " ";
	dispSemiexp += "\n";
	return dispSemiexp;
}

/*---------------Test Stub--------------------*/
#ifdef TEST_SEMI
int main() {
	Toker toker;
	std::string fileSpec = "/home/malz/workspace/new_workspace/testtok.cpp";
	std::fstream in(fileSpec);
	if (!in.good()) {
		std::cout << "\n  can't open file " << fileSpec << "\n\n";
		return 1;
	}
	toker.attach(&in);

	SemiExp semi(&toker);
	toker.setSpecialCharPairs("<<");
	toker.setSpecialCharPairs(">>");
	toker.setSpecialCharPairs("::");
	toker.setSpecialCharPairs("++");
	toker.setSpecialCharPairs("--");
	toker.setSpecialCharPairs("==");
	toker.setSpecialCharPairs("+=");
	toker.setSpecialCharPairs("-=");
	toker.setSpecialCharPairs("*=");
	toker.setSpecialCharPairs("/=");
	toker.setSpecialCharPairs("&&");

	toker.setSpecialSingleChars(">");
	toker.setSpecialSingleChars("<");
	toker.setSpecialSingleChars("[");
	toker.setSpecialSingleChars("]");
	toker.setSpecialSingleChars("(");
	toker.setSpecialSingleChars(")");
	toker.setSpecialSingleChars("{");
	toker.setSpecialSingleChars("}");
	toker.setSpecialSingleChars(":");
	toker.setSpecialSingleChars(";");
	toker.setSpecialSingleChars("=");
	toker.setSpecialSingleChars("+");
	toker.setSpecialSingleChars("-");
	toker.setSpecialSingleChars("*");
	toker.setSpecialSingleChars("\n");

	toker.setTokenTypesFlag("white_spaces");
	toker.setTokenTypesFlag("CppComment-Req4.5");
	toker.setTokenTypesFlag("C Comment-Req4.4");
	toker.setTokenTypesFlag("Punctuator-Req4");
	toker.setTokenTypesFlag("Punctuator-Req-4.2");
	toker.setTokenTypesFlag("character_single_quote_string_Req4.6");
	toker.setTokenTypesFlag("character string-Req4.6");
	toker.setTokenTypesFlag("character_double_quote_string_Req4.6");
	toker.setTokenTypesFlag("Special_two_characters_Req4.3");
	toker.setTokenTypesFlag("Special_Single_character_Req4.3");
	toker.setTokenTypesFlag("Alphanum_Req4");
	toker.setTokenTypesFlag("NewLine");

	while (semi.get1(true)) {
		std::cout << "\n  -- semiExpression --";
		cout << semi.show1(true);
		//cout << "\nLine number is:" << semi.getLineSemi();

	}
	/*
	 May have collected tokens, but reached end of stream
	 before finding SemiExp terminator.
	 */
	if (semi.length() > 0) {
		std::cout << "\n  -- semiExpression --";
		//semi.show();
		std::cout << "\n\n";
	}
	return 0;
}
#endif

int SemiExp::getLineSemi() {
	if (_pToker == nullptr)
		return 0;
	return _pToker->getLineToker();
}
