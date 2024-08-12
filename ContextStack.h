#ifndef CONTEXT_STACK_H
#define CONTEXT_STACK_H

#include <map>
#include <string>
#include <stack>
#include "BaseValue.h"
#include "Variables.h"
#include "ExecutionContext.h"

#define MAXIMUM_CALLSTACK 100

using namespace std;

class ContextStack
{
public:
	static stack<ExecutionContext*> context_stack;
	static void push(ExecutionContext* exec_context);
	static ExecutionContext* top();
	static void pop();
	static int size();
	static ExecutionContext* get_stack_element(int pos);
};

#endif
