#ifndef ANONUMOUS_FUNC_EXPRESSION_H
#define ANONUMOUS_FUNC_EXPRESSION_H

#include <vector>
#include "string"
#include "Expression.h"
#include "Node.h"
#include "Environment.h"
#include "FunctionBodyStatement.h"
#include "ObjectExpression.h"

using namespace std;

class AnonumousFuncExpression : public ObjectExpression
{
public:
	AnonumousFuncExpression(Environment* block);
	void add(string arg);
	void setBody(FunctionBodyStatement* body);
	FunctionBodyStatement* getBody();
	BaseValue* eval() override;
	vector<string>* get_arg_list();
	Environment* getBlock();
	void setBlock(Environment* env);
	const char* plain_name = "AnonumousFuncExpression";
private:
	bool is_struct;
	string name;
	FunctionBodyStatement* body;
	vector<string> args;
	Environment* block;
};

#endif
