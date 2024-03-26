#include "ReturnExpression.h"
#include "Token.h"
#include "NumberType.h"
#include "BoolType.h"

using namespace std;

ReturnExpression::ReturnExpression(Expression* exp) {
	this->exp = exp;
}

BaseValue* ReturnExpression::get_result() {
	return this->result;
}

BaseValue* ReturnExpression::eval() {
	this->result = this->exp->eval();
	throw this;
}