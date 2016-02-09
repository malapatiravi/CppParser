/////////////////////////////////////////////////////////////////////
// Tokenizer.cpp - read words from a std::stream                   //
// ver 3.2                                                         //
// Language:    Eclipse Mars                            //
// Application: Parser component, CSE687 - Object Oriented Design  //
// Author:       Ravichandra Malapati, Syracuse University, CST 4-174        //
//              rmalapat@syr.edu                              //
/////////////////////////////////////////////////////////////////////

#include "Tokenizer.h"
#include <iostream>
#include <cctype>
#include <string>
#include <stdexcept>
#include <vector>
#include <array>
#include <fstream>
//#define TEST_TOKENIZER
//#define TEST_LOG
//#define TEST_PROJECT1
namespace Scanner
{
class VecHolder
{
public:
	void displayVector()
	{
		vector<string> tempVec = getSpecialPair();
		for (int i = 0; i < tempVec.size(); i++)
		{
			if (i == 0)
				cout << "---------------------------------size of vector is: "
						<< tempVec.size();
			cout << "\n Test Vector is: " << tempVec[i];
		}
	}
	vector<string> getSpecialPair()
	{
		return specCharPair;
	}
	void setSpecialPair(string specialChars)
	{
		specCharPair.push_back(specialChars);

	}
	vector<string> getSpecialChar()
	{
		return specCharSing;
	}
	void setSpecialChar(string specialChars)
	{
		specCharSing.push_back(specialChars);
	}
private:

	vector<string> specCharPair;
	vector<string> specCharSing;
};

class ConsumeState
{
public:
	ConsumeState();
	ConsumeState(const ConsumeState&) = delete;
	ConsumeState& operator=(const ConsumeState&) = delete;
	virtual ~ConsumeState();
	void attach(std::istream* pIn)
	{
		_pIn = pIn;
	}
	virtual void eatChars() = 0;
	void consumeChars()
	{
		_pState->eatChars();
		_pState = nextState();
	}
	bool canRead()
	{
		return _pIn->good();
	}
	std::string getTok()
	{
		return token;
	}
	std::string* getToks()
	{
		return tokens;
	}
	bool hasTok()
	{
		return token.size() > 0;
	}
	ConsumeState* nextState();
	void displayVector()
	{
		_pVecHolder->displayVector();
	}

	vector<string> getSpecialPair()
	{
		return _pVecHolder->getSpecialPair();
	}
	void setSpecialPair(string specialChars)
	{
		_pVecHolder->setSpecialPair(specialChars);
	}
	vector<string> getSpecialChar()
	{
		return _pVecHolder->getSpecialChar();
	}
	void setSpecialChar(string specialChars)
	{
		_pVecHolder->setSpecialChar(specialChars);

	}
	int getLine()
	{
		return _line_count;
	}

private:

protected:
	static int _line_count;
	static std::string tokens[2];
	static std::string token;
	static std::string token_contents;
	static std::istream* _pIn;
	static int prevChar;
	static int currChar;
	static VecHolder* _pVecHolder;
	static ConsumeState* _pState;
	static ConsumeState* _pEatCppComment;
	static ConsumeState* _pEatCComment;
	static ConsumeState* _pEatWhitespace;
	static ConsumeState* _pEatPunctuator;
	static ConsumeState* _pEatAlphanum;
	static ConsumeState* _pEatNewline;
	static ConsumeState* _pEatPunctuatorExpansion;
};

}

//#ifndef TEST_TOKENIZER
using namespace std;
using namespace Scanner;
int ConsumeState::_line_count = 0;
std::string ConsumeState::tokens[2];
std::string ConsumeState::token;
std::string ConsumeState::token_contents;
std::istream* ConsumeState::_pIn;
int ConsumeState::prevChar;
int ConsumeState::currChar;
VecHolder* ConsumeState::_pVecHolder = nullptr;
ConsumeState* ConsumeState::_pState = nullptr;
ConsumeState* ConsumeState::_pEatCppComment = nullptr;
ConsumeState* ConsumeState::_pEatCComment = nullptr;
ConsumeState* ConsumeState::_pEatWhitespace = nullptr;
ConsumeState* ConsumeState::_pEatPunctuator = nullptr;
ConsumeState* ConsumeState::_pEatAlphanum = nullptr;
ConsumeState* ConsumeState::_pEatNewline;
ConsumeState* ConsumeState::_pEatPunctuatorExpansion = nullptr;

