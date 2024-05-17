#ifndef BASE_VALUE_H
#define BASE_VALUE_H

#include "string"
#include "VariableTypes.h"

using namespace std;

class ObjectExpression;
class BaseValue
{
public:
	BaseValue(string data, variable_t type);
	BaseValue(ObjectExpression* exp, variable_t type);
	BaseValue(ObjectExpression* exp);
	virtual string get_as_string();
	virtual double get_as_number();
	virtual bool get_as_boolean();
	variable_t get_type();
	virtual ObjectExpression* get_ref();
protected:
	string data;
	variable_t type;
	ObjectExpression* ref;
};

#endif