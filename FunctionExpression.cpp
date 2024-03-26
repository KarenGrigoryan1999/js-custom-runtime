#include "FunctionExpression.h"
#include "string"
#include "Token.h"
#include "Functions.h"
#include "DefineFunctionExpression.h"
#include "ReturnExpression.h"
#include "UndefinedType.h"

using namespace std;

FunctionExpression::FunctionExpression(string name, BlockStatement* block) {
	this->name = name;
	this->block = block;
}

void FunctionExpression::add(Expression* exp) {
	this->args.push_back(exp);
}

BaseValue* FunctionExpression::eval() {
	BaseValue* func = NULL;
	if (this->block != NULL) {
		BlockStatement* current = this->block;

		while (current != NULL) {
			try {
				func = current->local_env->get_local(this->name);
				throw "err";
			}
			catch (const char* error_message) {
				current = current->prev;
			}
		}
	}

	try {
		if(func == NULL) func = Variables::get(this->name);
	}
	catch (const char* msg) {
		return Functions::get(this->name, &this->args);
	}

	Variables* func_env = new Variables();

	DefineFunctionExpression* func_ref = func->get_ref();

	 vector<string>* arg_list = func_ref->get_arg_list();

	for (int i = 0; i < arg_list->size(); i++) {
		func_env->set_local(arg_list->at(i), this->args.at(i)->eval(), false);
	}

	Variables::push(func_env);

	func_ref->getBody()->refresh_env();

	BaseValue* ret = new UndefinedType();
	try {
		func_ref->getBody()->eval();
	}
	catch (ReturnExpression* rt) {
		ret = rt->get_result();
	}

	Variables::pop();

	func_ref->getBody()->refresh_env();

	return ret;
}
