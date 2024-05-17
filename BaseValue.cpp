#include "BaseValue.h"
#include <stdexcept>
#include "ObjectExpression.h"
#include "NativeCodeRealisation.h"

BaseValue::BaseValue(string data, variable_t type) {
	this->data = data;
	this->type = type;
}

BaseValue::BaseValue(ObjectExpression* data) {
	this->data = "";
	this->ref = data;
	this->type = FUNCTION_TYPE;
}

BaseValue::BaseValue(ObjectExpression* data, variable_t type) {
	this->data = "";
	this->ref = data;
	this->type = type;
}

variable_t BaseValue::get_type() {
	return this->type;
}

ObjectExpression* BaseValue::get_ref() {
	return this->ref;
}

string BaseValue::get_as_string() {
	if (type == BOOL_TYPE) {
		if (this->data == "") return "false";
		return "true";
	}
	if (type == NAN_TYPE) {
		return "NaN";
	}
	if (type == UNDEFINED_TYPE) {
		return "undefined";
	}
	if (type == NULL_TYPE) {
		return "null";
	}
	if (type == OBJECT_TYPE) {
		return "object [Object]";
	}
	if (type == FUNCTION_TYPE) {
		return "[Function]";
	}
	return this->data;
}

double BaseValue::get_as_number() {
	if (type == BOOL_TYPE) {
		if (this->data == "") return 0;
		return 1;
	}
	if (type == NULL_TYPE) {
		return 0;
	}
	try {
		return stod(this->data);
	} catch(const std::invalid_argument& e) {
		return NAN;
	}
}

bool BaseValue::get_as_boolean() {
	if (type == NULL_TYPE) {
		return false;
	}
	if (type == FUNCTION_TYPE || type == OBJECT_TYPE) {
		return true;
	}
	if (this->data == "") return false;
	try {
		if (stod(this->data) > 0) return true;
		else return false;
	}
	catch (const std::invalid_argument& e) {
		return this->data.size() > 0 ? true : false;
	}
}