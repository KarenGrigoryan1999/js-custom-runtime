#include "FunctionExpression.h"
#include "string"
#include "Token.h"
#include "Functions.h"

using namespace std;

FunctionExpression::FunctionExpression(string name) {
	this->name = name;
}

void FunctionExpression::add(Expression* exp) {
	this->args.push_back(exp);
}

BaseValue* FunctionExpression::eval() {
	return Functions::get(this->name, &this->args);
}