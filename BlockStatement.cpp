#include "iostream"
#include "BlockStatement.h"
#include "Parser.h"

using namespace std;

BlockStatement::BlockStatement(BlockStatement* statement, bool is_func_body) {
	if(is_func_body == true) {
		this->local_env = NULL;
	}
	else {
		this->local_env = new Variables();
	}
	this->is_func_body = is_func_body;
	this->prev = statement;
}

BlockStatement::BlockStatement(BlockStatement* statement) {
	this->local_env = new Variables();
	this->prev = statement;
}

void BlockStatement::add(Node* statement) {
	this->statements.push_back(statement);
}

void BlockStatement::refresh_env() {
	if (Variables::size() != 0) {
		this->local_env = Variables::top();
	}
	else {
		this->local_env = NULL;
	}
}

BaseValue* BlockStatement::eval() {
	for (int i = 0; i < this->statements.size(); i++) {
		this->statements[i]->eval();
	}

	if (this->is_func_body == false) this->local_env = new Variables();//Очень странные код, надо как-то исправить

	return 0;
}