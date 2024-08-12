#ifndef UNARY_EXPRESSION_H
#define UNARY_EXPRESSION_H

#include <vector>
#include "string"
#include "Expression.h"
#include "BaseValue.h"
#include "TokenType.h"

using namespace std;

class UnaryExpression : public Expression
{
public:
	UnaryExpression(token_t op, Expression* exp1);
	BaseValue* eval() override;
	const char* plain_name = "UnaryExpression";
private:
	token_t op;
	Expression* exp1;
};

#endif