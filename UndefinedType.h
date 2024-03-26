#ifndef UNDEFINED_TYPE_H
#define UNDEFINED_TYPE_H

#include "string"
#include "BaseValue.h"
#include "VariableTypes.h"

using namespace std;

class UndefinedType : public virtual BaseValue
{
public:
	UndefinedType() : BaseValue{ "", UNDEFINED_TYPE } {};
};

#endif