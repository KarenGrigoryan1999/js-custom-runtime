#include "NativeCodeRealisation.h"
#include "string"
#include "StringType.h"
#include "Token.h"
#include "Expression.h"
#include "DotExpression.h"
#include "ThisExpression.h"
#include "UndefinedType.h"
#include "Environment.h"
#include "ContextStack.h"
#include "ObjectExpression.h"
#include "Errors.h"

using namespace std;

NativeCodeRealisation::NativeCodeRealisation(native_method_type type) {
	this->type = type;
}

BaseValue* NativeCodeRealisation::eval() {
	if (this->type == OBJECT_DEFINE_PROPERTY) {
		Variables* env = ContextStack::top()->get_environment_record()->records;
		BaseValue* current_obj = env->get_local("obj");
		BaseValue* obj_property = env->get_local("prop");
		BaseValue* obj_config = env->get_local("conf");
		ObjectExpression* obj_config_ref = obj_config->get_ref();

		if (current_obj->get_type() != FUNCTION_TYPE && current_obj->get_type() != OBJECT_TYPE) {
			throw Errors::throw_error(ExceptionTypes::ReferenceError, "Object.defineProperty called on non-object");
		}

		if (obj_property->get_type() != STRING_TYPE) {
			throw Errors::throw_error(ExceptionTypes::TypeError, "Invalid property descriptor. Cannot both specify accessors and a value or writable attribute, #<Object>");
		}

		if (obj_config->get_type() != FUNCTION_TYPE && obj_config->get_type() != OBJECT_TYPE) {
			throw Errors::throw_error(ExceptionTypes::TypeError, "Property description must be an object" + obj_config->get_as_string());
		}

		object_property prop;
		BaseValue* w = obj_config_ref->get_property_value("writable");
		BaseValue* c = obj_config_ref->get_property_value("configurable");
		BaseValue* e = obj_config_ref->get_property_value("enumirable");
		BaseValue* value = obj_config_ref->get_property_value("value");
		BaseValue* get = obj_config_ref->get_property_value("get");
		BaseValue* set = obj_config_ref->get_property_value("set");

		prop.writable = this->convert_to_object_property_descriptor_state(w);
		prop.configurable = this->convert_to_object_property_descriptor_state(c);
		prop.enumerable = this->convert_to_object_property_descriptor_state(e);
		if (value->get_type() != UNDEFINED_TYPE) prop.value = value;
		else prop.value = NULL;
		if (get->get_type() != UNDEFINED_TYPE) prop.get = get;
		else prop.get = NULL;
		if (set->get_type() != UNDEFINED_TYPE) prop.set = set;
		else prop.set = NULL;

		if (
			(get != NULL || set != NULL) &&
			(prop.writable != PropertyDescriptorState::UNSET || prop.enumerable != PropertyDescriptorState::UNSET || prop.configurable != PropertyDescriptorState::UNSET)
		) {
			throw Errors::throw_error(ExceptionTypes::TypeError, "Invalid property descriptor. Cannot both specify accessors and a value or writable attribute, #<Object>");
		}

		BaseValue* val = current_obj->get_ref()->set_property_with_descriptors(obj_property->get_as_string(), &prop);

		return new UndefinedType();
	}
	string val = (new DotExpression(new ThisExpression(), "[[PrimitiveValue]]"))->eval()->get_as_string();
	if (this->type == STRING_TO_LOWER_CASE) {
		for (char& c : val) {
			c = tolower(c);
		}
	}

	if (this->type == STRING_TO_UPPER_CASE) {
		for (char& c : val) {
			c = toupper(c);
		}
	}
	
	this->result = new StringType(val);
	throw this;
}

PropertyDescriptorState NativeCodeRealisation::convert_to_object_property_descriptor_state(BaseValue* val) {
	if (val->get_type() != UNDEFINED_TYPE) {
		return val->get_as_boolean() ? PropertyDescriptorState::TURNED_ON : PropertyDescriptorState::TURNED_OFF;
	}
	return PropertyDescriptorState::UNSET;
}