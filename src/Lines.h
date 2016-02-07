/*
 * Lines.h
 *
 *  Created on: Jan 31, 2016
 *      Author: malz
 */

#ifndef SRC_LINES_H_
#define SRC_LINES_H_

#include <vector>
#include "Tokenizer.h"

namespace Scanner
{
using Token = std::string;

class Lines
{
public:
	Lines(Toker* pToker);
	bool get();
	Token operator[](size_t n);
	size_t length();
	void show();
private:
	std::vector<Token> _tokens;
	Toker* _pToker;
};
}

#endif /* SRC_LINES_H_ */
