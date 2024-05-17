#include "FunctionBodyStatement.h"
#include "iostream"
#include "BlockStatement.h"
#include "Parser.h"
#include "ContextStack.h"
#include "Variables.h"

using namespace std;

void FunctionBodyStatement::add(Node* statement) {
	this->statements.push_back(statement);
}

void FunctionBodyStatement::refresh_env() {
	if (ContextStack::size() != 0) {
		this->env->records = ContextStack::top()->get_environment_record()->records;
	}
	else {
		this->env->records = NULL;
	}
}

BaseValue* FunctionBodyStatement::eval() {
	for (int i = 0; i < this->statements.size(); i++) {
		this->statements[i]->eval();
	}

	this->env->records = new Variables();

	return 0;
}