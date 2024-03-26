#ifndef VARIABLE_STATEMENT_H
#define VARIABLE_STATEMENT_H

#include <vector>
#include "string"
#include "Statement.h"
#include "Expression.h"
#include "BaseValue.h"
#include "BlockStatement.h"

using namespace std;

class VariableStatement : public Statement
{
public:
	VariableStatement(string name, bool is_struct, BlockStatement* block, Expression* exp);
	BaseValue* eval() override;
private:
	string name;
	bool is_struct;
	BlockStatement* block;
	Expression* exp;
};

#endif