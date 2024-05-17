#ifndef CALL_EXPRESSION_H
#define CALL_EXPRESSION_H

#include <vector>
#include "string"
#include "Expression.h"
#include "BaseValue.h"
#include "BlockStatement.h"
#include "AnonumousFuncExpression.h"

using namespace std;

class CallExpression : public Expression
{
public:
	CallExpression(string name, Environment* block);
	CallExpression(Expression* exp, Environment* block);
	AnonumousFuncExpression* evaluated_function;
	void set_this_object(Expression* obj_expression);
	BaseValue* eval() override;
	void add(Expression* exp);
private:
	string name;
	Expression* func_exp;
	vector<Expression*> args;
	Environment* block;
	Expression* obj_expression;
};

#endif