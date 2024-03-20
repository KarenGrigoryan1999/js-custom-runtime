#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "string"
#include "Token.h"
#include "Node.h"
#include "Expression.h"
#include "BlockStatement.h"

using namespace std;

class Parser
{
public:
	Parser(vector<Token>* lexems);
	vector<Token>* lexems;
	Token* get(int position);
	bool match(token_t token_type);
	int pos;
	Node* parse();
	Expression* additive();
	Expression* logical();
	Expression* andLogical();
	Expression* orLogical();
	Expression* complexity();
	Expression* function_expression();
	Node* evaluate_statement();
	Node* kus_statement();
	Node* variable_statement();
	Node* if_else_statement();
	Node* for_statement();
	Node* block_statement();
	Expression* evaluate_expression();
	Expression* unary();
	Expression* primary();

	Expression* increment_expression();

	static void set_current_block(BlockStatement* block);
private:
	static BlockStatement* current_block;
};

#endif
