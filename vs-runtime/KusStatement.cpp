#include "iostream"
#include "KusStatement.h"
#include "Token.h"
#include "Expression.h"

using namespace std;

KusStatement::KusStatement(Expression* exp) {
	this->exp = exp;
}

BaseValue* KusStatement::eval() {
	cout << exp->eval()->get_as_string() << endl;
	return 0;
}