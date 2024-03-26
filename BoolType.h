#ifndef BOOL_TYPE_H
#define BOOL_TYPE_H

#include "string"
#include "BaseValue.h"
#include "VariableTypes.h"

using namespace std;

class BoolType : public virtual BaseValue
{
public:
	BoolType(bool data) : BaseValue{ data ? "1" : "", BOOL_TYPE} {};
};

#endif