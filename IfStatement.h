#ifndef IF_STATEMENT_H
#define IF_STATEMENT_H

#include <vector>
#include "string"
#include "Statement.h"
#include "Expression.h"

using namespace std;

class IfStatement : public Statement
{
public:
	IfStatement(Expression* condition, Node* ifStatement, Node* elseStatement);
	BaseValue* eval() override;
	const char* plain_name = "IfStatement";
private:
	Expression* condition;
	Node* ifStatement;
	Node* elseStatement;
};

#endif