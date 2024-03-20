#include "iostream"
#include "BlockStatement.h"
#include "Parser.h"

using namespace std;

BlockStatement::BlockStatement(BlockStatement* statement) {
	this->local_env = new Variables();
	this->prev = statement;
}

void BlockStatement::add(Node* statement) {
	this->statements.push_back(statement);
}

BaseValue* BlockStatement::eval() {
	for (int i = 0; i < this->statements.size(); i++) {
		this->statements[i]->eval();
	}

	return 0;
}