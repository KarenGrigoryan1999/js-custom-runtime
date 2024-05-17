#ifndef FUNCTION_DECLARATION_H
#define FUNCTION_DECLARATION_H

#include <vector>
#include "string"
#include "Expression.h"
#include "Node.h"
#include "BlockStatement.h"
#include "AnonumousFuncExpression.h"
#include "Environment.h"

using namespace std;

class FunctionDeclaration : public Expression
{
public:
	FunctionDeclaration(string name, Environment* block, bool is_const);
	BaseValue* eval() override;
	AnonumousFuncExpression* function;
private:
	bool is_const;
	string name;
	Environment* block;
};

#endif