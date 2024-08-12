#include "string"
#include "VariableExpression.h"
#include "Token.h"
#include "Variables.h"
#include "ContextStack.h"

using namespace std;

VariableExpression::VariableExpression(string name, Environment* block) {
	this->name = name;
	this->block = block;
}

BaseValue* VariableExpression::eval() {
	if (this->block != NULL) {
		Environment* current = this->block;
		
		while (current != NULL) {
			if (current->records == NULL) {
				current = current->outer;
				continue;
			}
			try {
				return current->records->get_local(name);
			}
			catch (BaseException* error_message) {
				current = current->outer;
			}
		}
	}
	return Variables::get(this->name);
}