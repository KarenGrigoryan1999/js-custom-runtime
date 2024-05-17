#ifndef RETURN_EXPRESSION_H
#define RETURN_EXPRESSION_H

#include <vector>
#include "string"
#include "Expression.h"
#include "BaseValue.h"
#include "TokenType.h"
#include "NanType.h"

using namespace std;

class ReturnExpression : public Expression
{
public:
	ReturnExpression(Expression* exp);
	ReturnExpression();
	BaseValue* eval() override;
	BaseValue* get_result();
protected:
	Expression* exp;
	BaseValue* result;
};

#endif