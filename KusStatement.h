#ifndef KUS_STATEMENT_H
#define KUS_STATEMENT_H

#include <vector>
#include "string"
#include "Statement.h"
#include "Expression.h"

using namespace std;

class KusStatement : public Statement
{
public:
	KusStatement(Expression* exp);
	BaseValue* eval() override;
private:
	Expression* exp;
};

#endif