#ifndef DEFINE_EXPRESSION_H
#define DEFINE_EXPRESSION_H

#include <vector>
#include "string"
#include "Expression.h"
#include "Node.h"
#include "BlockStatement.h"

using namespace std;

class DefineFunctionExpression : public Expression
{
public:
	DefineFunctionExpression(string name, BlockStatement* block, bool is_struct);
	void add(string arg);
	void setBody(BlockStatement* body);
	BlockStatement* getBody();
	BaseValue* eval() override;
	vector<string>* get_arg_list();
private:
	bool is_struct;
	string name;
	BlockStatement* body;
	vector<string> args;
	BlockStatement* block;
};

#endif