void testLog(const std::string& msg);

ConsumeState* ConsumeState::nextState()
{
	if (!(_pIn->good()))
		return nullptr;

	int chNext = _pIn->peek();
	if (std::isspace(currChar) && currChar != '\n')
	{
		testLog("state: eatWhitespace");
		return _pEatWhitespace;
	}
	if (currChar == '/' && chNext == '/')
	{
		testLog("state: eatCppComment");
		return _pEatCppComment;
	}
	if (currChar == '/' && chNext == '*')
	{
		testLog("state: eatCComment");
		return _pEatCComment;
	}
	if (currChar == '\n')
	{
		testLog("state: eatNewLine");
		return _pEatNewline;
	}
	if (std::isalnum(currChar) || currChar == '_')
	{
		testLog("state: eatAlphanum");
		return _pEatAlphanum;
	}
	if (ispunct(currChar))
	{
#ifdef TEST_TOKENIZER
		testLog("state: eatPunctuator");
		return _pEatPunctuator;
#endif
#ifndef TEST_TOKENIZER
		testLog("state: eatPunctuatorExpansion");
		return _pEatPunctuatorExpansion;
#endif
	}
	if (!_pIn->good())
		return _pEatWhitespace;
	throw(std::logic_error("invalid type"));
}

class EatWhitespace: public ConsumeState
{
public:
	virtual void eatChars()
	{
		token.clear();
		token_contents.clear();
		tokens[0].clear();
		tokens[1].clear();
		//tp.token_state.clear();
		token_contents = "white_spaces";
		tokens[1] = token_contents;
		do
		{
			if (!_pIn->good())
				return;
			currChar = _pIn->get();

		} while (std::isspace(currChar) && currChar != '\n');
		tokens[0] = token;
	}
};

class EatCppComment: public ConsumeState
{
public:
	virtual void eatChars()
	{
		token.clear();
		token_contents.clear();
		tokens[0].clear();
		tokens[1].clear();
		token_contents = "CppComment-Req4.5";
		tokens[1] = token_contents;
		do
		{
			token += currChar;

			if (!_pIn->good())  // end of stream
				return;
			currChar = _pIn->get();
		} while (currChar != '\n');

		tokens[0] = token;
	}
};

class EatCComment: public ConsumeState
{
public:
	virtual void eatChars()
	{
		token.clear();
		token_contents.clear();
		tokens[0].clear();
		tokens[1].clear();
		token_contents = "C Comment-Req4.4";
		tokens[1] = token_contents;
		do
		{
			token += currChar;
			if (!_pIn->good())  // end of stream
				return;
			currChar = _pIn->get();
		} while (currChar != '*' || _pIn->peek() != '/');
		token += "*/";
		tokens[0] = token;
		_pIn->get();
		currChar = _pIn->get();
	}
};

class EatPunctuator: public ConsumeState
{
public:
	virtual void eatChars()
	{
		token.clear();
		token_contents.clear();
		tokens[0].clear();
		tokens[1].clear();

		token_contents = "Punctuator-Req4";
		tokens[1] = token_contents;
		do
		{
			token += currChar;
			if (!_pIn->good())  // end of stream
				return;
			currChar = _pIn->get();
		} while (ispunct(currChar));
		tokens[0] = token;
	}
};
class PunctuatorExpansion: public EatPunctuator
{
public:

