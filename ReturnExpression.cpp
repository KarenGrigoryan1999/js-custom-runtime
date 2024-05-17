#include "ReturnExpression.h"
#include "Token.h"
#include "NumberType.h"
#include "BoolType.h"
#include <iostream>

using namespace std;

ReturnExpression::ReturnExpression(Expression* exp) {
	this->exp = exp;
}

ReturnExpression::ReturnExpression() {}

BaseValue* ReturnExpression::get_result() {
	return this->result;
}

BaseValue* ReturnExpression::eval() {
	this->result = this->exp->eval();
	throw this;
}