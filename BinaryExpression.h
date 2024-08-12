#ifndef BINARY_EXPRESSION_H
#define BINARY_EXPRESSION_H

#include <vector>
#include "string"
#include "Expression.h"
#include "TokenType.h"

using namespace std;

class BinaryExpression: public Expression
{
public:
	BinaryExpression(token_t op, Expression* exp1, Expression* exp2);
	BaseValue* eval() override;
	const char* plain_name = "AnonumousFuncExpression";
private:
	token_t op;
	Expression* exp1;
	Expression* exp2;
};

#endif