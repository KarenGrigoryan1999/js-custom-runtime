#ifndef NUMBERIC_EXPRESSION_H
#define NUMBERIC_EXPRESSION_H

#include <vector>
#include "string"
#include "Expression.h"
#include "BaseValue.h"

using namespace std;

class NumberExpression: public Expression
{
public:
	NumberExpression(string value);
	BaseValue* eval() override;
private:
	string value;
};

#endif