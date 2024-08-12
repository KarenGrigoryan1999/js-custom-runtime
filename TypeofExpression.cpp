#include "iostream"
#include "TypeofExpression.h"
#include "Token.h"
#include "Expression.h"
#include "StringType.h"
#include "ReferenceError.h"

using namespace std;

TypeofExpression::TypeofExpression(Expression* exp) {
	this->exp = exp;
}

BaseValue* TypeofExpression::eval() {
	try {
		BaseValue* val = exp->eval();
		variable_t type = val->get_type();

		if (type == UNDEFINED_TYPE) {
			return new StringType("undefined");
		}
		if (type == STRING_TYPE) {
			return new StringType("string");
		}
		if (type == NULL_TYPE || type == OBJECT_TYPE) {
			return new StringType("object");
		}
		if (type == FUNCTION_TYPE) {
			return new StringType("function");
		}
		if (type == BOOL_TYPE) {
			return new StringType("boolean");
		}
		if (type == NUMBER_TYPE || type == NAN_TYPE) {
			return new StringType("number");
		}
	}
	catch (BaseException* err) {
		if(strcmp(err->plain_name, "ReferenceError")) return new StringType("undefined");//TODO нужно переписать исключения чтобы все работало нормально
		throw err;
	}
}