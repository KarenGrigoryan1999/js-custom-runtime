#include "UnaryExpression.h"
#include "Token.h"
#include "NumberType.h"
#include "BoolType.h"

using namespace std;

UnaryExpression::UnaryExpression(token_t op, Expression* exp1) {
	this->op = op;
	this->exp1 = exp1;
}

BaseValue* UnaryExpression::eval() {
	if (this->op == PLUS) {
		return exp1->eval();
	}
	if (this->op == MINUS) {
		return new NumberType(exp1->eval()->get_as_number()*(-1));
	}
	if (this->op == INVERSE) {
		return new BoolType(!exp1->eval()->get_as_boolean());
	}
}