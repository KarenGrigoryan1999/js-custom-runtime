#include "string";
#include "vector";
#include "Variables.h"
#include "BaseValue.h"
#include "NumberType.h"
#include "UndefinedType.h"
#include "ObjectExpression.h"
#include "AnonumousFuncExpression.h"
#include "IfStatement.h"
#include "ThisExpression.h"
#include "CallExpression.h"
#include "DotExpression.h"
#include "StringExpression.h"
#include "VariableExpression.h"
#include "NumberType.h"
#include "ReturnExpression.h"
#include "NumberExpression.h"
#include "Functions.h"
#include "NativeCodeRealisation.h"
#include "NullType.h"
#include "Errors.h"

using namespace std;

ObjectExpression* global_context_obj = new ObjectExpression(true);

AnonumousFuncExpression* string_proto_obj = new AnonumousFuncExpression(NULL);
AnonumousFuncExpression* object_proto_obj = new AnonumousFuncExpression(NULL);

std::map<string, Variables::var_t> Variables::global_identifiers = {
	{"Object", {new BaseValue(object_proto_obj), true}},
	{"String", {new BaseValue(string_proto_obj), true}},
	{"global", {new BaseValue(global_context_obj), true}},
	{"PI", {new NumberType(3.14), true}},
	{"EXP", {new NumberType(2.7182), true}},
};

void Variables::setupDefaultPrototypes() {
	FunctionBodyStatement* constructor = new FunctionBodyStatement(new Environment());
	DotExpression* left = new DotExpression(new ThisExpression(), HiddenProperties::PrimitiveValue);
	left->set_expression_to_write(new VariableExpression("str", constructor->env));
	constructor->add(new IfStatement(new ThisExpression(), left, NULL));

	string_proto_obj->add("str");
	string_proto_obj->setBody(constructor);

	BaseValue* string_prototype = string_proto_obj->get_property_value("prototype");

	AnonumousFuncExpression* to_lower_case = new AnonumousFuncExpression(NULL);
	FunctionBodyStatement* to_lower_case_body = new FunctionBodyStatement(NULL);
	to_lower_case_body->add(new NativeCodeRealisation(STRING_TO_LOWER_CASE));
	to_lower_case->setBody(to_lower_case_body);
	string_prototype->get_ref()->add_property("toLowerCase", to_lower_case);

	AnonumousFuncExpression* to_upper_case = new AnonumousFuncExpression(NULL);
	FunctionBodyStatement* to_upper_case_body = new FunctionBodyStatement(NULL);
	to_upper_case_body->add(new NativeCodeRealisation(STRING_TO_UPPER_CASE));
	to_upper_case->setBody(to_upper_case_body);
	string_prototype->get_ref()->add_property("toUpperCase", to_upper_case);

	AnonumousFuncExpression* length_getter = new AnonumousFuncExpression(NULL);
	FunctionBodyStatement* length_getter_body = new FunctionBodyStatement(NULL);
	length_getter_body->add(new NativeCodeRealisation(STRING_LENGTH));

	object_property prop = {};
	prop.get = new BaseValue(length_getter);

	length_getter->setBody(length_getter_body);
	string_prototype->get_ref()->add_property("length", prop);

	//Object
	AnonumousFuncExpression* define_property = new AnonumousFuncExpression(NULL);
	define_property->add("obj");
	define_property->add("prop");
	define_property->add("conf");
	FunctionBodyStatement* define_property_body = new FunctionBodyStatement(NULL);
	define_property_body->add(new NativeCodeRealisation(OBJECT_DEFINE_PROPERTY));
	define_property->setBody(define_property_body);
	object_proto_obj->add_property("defineProperty", define_property);
}

BaseValue* Variables::get(string name) {
	auto it = Variables::global_identifiers.find(name);
	if (it != Variables::global_identifiers.end()) {
		BaseValue* variable = it->second.value;
		if (variable->get_type() == TDZ) {
			throw Errors::throw_error(ExceptionTypes::ReferenceError, string("Cannot access ") + name + string(" before initialization"));
		} else
		return it->second.value;
	}

	throw Errors::throw_error(ExceptionTypes::ReferenceError, name + string(" is not defined"));
}

BaseValue* Variables::get_local(string name) {
	auto it = this->identifiers.find(name);
	if (it != this->identifiers.end()) {
		BaseValue* variable = it->second.value;
		if (variable->get_type() == TDZ) {
			throw Errors::throw_error(ExceptionTypes::ReferenceError, string("Cannot access ") + name + string("before initialization"));
		} else
		return it->second.value;
	}

	throw Errors::throw_error(ExceptionTypes::ReferenceError, name + string(" is not defined"));
}

void Variables::set(string name, BaseValue* data, bool is_const) {
	auto it = Variables::global_identifiers.find(name);
	if (it != Variables::global_identifiers.end()) {
		if (it->second.is_const == true && it->second.value->get_type() != TDZ) throw Errors::throw_error(ExceptionTypes::TypeError, string("Assignment to constant variable."));
	}

	Variables::global_identifiers[name] = { data, is_const };
}

void Variables::set_local(string name, BaseValue* data, bool is_const) {
	auto it = this->identifiers.find(name);
	if (it != this->identifiers.end()) {
		if (it->second.is_const == true && it->second.value->get_type() != TDZ) throw Errors::throw_error(ExceptionTypes::TypeError, string("Assignment to constant variable."));
	}

	this->identifiers[name] = { data, is_const };
}
