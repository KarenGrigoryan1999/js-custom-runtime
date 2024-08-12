#ifndef BASE_BLOCK_STATEMENT_H
#define BASE_BLOCK_STATEMENT_H

#include <vector>
#include "string"
#include "Statement.h"
#include "Expression.h"
#include "Variables.h"
#include "Environment.h"

using namespace std;

class BlockBaseStatement : public Statement
{
public:
	BlockBaseStatement(Environment* statement);
	void add(Node* statement);
	Environment* env;
	BaseValue* eval() override;
	const char* plain_name = "BlockBaseStatement";
private:
	vector<Node*> statementList;
};

#endif