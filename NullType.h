#ifndef NULL_TYPE_H
#define NULL_TYPE_H

#include "string"
#include "BaseValue.h"
#include "VariableTypes.h"

using namespace std;

class NullType : public virtual BaseValue
{
public:
	NullType() : BaseValue{ "", NULL_TYPE } {};
};

#endif