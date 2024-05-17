#include "BinaryExpression.h"
#include "Token.h"
#include "NumberType.h"
#include "StringType.h"
#include "TokenType.h"
#include "NanType.h"
#include "ObjectExpression.h"

using namespace std;

BinaryExpression::BinaryExpression(token_t op, Expression* exp1, Expression* exp2) {
	this->op = op;
	this->exp1 = exp1;
	this->exp2 = exp2;
}

BaseValue* BinaryExpression::eval() {
	BaseValue* operand1 = exp1->eval();
	BaseValue* operand2 = exp2->eval();

	if (
		(operand1->get_type() == NUMBER_TYPE || operand1->get_type() == NULL_TYPE)
		&& (operand2->get_type() == NUMBER_TYPE || operand2->get_type() == NULL_TYPE)
	) {
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
			double op1 = operand1->get_as_number();
			double op2 = operand2->get_as_number();

			if (op1 == op2 && op1 == 0) {
				return new NanType();
			}

			if (op2 == 0) {
				return new StringType("Infinity");
			}
			return new NumberType(operand1->get_as_number() / operand2->get_as_number());
		}
	}

	if (
		(operand1->get_type() == NUMBER_TYPE || operand2->get_type() == NUMBER_TYPE)
		&& (operand1->get_type() == UNDEFINED_TYPE || operand2->get_type() == UNDEFINED_TYPE)
		) {
		return new NanType();
	}

	if (
		(operand1->get_type() == NAN_TYPE || operand2->get_type() == NAN_TYPE)
		&& (operand1->get_type() != STRING_TYPE && operand2->get_type() != STRING_TYPE)
	) {
		return new NanType();
	}

	if (operand1->get_type() == STRING_TYPE || operand2->get_type() == STRING_TYPE) {
		if (this->op == PLUS) {
			return new StringType(operand1->get_as_string() + operand2->get_as_string());
		}
		if (this->op == MINUS) {
			return new NanType();
		}
		if (this->op == STAR) {
			return new NanType();
		}
		if (this->op == DIV) {
			return new NanType();
		}
	}
}