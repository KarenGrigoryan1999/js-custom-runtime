#include "IncrementExpression.h"
#include "Token.h"
#include "NumberType.h"
#include "StringType.h"
#include "TokenType.h"

using namespace std;

IncrementExpression::IncrementExpression(char op, token_t op1, Expression* exp, string var_name, BlockStatement* block) {
	this->op = op;
	this->op1 = op1;
	this->exp = exp;
	this->var_name = var_name;
	this->block = block;
}

BaseValue* IncrementExpression::eval() {
	BaseValue* operand = exp->eval();

	NumberType* res = new NumberType(this->op1 == INCREMENT ? operand->get_as_number() + 1 : operand->get_as_number() - 1);

	if (block == NULL) Variables::set(var_name, res, false);
	else {
		BlockStatement* current = this->block;

		while (current != NULL) {
			try {
				current->local_env->get_local(var_name);
				break;
			}
			catch (const char* error_message) {
				current = current->prev;
			}
		}
		if (current == NULL) {
			try {
				Variables::get(var_name);
				Variables::set(var_name, res, false);
				return this->op == 'l' ? res : operand;
			}
			catch (const char* error_message) {
				block->local_env->set_local(var_name, res, false);
				return this->op == 'l' ? res : operand;
			}
		}
		current->local_env->set_local(var_name, res, false);
	}

	return this->op == 'l' ? res : operand;
}