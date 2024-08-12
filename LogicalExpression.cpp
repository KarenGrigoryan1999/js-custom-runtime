#include "LogicalExpression.h"
#include "Token.h"
#include "NumberType.h"
#include "StringType.h"
#include "BoolType.h"
#include "TokenType.h"

using namespace std;

LogicalExpression::LogicalExpression(token_t op, Expression* exp1, Expression* exp2) {
	this->op = op;
	this->exp1 = exp1;
	this->exp2 = exp2;
}

BaseValue* LogicalExpression::eval() {
	BaseValue* operand1 = exp1->eval();
	BaseValue* operand2 = exp2->eval();

	BoolType* TrueVariant = new BoolType(true);
	BoolType* FalseVariant = new BoolType(false);

	if (this->op == LOGICAL_AND_EXPRESSION) {
		if (operand1->get_as_boolean() == false) {
			return operand1;
		}
		return operand2;
	}

	if (this->op == BITWISE_OR_EXPRESSION) {
		if (operand1->get_as_boolean() == true) {
			return operand1;
		}
		return operand2;
	}

	if (operand1->get_type() == NAN_TYPE || operand2->get_type() == NAN_TYPE) return FalseVariant;
	if (this->op == NOT_EQ_CHECKING) {
		return operand1->get_as_number() != operand2->get_as_number() ? TrueVariant : FalseVariant;
	}
	if (this->op == NOT_EQ_STRICT_CHECKING) {
		if (operand1->get_type() != operand2->get_type()) return TrueVariant;
		if (operand1->get_as_string() == operand2->get_as_string()) return FalseVariant;
		else return TrueVariant;
	}
	if (this->op == EQ_CHECKING) {
		return operand1->get_as_number() == operand2->get_as_number() ? TrueVariant : FalseVariant;
	}
	if (this->op == EQ_STRICT_CHECKING) {
		if (operand1->get_type() != operand2->get_type()) return TrueVariant;
		if (operand1->get_as_string() == operand2->get_as_string()) return TrueVariant;
		else
		return FalseVariant;
	}

	if (operand1->get_type() == NUMBER_TYPE && operand2->get_type() == NUMBER_TYPE) {
		if (this->op == GT) {
			return operand1->get_as_number() > operand2->get_as_number() ? TrueVariant : FalseVariant;
		}
		if (this->op == GTE) {
			return operand1->get_as_number() >= operand2->get_as_number() ? TrueVariant : FalseVariant;
		}
		if (this->op == LT) {
			return operand1->get_as_number() < operand2->get_as_number() ? TrueVariant : FalseVariant;
		}
		if (this->op == LTE) {
			return operand1->get_as_number() <= operand2->get_as_number() ? TrueVariant : FalseVariant;
		}
	}
	else if (operand1->get_type() == STRING_TYPE && operand2->get_type() == STRING_TYPE) {
		if (this->op == '>') {
			return TrueVariant;
		}
		if (this->op == '<') {
			return TrueVariant;
		}
		if (this->op == '=') {
			return operand1->get_as_string() == operand2->get_as_string() ? TrueVariant : FalseVariant;
		}
	}
	else {
		return FalseVariant;
	}
}

struct Environment {
	vector<BaseValue*>* record;
	Environment* outer;
};