#ifndef TOKEN_H
#define TOKEN_H
#include "TokenType.h"

using namespace std;

class Token
{
public:
	Token(token_t type, string value);
	string value;
	token_t type;
};

#endif