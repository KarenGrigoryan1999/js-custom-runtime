#include "ContextStack.h"
#include "string";
#include "ExecutionContext.h"
#include "BaseValue.h"

using namespace std;

std::stack<ExecutionContext*> ContextStack::context_stack;

void ContextStack::push(ExecutionContext* exec_context) {
	if (ContextStack::context_stack.size() > MAXIMUM_CALLSTACK) throw "Maximum call stack size exceeded";
	ContextStack::context_stack.push(exec_context);
}

ExecutionContext* ContextStack::top() {
	if (ContextStack::context_stack.size() == 0)
		return NULL;
	return ContextStack::context_stack.top();
}

int ContextStack::size() {
	return ContextStack::context_stack.size();
}

void ContextStack::pop() {
	ContextStack::context_stack.pop();
}
