/*
 * TestExec.cpp
 *
 *  Created on: Feb 9, 2016
 *      Author: malz
 */

/////////////////////////////////////////////////////////////////////
// TestExec.cpp - this package executes all the operations of Tokenizer, ITok collection and SemiExp                  //
// ver 1.1                                                        //
// Language:   Visual studio 2015                            //
// Application: Parser component, CSE687 - Object Oriented Design  //
// Author:       Ravichandra Malapati, Syracuse University, CST 4-174        //
//              rmalapat@syr.edu                              //
/////////////////////////////////////////////////////////////////////


#define TESTEXEC
#include "Tokenizer.h"
#include "SemiExp.h"
#include "Tokenizer.h"
#include <iostream>
#include <cctype>
#include <string>
#include <stdexcept>
#include <vector>
#include <array>
#include <fstream>
using namespace std;
using namespace Scanner;
class TestExec {
public:
	std::ifstream in;
	std::ifstream in1;
	std::string fileSpec = "/home/malz/workspace/new_workspace/testtok.cpp";
	void tokenizerSetUp(Toker& toker) {
		toker.setSpecialCharPairs("<<");
		toker.setSpecialCharPairs("<=");
		toker.setSpecialCharPairs(">=");
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
		toker.setTokenTypesFlag(" ");
	}
	void showInit() {
		cout << "\n Loading file";
	}
	int main1() {

		showInit();
		std::ifstream in(fileSpec);
		if (!in.good()) {
			std::cout << "\n  can't open " << fileSpec << "\n\n";
		}
		Toker toker;

		toker.attach(&in);
		std::ofstream myfile;
		tokenizerSetUp(toker);
		while (in.good()) {
			std::string* toks = toker.getToks();
			std::cout << "\n--" << toks[1];
			if (toks[1] != "NewLine") {
				std::cout << "\n" << toks[0];
			}
		}
		std::cout << "\n\n";

		///////////
		cout << "\n-------------------------Semi Exp------------------------";
		Toker toker1;
		std::string fileSpec1 = "/home/malz/workspace/new_workspace/testtok.cpp";
		std::fstream in1(fileSpec1);
		if (!in1.good()) {
			std::cout << "\n  can't open file " << fileSpec1 << "\n\n";
			return 1;
		}
		toker1.attach(&in1);
		SemiExp semi(&toker1);
		tokenizerSetUp(toker1);
		while (semi.get1(true)) {
			std::cout << "\n  -- semiExpression --";
			cout<<semi.show1(true);
		}
		if (semi.length() > 0) {
			std::cout << "\n  -- semiExpression --";
			semi.show();
			std::cout << "\n\n";
		}
		return 0;
	}

};

#ifdef TESTEXEC
int main() {
	TestExec te;
	te.main1();
}
#endif
