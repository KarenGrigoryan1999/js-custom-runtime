#ifndef EXECUTION_CONTEXT_H
#define EXECUTION_CONTEXT_H

#include "BaseValue.h"
#include "Environment.h"

using namespace std;

class ExecutionContext
{
public:
	ExecutionContext();
	void set_environment_record(Environment* env);
	Environment* get_environment_record();
	void set_this_binding(BaseValue* obj);
	BaseValue* get_this_binding();
private:
	Environment* env;
	BaseValue* this_binding;
};

#endif