#include "IncrementExpression.h"
#include "Token.h"
#include "NumberType.h"
#include "StringType.h"
#include "TokenType.h"
#include "NanType.h"
#include "DotExpression.h"
#include "EmptyExpression.h"

using namespace std;

IncrementExpression::IncrementExpression(char op, token_t op1, Expression* exp, string var_name, Environment* block) {
	this->op = op;
	this->op1 = op1;
	this->exp = exp;
	this->var_name = var_name;
	this->block = block;
}

BaseValue* IncrementExpression::eval() {
	//Код, вероятно, немножко не оптимален. Стоит на будущее его подправить
	BaseValue* operand = exp->eval();
	BaseValue* res;

	if (operand->get_type() != NUMBER_TYPE)
		res = new NanType();
	else
		res = new NumberType(this->op1 == INCREMENT ? operand->get_as_number() + 1 : operand->get_as_number() - 1);

	try {
		Environment* current = this->block;
		if (current == NULL) {
			BaseValue* elem = Variables::get(var_name);
			if (elem->get_type() == FUNCTION_TYPE || elem->get_type() == OBJECT_TYPE) {
				((DotExpression*)this->exp)->set_expression_to_write(new EmptyExpression(res));
				this->exp->eval();
			}
			else
				Variables::set(var_name, res, false);
		}
		else {
			while (current != NULL) {
				try {
					current->records->get_local(var_name);
					break;
				}
				catch (BaseException* error_message) {
					current = current->outer;
				}
			}
			if (current == NULL) {
				try {
					Variables::get(var_name);
					Variables::set(var_name, res, false);
					return this->op == 'l' ? res : operand;
				}
				catch (BaseException* error_message) {
					block->records->set_local(var_name, res, false);
					return this->op == 'l' ? res : operand;
				}
			}
			BaseValue* elem = current->records->get_local(var_name);
			if (elem->get_type() == FUNCTION_TYPE || elem->get_type() == OBJECT_TYPE) {
				((DotExpression*)this->exp)->set_expression_to_write(new EmptyExpression(res));
				this->exp->eval();
			}
			else
				current->records->set_local(var_name, res, false);
		}
	}
	catch (BaseException* err) {
		throw Errors::throw_error(ExceptionTypes::SyntaxError, string("Invalid left-hand side expression in ") + (this->op == 'r' ? "postfix" : "prefix") + " operation");
	}

	return this->op == 'l' ? res : operand;
}