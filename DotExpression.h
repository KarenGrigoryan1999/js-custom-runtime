#ifndef DOT_EXPRESSION_H
#define DOT_EXPRESSION_H

#include <vector>
#include "string"
#include "Expression.h"

using namespace std;

class DotExpression : public Expression
{
public:
	DotExpression(Expression* exp, string property_name);
	BaseValue* eval() override;
	void set_expression_to_write(Expression* exp);
private:
	Expression* exp;
	string property_name;
	Expression* expression_to_write;
	bool read;
	BaseValue* primitive_to_object_instance(variable_t type);
};

#endif