#ifndef NUMBER_TYPE_H
#define NUMBER_TYPE_H

#include "string"
#include "BaseValue.h"
#include "VariableTypes.h"

using namespace std;

class NumberType: public virtual BaseValue
{
public:
	NumberType(double data) : BaseValue{ to_string(data), NUMBER_TYPE } {};
};

#endif