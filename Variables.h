#ifndef VARIABLES_H
#define VARIABLES_H

#include <map>
#include <string>
#include <stack>
#include "BaseValue.h"

using namespace std;

class Variables
{
public:
	struct var_t {
		BaseValue* value;
		bool is_const;
	};
	map<string, var_t> identifiers;
	static map<string, var_t> global_identifiers;
	BaseValue* get_local(string name);
	static BaseValue* get(string name);
	void set_local(string name, BaseValue* data, bool is_const);
	static void set(string name, BaseValue* data, bool is_const);
	static void setupDefaultPrototypes();
};

#endif
