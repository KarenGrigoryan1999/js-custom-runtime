#ifndef STRING_TYPE_H
#define STRING_TYPE_H

#include "string"
#include "BaseValue.h"
#include "VariableTypes.h"

using namespace std;

class StringType : public virtual BaseValue
{
public:
	StringType(string data) : BaseValue(data, STRING_TYPE) {};
};

#endif