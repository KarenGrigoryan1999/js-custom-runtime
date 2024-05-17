#include "ExecutionContext.h"


using namespace std;

ExecutionContext::ExecutionContext() {}

void ExecutionContext::set_environment_record(Environment* env) {
	this->env = env;
}

Environment* ExecutionContext::get_environment_record() {
	return this->env;
}

void ExecutionContext::set_this_binding(BaseValue* obj) {
	this->this_binding = obj;
}

BaseValue* ExecutionContext::get_this_binding() {
	return this->this_binding;
}
