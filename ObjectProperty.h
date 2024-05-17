#pragma once
#include "BaseValue.h"
#include "ObjectPropertyDescriptorState.h"

struct object_property {
	BaseValue* value;
	PropertyDescriptorState writable;
	PropertyDescriptorState configurable;
	PropertyDescriptorState enumerable;
	BaseValue* get;
	BaseValue* set;
};