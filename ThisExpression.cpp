#include "ThisExpression.h"
#include "string"
#include "Token.h"
#include "ContextStack.h"

using namespace std;

ThisExpression::ThisExpression() {}

BaseValue* ThisExpression::eval() {
	ExecutionContext* context = ContextStack::top();
	if (context) {
		return context->get_this_binding();
	}
	return Variables::get("global");
}