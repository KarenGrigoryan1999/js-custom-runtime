#ifndef BASE_VALUE_H
#define BASE_VALUE_H

#include "string"
#include "VariableTypes.h"

using namespace std;

class DefineFunctionExpression;
class BaseValue
{
public:
	BaseValue(string data, variable_t type);
	BaseValue(DefineFunctionExpression* exp);
	string get_as_string();
	double get_as_number();
	bool get_as_boolean();
	variable_t get_type();
	DefineFunctionExpression* get_ref();
protected:
	string data;
	variable_t type;
	DefineFunctionExpression* ref;
};

#endif