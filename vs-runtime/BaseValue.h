#ifndef BASE_VALUE_H
#define BASE_VALUE_H

#include "string"
#include "VariableTypes.h"

using namespace std;

class BaseValue
{
public:
	BaseValue(string data, variable_t type);
	string get_as_string();
	double get_as_number();
	bool get_as_boolean();
	variable_t get_type();
protected:
	string data;
	variable_t type;
};

#endif