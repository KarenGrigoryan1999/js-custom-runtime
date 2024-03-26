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
	BlockStatement(BlockStatement* statement, bool is_func_body);
	BlockStatement(BlockStatement* statement);
	void add(Node* statement);
	BaseValue* eval() override;
	Variables* local_env;
	BlockStatement* prev;
	void refresh_env();
private:
	vector<Node*> statements;
	bool is_func_body = false;
};

#endif