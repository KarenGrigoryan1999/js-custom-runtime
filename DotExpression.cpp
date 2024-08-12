#include "DotExpression.h"

using namespace std;

DotExpression::DotExpression(Expression* exp, string property_name) {
	this->exp = exp;
	this->property_name = property_name;
	this->read = true;
	this->is_hidden_property = false;
}

DotExpression::DotExpression(Expression* exp, HiddenProperties property_name) {
	this->exp = exp;
	this->read = true;
	this->is_hidden_property = true;
	this->hidden_property_name = property_name;
	this->expression_to_write = NULL;
}

void DotExpression::set_expression_to_write(Expression* exp) {
	this->read = false;
	this->expression_to_write = exp;
}

BaseValue* DotExpression::eval() {
	BaseValue* obj = this->exp->eval();
	variable_t var_type = obj->get_type();
	//Если перед точкой undefined или null, то боксинг работать не должен и мы можем сразу выкинуть исключение
	if (var_type == UNDEFINED_TYPE || var_type == NULL_TYPE) {
		throw Errors::throw_error(ExceptionTypes::TypeError, string("Cannot read properties of ") + (var_type == UNDEFINED_TYPE ? "undefined" : "null") + " (reading '" + property_name + "')");
	}
	// Если перед точной примитивный тип, то делаем боксинг, чтобы работать со свойствами
	if (var_type == STRING_TYPE) {
		obj = this->primitive_to_object_instance(STRING_TYPE);
	}

	if (this->read) {
		if(this->is_hidden_property)
			return ((ObjectExpression*)obj->get_ref())->get_hidden_property(this->hidden_property_name);
		else
			return ((ObjectExpression*)obj->get_ref())->get_property_value(property_name);
	}
	else {
		if (this->is_hidden_property)
			return ((ObjectExpression*)obj->get_ref())->set_hidden_property(HiddenProperties::PrimitiveValue, this->expression_to_write);
		else
		return ((ObjectExpression*)obj->get_ref())->set_property_value(property_name, this->expression_to_write);
	}
}

BaseValue* DotExpression::primitive_to_object_instance(variable_t type) {
	BaseValue* primitive_prototype = NULL;
	if (type == STRING_TYPE) {
		primitive_prototype = Variables::get("String");
	}
	
	ObjectExpression* string_object = new ObjectExpression(false);//Создаем новый объект
	BaseValue* evaluated_obj = string_object->eval();

	ObjectExpression* object_reference = evaluated_obj->get_ref();

	object_reference->set_property_value("__proto__", primitive_prototype->get_ref()->get_property_value("prototype"));
	object_reference->set_hidden_property(HiddenProperties::PrimitiveValue, this->exp);
	
	return evaluated_obj;
}