#ifndef LOGICAL_EXPRESSION_H
#define LOGICAL_EXPRESSION_H

#include <vector>
#include "string"
#include "Expression.h"
#include "TokenType.h"

using namespace std;

class LogicalExpression : public Expression
{
public:
	LogicalExpression(token_t op, Expression* exp1, Expression* exp2);
	BaseValue* eval() override;
private:
	token_t op;
	Expression* exp1;
	Expression* exp2;
};

#endif