#include "NumberExpression.h"
#include "string"
#include "NanType.h"
#include "Token.h"

using namespace std;

NumberExpression::NumberExpression(string value) {
	this->value = value;
}

BaseValue* NumberExpression::eval() {
	return new BaseValue(this->value, NUMBER_TYPE);
}