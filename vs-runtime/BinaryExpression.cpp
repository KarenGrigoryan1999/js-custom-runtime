#include "BinaryExpression.h"
#include "Token.h"
#include "NumberType.h"
#include "StringType.h"
#include "TokenType.h"

using namespace std;

BinaryExpression::BinaryExpression(token_t op, Expression* exp1, Expression* exp2) {
	this->op = op;
	this->exp1 = exp1;
	this->exp2 = exp2;
}

BaseValue* BinaryExpression::eval() {
	BaseValue* operand1 = exp1->eval();
	BaseValue* operand2 = exp2->eval();

	if (operand1->get_type() == NUMBER_TYPE && operand2->get_type() == NUMBER_TYPE) {
		if (this->op == PLUS) {
			return new NumberType(operand1->get_as_number() + operand2->get_as_number());
		}
		if (this->op == MINUS) {
			return new NumberType(operand1->get_as_number() - operand2->get_as_number());
		}
		if (this->op == STAR) {
			return new NumberType(operand1->get_as_number() * operand2->get_as_number());
		}
		if (this->op == DIV) {
			return new NumberType(operand1->get_as_number() / operand2->get_as_number());
		}
	}

	if (operand1->get_type() == STRING_TYPE || operand2->get_type() == STRING_TYPE) {
		if (this->op == PLUS) {
			return new StringType(operand1->get_as_string() + operand2->get_as_string());
		}
		if (this->op == MINUS) {
			return new StringType("NaN");
		}
		if (this->op == STAR) {
			return new StringType("NaN");
		}
		if (this->op == DIV) {
			return new StringType("NaN");
		}
	}
}