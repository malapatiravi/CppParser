/*
 * Special.h
 *
 *  Created on: Jan 31, 2016
 *      Author: malz
 */

#ifndef SRC_SPECIAL_H_
#define SRC_SPECIAL_H_

#include "Tokenizer.h"
#include <vector>
using Token = std::string;
namespace Scanner
{

class Special: public Toker
{

public:
	std::string start;
	std::string end;
	Special(Toker* pToker);
	bool setSpecialCharspairs(std::string pair, bool two_or_not);

	bool get();
	Token operator[](size_t n);
	size_t length();
	void show();
private:
	std::vector<Token> _tokens;
	Toker* _pToker;
};
}
#endif /* SRC_SPECIAL_H_ */
