#include "IfStatement.h"
#include "Token.h"
#include "NumberType.h"
#include "StringType.h"

using namespace std;

IfStatement::IfStatement(Expression* condition, Node* ifStatement, Node* elseStatement) {
	this->condition = condition;
	this->ifStatement = ifStatement;
	this->elseStatement = elseStatement;
}

BaseValue* IfStatement::eval() {
	BaseValue* result = this->condition->eval();

	if (result->get_as_boolean()) {
		this->ifStatement->eval();
	}
	else if(this->elseStatement != NULL) {
		this->elseStatement->eval();
	}

	return 0;
}