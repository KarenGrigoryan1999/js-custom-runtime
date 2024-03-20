#ifndef STATEMENT_STATEMENT_H
#define STATEMENT_STATEMENT_H

#include <vector>
#include "string"
#include "Statement.h"
#include "Expression.h"
#include "Variables.h"

using namespace std;

class BlockStatement : public Statement
{
public:
	BlockStatement(BlockStatement* statement);
	void add(Node* statement);
	BaseValue* eval() override;
	Variables* local_env;
	BlockStatement* prev;
private:
	vector<Node*> statements;
};

#endif