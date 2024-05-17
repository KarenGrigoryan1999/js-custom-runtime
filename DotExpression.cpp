#include "DotExpression.h"
#include "Token.h"
#include "NumberType.h"
#include "StringType.h"
#include "TokenType.h"
#include "NanType.h"
#include "ObjectExpression.h"
#include "Variables.h"
#include "NewExpression.h"
#include "CallExpression.h"
#include "Errors.h"

using namespace std;

DotExpression::DotExpression(Expression* exp, string property_name) {
	this->exp = exp;
	this->property_name = property_name;
	this->read = true;
}

void DotExpression::set_expression_to_write(Expression* exp) {
	this->read = false;
	this->expression_to_write = exp;
}

BaseValue* DotExpression::eval() {
	BaseValue* obj = this->exp->eval();
	if (this->read) {
		variable_t var_type = obj->get_type();
		//Если перед точкой undefined или null, то боксинг работать не должен и мы можем сразу выкинуть исключение
		if (var_type == UNDEFINED_TYPE || var_type == NULL_TYPE) {
			throw Errors::throw_error(ExceptionTypes::TypeError, string("Cannot read properties of ") + (var_type == UNDEFINED_TYPE ? "undefined" : "null") + " (reading '" + property_name + "')");
		}
		// Если перед точной примитивный тип, то делаем боксинг, чтобы работать со свойствами
		if (var_type == STRING_TYPE) {
			obj = this->primitive_to_object_instance(STRING_TYPE);
		}
		return ((ObjectExpression*)obj->get_ref())->get_property_value(property_name);
	}
	else {
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
	object_reference->add_property("[[PrimitiveValue]]", this->exp);
	
	return evaluated_obj;
}