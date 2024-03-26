#ifndef NAN_TYPE_H
#define NAN_TYPE_H

#include "string"
#include "BaseValue.h"
#include "VariableTypes.h"

using namespace std;

class NanType : public virtual BaseValue
{
public:
	NanType() : BaseValue{ "", NAN_TYPE } {};
};

#endif