#ifndef INCREMENT_EXPRESSION_H
#define INCREMENT_EXPRESSION_H

#include <vector>
#include "string"
#include "Expression.h"
#include "TokenType.h"
#include "BlockStatement.h"
#include "Errors.h"

using namespace std;

class IncrementExpression : public Expression
{
public:
	IncrementExpression(char op, token_t op1, Expression* exp1, string var_name, Environment* block);
	BaseValue* eval() override;
private:
	char op;
	token_t op1;
	Expression* exp;
	string var_name;
	Environment* block;
};

#endif