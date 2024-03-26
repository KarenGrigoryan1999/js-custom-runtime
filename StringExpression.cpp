#include "StringExpression.h"
#include "string"
#include "Token.h"

using namespace std;

StringExpression::StringExpression(string value) {
	this->value = value;
}

BaseValue* StringExpression::eval() {
	return new BaseValue(this->value, STRING_TYPE);
}