#include "string"
#include "VariableExpression.h"
#include "Token.h"
#include "Variables.h"

using namespace std;

VariableExpression::VariableExpression(string name, BlockStatement* block) {
	this->name = name;
	this->block = block;
}

BaseValue* VariableExpression::eval() {
	if (this->block != NULL) {
		BlockStatement* current = this->block;

		while (current != NULL) {
			try {
				return current->local_env->get_local(this->name);
			}
			catch (const char* error_message) {
				current = current->prev;
			}
		}
	}
	return Variables::get(this->name);
}