#include "BlockBaseStatement.h"
#include "iostream"
#include "BlockStatement.h"
#include "Parser.h"

using namespace std;

BlockBaseStatement::BlockBaseStatement(Environment* statement) {
	this->env = new Environment();
	this->env->records = new Variables();
	this->env->outer = statement;
}

void BlockBaseStatement::add(Node* statement) {
	this->statementList.push_back(statement);
}

BaseValue* BlockBaseStatement::eval() {
	for (int i = 0; i < this->statementList.size(); i++) {
		this->statementList[i]->eval();
	}

	return 0;
}