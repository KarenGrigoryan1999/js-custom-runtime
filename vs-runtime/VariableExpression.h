#ifndef VARIABLE_EXPRESSION_H
#define VARIABLE_EXPRESSION_H

#include <vector>
#include "string"
#include "Expression.h"
#include "BaseValue.h"
#include "BlockStatement.h"

using namespace std;

class VariableExpression : public Expression
{
public:
	VariableExpression(string name, BlockStatement* block);
	BaseValue* eval() override;
private:
	string name;
	BlockStatement* block;
};

#endif