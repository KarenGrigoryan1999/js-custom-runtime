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
	VariableStatement(string name, Environment* block, Expression* exp, bool is_const, bool is_declaration);
	BaseValue* eval() override;
	const char* plain_name = "VariableStatement";
private:
	string name;
	bool is_const;
	bool is_declaration;
	Environment* block;
	Expression* exp;
};

#endif