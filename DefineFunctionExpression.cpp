#include "DefineFunctionExpression.h"
#include "string"
#include "Token.h"
#include "Functions.h"

using namespace std;

DefineFunctionExpression::DefineFunctionExpression(string name, BlockStatement* block, bool is_struct) {
	this->name = name;
	this->block = block;
	this->is_struct = is_struct;
}

void DefineFunctionExpression::add(string arg) {
	this->args.push_back(arg);
}

vector<string>* DefineFunctionExpression::get_arg_list() {
	return &this->args;
}

void DefineFunctionExpression::setBody(BlockStatement* body) {
	this->body = body;
}

BlockStatement* DefineFunctionExpression::getBody() {
	return this->body;
}

BaseValue* DefineFunctionExpression::eval() {
	BaseValue* function = new BaseValue(this);
	if (block == NULL) Variables::set(this->name, function, this->is_struct);
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
				Variables::set(this->name, function, this->is_struct);
				return 0;
			}
			catch (const char* error_message) {
				block->local_env->set_local(this->name, function, this->is_struct);
				return 0;
			}
		}
		current->local_env->set_local(this->name, function, this->is_struct);
	}
	return 0;
}