	virtual void eatChars()
	{
		token.clear();
		token_contents.clear();
		tokens[0].clear();
		tokens[1].clear();
		string tempSpecCharac, tempSpecCharacSing;
		tempSpecCharac = string() + char(currChar) + char(_pIn->peek());
		tempSpecCharacSing = string() + char(currChar);
		token_contents = "Punctuator-Req-4.2";
		tokens[1] = token_contents;
		if (currChar == '\'')
		{
			do
			{

				if (!_pIn->good())  // end of stream
					return;
				prevChar = currChar;
				currChar = _pIn->get();
				if (currChar != '\'')
					token += currChar;
				if (currChar == '\'' && prevChar == '\\')
				{
					//token += currChar;
					prevChar = currChar;
					currChar = _pIn->get();
				}
			} while (currChar != '\'');

			currChar = _pIn->peek();
			tokens[0] = token;
			tokens[1] = "character string-Req4.6";
			return;
		}
		if (currChar == '"')
		{
			do
			{

				if (!_pIn->good())  // end of stream
					return;
				prevChar = currChar;
				currChar = _pIn->get();
				if (currChar != '"')
					token += currChar;
				if (currChar == '"' && prevChar == '\\')
				{
					//token += currChar;
					prevChar = currChar;
					currChar = _pIn->get();
				}

			} while (currChar != '"');

			currChar = _pIn->peek();
			tokens[0] = token;
			tokens[1] = "character string-Req4.6";
			return;
		}

		for (int k = 0; k < _pVecHolder->getSpecialPair().size(); k++) //while (i != specCharPair.end())
		{
			if (_pVecHolder->getSpecialPair()[k] == tempSpecCharac)
			{
				token += currChar;
				currChar = _pIn->get();
				token += currChar;
				tokens[0] = token;
				currChar = _pIn->get();
				tokens[1] = "Special two characters-Req4.3";
				return;
			}
		}
		for (int k = 0; k < _pVecHolder->getSpecialChar().size(); k++) //while (i != specCharPair.end())
		{
			if (_pVecHolder->getSpecialChar()[k] == tempSpecCharacSing)
			{
				token += currChar;
				tokens[0] = token;
				currChar = _pIn->get();
				tokens[1] = "Special Single character-Req4.3";
				return;
			}
		}
		do
		{
			token += currChar;
			if (!_pIn->good())
				return;
			currChar = _pIn->get();
		} while (ispunct(currChar));
		tokens[0] = token;
	}
};
class EatAlphanum: public ConsumeState
{
public:
	virtual void eatChars()
	{
		token.clear();
		token_contents.clear();
		tokens[0].clear();
		tokens[1].clear();

		token_contents = "Alphanum-Req4";
		tokens[1] = token_contents;

		do
		{
			token += currChar;
			if (!_pIn->good())  // end of stream
				return;
			currChar = _pIn->get();
		} while (isalnum(currChar) || (currChar == '_'));

		tokens[0] = token;
	}
};

class EatNewline: public ConsumeState
{
public:
	virtual void eatChars()
	{
		token.clear();
		token_contents.clear();
		tokens[0].clear();
		tokens[1].clear();
		token_contents = "NewLine";
		tokens[1] = token_contents;
		token += currChar;
		tokens[0] = token;
		_line_count++;
		//tp.token_s = token;
		if (!_pIn->good())  // end of stream
			return;
		currChar = _pIn->get();
	}
};

ConsumeState::ConsumeState()
{
	static bool first = true;
	if (first)
	{
		//specChar.clear();
		//specCharPair.clear();
		first = false;
		_pEatAlphanum = new EatAlphanum();
		_pEatCComment = new EatCComment();
		_pEatCppComment = new EatCppComment();
		_pEatPunctuator = new EatPunctuator();
		_pEatWhitespace = new EatWhitespace();
		_pEatNewline = new EatNewline();
		_pState = _pEatWhitespace;
		_pEatPunctuatorExpansion = new PunctuatorExpansion();
		VecHolder* vec = new VecHolder();
		_pVecHolder = vec;
		_line_count = 1;

	}
}

ConsumeState::~ConsumeState()
{
	static bool first = true;
	if (first)
	{
		first = false;
		delete _pEatAlphanum;
		delete _pEatCComment;
		delete _pEatCppComment;
		delete _pEatPunctuator;
		delete _pEatWhitespace;
		delete _pEatNewline;
		delete _pVecHolder;
	}
}

