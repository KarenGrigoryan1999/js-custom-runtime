#include "Functions.h"
#include "BaseValue.h"
#include "NumberType.h"
#include "Expression.h"
#include "ObjectExpression.h"
#include "EmptyExpression.h"
#include "BoolType.h"
#include "NanType.h"
#include <iostream>
#include "Errors.h"

using namespace std;

#define BLUE_TEXT "\033[34m"
#define LIGHT_YELLOW_TEXT "\033[93m"
#define ANSI_COLOR_GRAY "\x1b[90m"
#define RESET_COLOR "\033[0m"

BaseValue* print(vector<Expression*>* args) {
	for (int i = 0; i < args->size(); i++) {
		BaseValue* res = args->at(i)->eval();
		switch (res->get_type())
		{
		case NUMBER_TYPE:
			cout << BLUE_TEXT << res->get_as_number() << RESET_COLOR;
			break;
		case UNDEFINED_TYPE:
			cout << ANSI_COLOR_GRAY << res->get_as_string() << RESET_COLOR;
			break;
		case NULL_TYPE:
			cout << BLUE_TEXT << res->get_as_string() << RESET_COLOR;
			break;
		case OBJECT_TYPE:
		{
			cout << ANSI_COLOR_GRAY << "{" << endl;
			ObjectExpression* obj = res->get_ref();
			vector<string>* obj_keys = obj->get_keys();
			for (int i = 0; i < obj_keys->size(); i++) {
				cout << "   " << obj_keys->at(i) << ": " << obj->get_property_value(obj_keys->at(i))->get_as_string() << endl;
			}
			cout << "}" << RESET_COLOR;
			break;
		}
		default:
			cout << LIGHT_YELLOW_TEXT  << res->get_as_string() << RESET_COLOR;
			break;
		}
	}
	cout << endl;

	return new BaseValue("", NUMBER_TYPE);
}

BaseValue* input(vector<Expression*>* args) {
	string temp;
	if(args->size() > 0) cout << args->at(0)->eval()->get_as_string();
	cin >> temp;

	return new BaseValue(temp, STRING_TYPE);
}

BaseValue* is_nan(vector<Expression*>* args) {
	string temp;
	if (args->at(0)->eval()->get_type() == NAN_TYPE) return new BoolType(true);

	return new BoolType(false);
}

BaseValue* parse_int(vector<Expression*>* args) {
	string str = args->at(0)->eval()->get_as_string();
	string buffer = "";
	for (int i = 0; i < str.size(); i++) {
		if (std::isdigit(str[i])) buffer += str[i];
		else break;
	}

	if (buffer == "") return new NanType();

	return new NumberType(stod(buffer));
}

BaseValue* Functions::get(string name, vector<Expression*>* args) {
	if (name == "print") {
		return print(args);
	}
	if (name == "meow") {
		return input(args);
	}
	if (name == "isNaN") {
		return is_nan(args);
	}
	if (name == "parseInt") {
		return parse_int(args);
	}

	Errors::throw_error(ExceptionTypes::ReferenceError, "function is not defined");
}
