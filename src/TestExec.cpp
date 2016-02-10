/*
 * TestExec.cpp
 *
 *  Created on: Feb 9, 2016
 *      Author: malz
 */

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
std::ifstream in;
std::ifstream in1;
Toker toker;
Toker toker1;
std::string fileSpec;
void tokenizerSetUp(Toker& toker) {
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
}

int main() {
	std::string fileSpec = "/home/malz/workspace/new_workspace/testtok.cpp";
	cout << "\n Loading file";

	cout
			<< "----------------Requirement1 and Requirment2----------------------------\n";
	cout << "Using Visual Studio and Standard C++ I/O Library \n";
	cout << "----------------Requirement3----------------------------\n";
	cout
			<< "Providing Tokenizing, SemiExpression Package and Scanner interface \n";

	std::ifstream in(fileSpec);
	cout << "input is: " << in;
	if (!in.good()) {
		std::cout << "\n  can't open " << fileSpec << "\n\n";
		//return 1;
	}
	Toker toker;

	toker.attach(&in);
	std::ofstream myfile;
	tokenizerSetUp(toker);
	while (in.good()) {
		std::string* toks = toker.getToks();
		std::cout << "\n---------------" << toks[1];
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

	while (semi.get()) {
		std::cout << "\n  -- semiExpression --";
		semi.show();
		//cout << "\nLine number is:" << semi.getLineSemi();

	}
	/*
	 May have collected tokens, but reached end of stream
	 before finding SemiExp terminator.
	 */
	if (semi.length() > 0) {
		std::cout << "\n  -- semiExpression --";
		semi.show();
		std::cout << "\n\n";
	}
	return 0;
}