Toker::Toker() :
		pConsumer(new EatWhitespace())
{
}

Toker::~Toker()
{
	delete pConsumer;
}

bool Toker::attach(std::istream* pIn)
{
	if (pIn != nullptr && pIn->good())
	{
		pConsumer->attach(pIn);
		return true;
	}
	return false;

}

std::string Toker::getTok()
{

	while (true)
	{
		if (!pConsumer->canRead())
			return "";
		pConsumer->consumeChars();
		if (pConsumer->hasTok())
			break;
	}
	return pConsumer->getTok();
}
std::string* Toker::getToks()
{
	while (true)
	{
		std::string str[] = "";
		pConsumer->consumeChars();
		if (pConsumer->hasTok())
			break;
		if (!pConsumer->canRead())
			return str;
		//std::cout<<" \n the token is" << pConsumer->getTok();
	}
	return pConsumer->getToks();
}
std::string Toker::getTok_Comment()
{
	while (true)
	{
		pConsumer->consumeChars();
		if (pConsumer->hasTok())
			break;
		if (!pConsumer->canRead())
			return "";
		//std::cout<<" \n the token is" << pConsumer->getTok();
	}
	return pConsumer->getTok();
}

bool Toker::canRead()
{
	return pConsumer->canRead();
}

int Toker::getLineToker()
{
	return pConsumer->getLine();
}
void testLog(const std::string& msg)
{
#ifdef TEST_LOG
	std::cout << "\n  " << msg;
#endif
}


void Toker::setSpecialSingleChars(string specialChars)
{
	pConsumer->setSpecialChar(specialChars);
}
void Toker::setSpecialCharPairs(string specialChars)
{
	pConsumer->setSpecialPair(specialChars);
}
//#endif
//----< test stub >--------------------------------------------------
#ifdef TEST_PROJECT1
int main()
{
	cout
	<< "----------------Requirement1 and Requirment2----------------------------\n";
	cout << "Using Visual Studio and Standard C++ I/O Library \n";
	cout << "----------------Requirement3----------------------------\n";
	cout
	<< "Providing Tokenizing, SemiExpression Package and Scanner interface \n";

	std::string fileSpec =
	"/home/malz/workspace/new_workspace/testtok.cpp";

	std::ifstream in(fileSpec);
	if (!in.good())
	{
		std::cout << "\n  can't open " << fileSpec << "\n\n";
		return 1;
	}
	Toker toker;
	toker.attach(&in);
	std::ofstream myfile;
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
	//toker.setSpecialSingleChars("#");

	while (in.good())
	{

		std::string* toks = toker.getToks();
		std::cout << "\n---------------" << toks[1];
		std::cout << "\n" << toks[0];
		std::cout<<"\n the line number is :"<<toker.getLineToker();
		//std::cout << "\n-----------------------------------------" << toks[1];
	}
	std::cout << "\n\n";
	return 0;
}

#endif
#ifdef TEST_TOKENIZER

int main()
{
//getTok_comment();
	std::cout << "Done";
//std::string fileSpec = "/home/malz/workspace/new_workspace/Tokenizer/src/Tokenizer.cpp";
	std::string fileSpec =
	"/home/malz/workspace/new_workspace/Tokenizer/src/Tokenizer.cpp";
//std::string fileSpec = "../Tokenizer/Test.txt";

	std::ifstream in(fileSpec);
//std::cout << in.rdbuf();
	if (!in.good())
	{
		std::cout << "\n  can't open " << fileSpec << "\n\n";
		return 1;
	}
	Toker toker;
	toker.attach(&in);
	std::ofstream myfile;

	while (in.good())
	{

		std::string* toks = toker.getToks();
		std::cout << "\n-----------------------------------------" << toks[1];
		std::cout << "\n" << toks[0];
		std::cout << "\n-----------------------------------------" << toks[1];
	}
	std::cout << "\n\n";
	return 0;
}
#endif
