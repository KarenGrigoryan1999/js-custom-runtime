#ifndef TYPEOF_STATEMENT_H
#define TYPEOF_STATEMENT_H

#include <vector>
#include "string"
#include "Statement.h"
#include "Expression.h"

using namespace std;

class TypeofExpression : public Expression
{
public:
	TypeofExpression(Expression* exp);
	BaseValue* eval() override;
	const char* plain_name = "TypeofExpression";
private:
	Expression* exp;
};

#endif