#ifndef EMPTY_EXPRESSION_H
#define EMPTY_EXPRESSION_H

#include "Expression.h"
#include "BaseValue.h"

using namespace std;

class EmptyExpression : public Expression
{
public:
	EmptyExpression(BaseValue* value);
	BaseValue* eval() override;
private:
	BaseValue* value;
};

#endif