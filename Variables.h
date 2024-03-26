#ifndef VARIABLES_H
#define VARIABLES_H

#include <map>
#include <string>
#include <stack>
#include "BaseValue.h"

#define MAXIMUM_CALLSTACK 100

using namespace std;

class Variables
{
public:
	struct var_t {
		BaseValue* value;
		bool is_const;
	};
	map<string, var_t> local_var_record;
	static map<string, var_t> var_record;
	BaseValue* get_local(string name);
	static BaseValue* get(string name);
	static stack<Variables*> context_stack;
	static void push(Variables* env);
	static Variables* top();
	static void pop();
	static int size();
	void set_local(string name, BaseValue* data, bool is_const);
	static void set(string name, BaseValue* data, bool is_const);
};

#endif
