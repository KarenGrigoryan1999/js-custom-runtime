#ifndef FUNCTION_EXPRESSION_H
#define FUNCTION_EXPRESSION_H

#include <vector>
#include "string"
#include "Expression.h"
#include "BaseValue.h"
#include "BlockStatement.h"

using namespace std;

class FunctionExpression : public Expression
{
public:
	FunctionExpression(string name, BlockStatement* block);
	BaseValue* eval() override;
	void add(Expression* exp);
private:
	string name;
	vector<Expression*> args;
	BlockStatement* block;
};

#endif