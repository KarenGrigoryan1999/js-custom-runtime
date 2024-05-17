#include "string"
#include <iostream>
#include "CallExpression.h"
#include "Token.h"
#include "Functions.h"
#include "FunctionDeclaration.h"
#include "ReturnExpression.h"
#include "UndefinedType.h"
#include "Environment.h"
#include "ContextStack.h"
#include "ExecutionContext.h"

using namespace std;

CallExpression::CallExpression(string name, Environment* block) {
	this->name = name;
	this->block = block;
	this->func_exp = NULL;
	this->evaluated_function = NULL;
}

CallExpression::CallExpression(Expression* exp, Environment* block) {
	this->func_exp = exp;
	this->block = block;
	this->evaluated_function = NULL;
}

void CallExpression::add(Expression* exp) {
	this->args.push_back(exp);
}

void CallExpression::set_this_object(Expression* obj_expression) {
	this->obj_expression = obj_expression;
}

BaseValue* CallExpression::eval() {
	AnonumousFuncExpression* func_ref;
	if (!this->func_exp) {
		BaseValue* func = NULL;
		if (this->block != NULL && this->block->records != NULL) {
			Environment* current = this->block;

			while (current != NULL) {
				try {
					func = current->records->get_local(this->name);
					break;
				}
				catch (string error_message) {
					current = current->outer;
				}
			}
		}

		try {
			if (func == NULL) func = Variables::get(this->name);
		}
		catch (string msg) {
			return Functions::get(this->name, &this->args);
		}

		func_ref = (AnonumousFuncExpression*)func->get_ref();
	}
	else {
		func_ref = (AnonumousFuncExpression*)func_exp->eval()->get_ref();
	}
	this->evaluated_function = func_ref;
	
	Environment func_env = { new Variables(), NULL };

	ExecutionContext* exec_context = new ExecutionContext();
	exec_context->set_environment_record(&func_env);
	if(this->obj_expression)
		exec_context->set_this_binding(this->obj_expression->eval());
	else
		exec_context->set_this_binding(new UndefinedType());

	 vector<string>* arg_list = func_ref->get_arg_list();

	for (int i = 0; i < arg_list->size(); i++) {
		func_env.records->set_local(arg_list->at(i), this->args.at(i)->eval(), false);
	}

	ContextStack::push(exec_context);

	func_ref->getBody()->refresh_env();

	BaseValue* ret = new UndefinedType();
	try {
		func_ref->getBody()->eval();
	}
	catch (ReturnExpression* rt) {
		ret = rt->get_result();
		if (ret->get_type() == FUNCTION_TYPE) {
			AnonumousFuncExpression* anon_func = (AnonumousFuncExpression*)ret->get_ref();
			anon_func->getBody()->env->outer = new Environment();
			anon_func->getBody()->env->outer->outer = func_ref->getBody()->env->outer;
			anon_func->getBody()->env->outer->records = func_ref->getBody()->env->records;
		}
	}

	ContextStack::pop();

	func_ref->getBody()->refresh_env();

	return ret;
}
