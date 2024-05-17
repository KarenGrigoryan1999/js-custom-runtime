#ifndef NEW_EXPRESSION_H
#define NEW_EXPRESSION_H

#include "Expression.h"
#include "BaseValue.h"

using namespace std;

class NewExpression : public Expression
{
public:
	NewExpression(Expression* exp);
	BaseValue* eval() override;
private:
	Expression* exp;
};

#endif