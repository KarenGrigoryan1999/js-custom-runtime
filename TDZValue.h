#ifndef STRING_TYPE_H
#define STRING_TYPE_H

#include "string"
#include "BaseValue.h"
#include "VariableTypes.h"

using namespace std;

class TDZValue : public virtual BaseValue
{
public:
	TDZValue() : BaseValue{ "", TDZ} {};
	variable_t get_type();
	ObjectExpression* get_ref();
	string get_as_string();
	double get_as_number();
	bool get_as_boolean();
private:
	void base_tdz_get_value();
};

#endif