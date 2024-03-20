#include "Functions.h"
#include "BaseValue.h"
#include "NumberType.h"
#include "Expression.h"
#include <iostream>

using namespace std;

#define BLUE_TEXT "\033[34m"
#define LIGHT_YELLOW_TEXT "\033[93m"
#define RESET_COLOR "\033[0m"

BaseValue* print(vector<Expression*>* args) {
	for (int i = 0; i < args->size(); i++) {
		BaseValue* res = args->at(i)->eval();
		switch (res->get_type())
		{
		case NUMBER_TYPE:
			cout << BLUE_TEXT << res->get_as_number() << RESET_COLOR;
			break;
		default:
			cout << LIGHT_YELLOW_TEXT  << res->get_as_string() << RESET_COLOR;
			break;
		}
		cout << ' ';
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

BaseValue* Functions::get(string name, vector<Expression*>* args) {
	if (name == "print") {
		return print(args);
	}
	if (name == "meow") {
		return input(args);
	}

	throw "Uncaught ReferenceError: function is not defined";
}