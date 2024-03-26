#include "string";
#include "Variables.h"
#include "BaseValue.h"
#include "NumberType.h"

using namespace std;

std::map<string, Variables::var_t> Variables::var_record = {
	{"PI", {new NumberType(3.14), true}},
	{"EXP", {new NumberType(2.7182), true}},
};

std::stack<Variables*> Variables::context_stack;

void Variables::push(Variables* env) {
	if (Variables::context_stack.size() > MAXIMUM_CALLSTACK) throw "Maximum call stack size exceeded";
	Variables::context_stack.push(env);
}

Variables* Variables::top() {
	return Variables::context_stack.top();
}

int Variables::size() {
	return Variables::context_stack.size();
}

void Variables::pop() {
	Variables::context_stack.pop();
}

BaseValue* Variables::get(string name) {
	auto it = Variables::var_record.find(name);
	if (it != Variables::var_record.end()) {
		return it->second.value;
	}

	throw "Uncaught ReferenceError: variable is not defined";
}

BaseValue* Variables::get_local(string name) {
	auto it = this->local_var_record.find(name);
	if (it != this->local_var_record.end()) {
		return it->second.value;
	}

	throw "Uncaught ReferenceError: variable is not defined";
}

void Variables::set(string name, BaseValue* data, bool is_const) {
	auto it = Variables::var_record.find(name);
	if (it != Variables::var_record.end()) {
		if (it->second.is_const == true) throw "Uncaught TypeError: Assignment to constant variable.";
	}

	Variables::var_record[name] = { data, is_const };
}

void Variables::set_local(string name, BaseValue* data, bool is_const) {
	auto it = this->local_var_record.find(name);
	if (it != this->local_var_record.end()) {
		if (it->second.is_const == true) throw "Uncaught TypeError: Assignment to constant variable.";
	}

	this->local_var_record[name] = { data, is_const };
}
