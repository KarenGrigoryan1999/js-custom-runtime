#ifndef VARIABLE_EXPRESSION_H
#define VARIABLE_EXPRESSION_H

#include <vector>
#include "string"
#include "Expression.h"
#include "BaseValue.h"
#include "BlockStatement.h"
#include "ReferenceError.h"

using namespace std;

class VariableExpression : public Expression
{
public:
	VariableExpression(string name, Environment* block);
	BaseValue* eval() override;
	const char* plain_name = "VariableExpression";
private:
	string name;
	Environment* block;
};

#endif