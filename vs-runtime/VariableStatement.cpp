#include "VariableStatement.h"
#include "Expression.h"
#include "Variables.h"

VariableStatement::VariableStatement(string name, bool is_struct, BlockStatement* block, Expression* exp) {
	this->name = name;
	this->exp = exp;
	this->is_struct = is_struct;
	this->block = block;
}

BaseValue* VariableStatement::eval() {
	BaseValue* evaluated_data = this->exp->eval();
	if (block == NULL) Variables::set(this->name, evaluated_data, this->is_struct);
	else {
		BlockStatement* current = this->block;

		while (current != NULL) {
			try {
				current->local_env->get_local(this->name);
				break;
			}
			catch (const char* error_message) {
				current = current->prev;
			}
		}
		if (current == NULL) {
			try {
				Variables::get(this->name);
				Variables::set(this->name, evaluated_data, this->is_struct);
				return evaluated_data;
			}
			catch (const char* error_message) {
				block->local_env->set_local(this->name, evaluated_data, this->is_struct);
				return evaluated_data;
			}
		}
		current->local_env->set_local(this->name, evaluated_data, this->is_struct);
	}
	return evaluated_data;
}