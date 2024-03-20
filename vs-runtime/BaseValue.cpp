#include "BaseValue.h"

BaseValue::BaseValue(string data, variable_t type) {
	this->data = data;
	this->type = type;
}

variable_t BaseValue::get_type() {
	return this->type;
}

string BaseValue::get_as_string() {
	if (type == BOOL_TYPE) {
		if (this->data == "") return "false";
		return "true";
	}
	return this->data;
}

double BaseValue::get_as_number() {
	return stod(this->data);
}

bool BaseValue::get_as_boolean() {
	return this->data.size() > 0 ? true : false;
}