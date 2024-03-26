#pragma once
#include <iostream>
#include "Token.h"
#include "TokenType.h"

using namespace std;

Token::Token(token_t type, string value) {
	this->type = type;
	this->value = value;
}