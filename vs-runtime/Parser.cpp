#include "string"
#include <iostream>
#include <vector>
#include "Parser.h"
#include "TokenType.h"
#include "NumberExpression.h"
#include "BinaryExpression.h"
#include "LogicalExpression.h"
#include "UnaryExpression.h"
#include "VariableExpression.h"
#include "VariableStatement.h"
#include "ForStatement.h"
#include "IfStatement.h"
#include "KusStatement.h"
#include "StringExpression.h"
#include "BooleanExpression.h"
#include "BlockStatement.h"
#include "IncrementExpression.h"
#include "FunctionExpression.h"

using namespace std;

BlockStatement* Parser::current_block = NULL;

Parser::Parser(vector<Token>* lexems) {
	this->lexems = lexems;
	Token token(CODE_EOF, "");
	this->lexems->push_back(token);
	this->pos = 0;
}

Node* Parser::parse() {
	BlockStatement* statement = new BlockStatement(Parser::current_block);

	while (!this->match(CODE_EOF)) {
		statement->add(this->evaluate_statement());
	}

	return statement;
}

Node* Parser::block_statement() {
	if (this->match(L_BLOCK)) {
		BlockStatement* statement = new BlockStatement(Parser::current_block);
		Parser::current_block = statement;

		while (!this->match(R_BLOCK)) {
			statement->add(this->block_statement());
		}

		Parser::set_current_block(Parser::current_block->prev);

		return statement;
	}

	return this->kus_statement();
}

Node* Parser::evaluate_statement() {
	return this->block_statement();
}

Node* Parser::kus_statement() {
	if (this->match(KUS)) {
		Expression* result = this->evaluate_expression();
		return new KusStatement(result);
	}
	if (this->match(IF_STATEMENT))
		return this->if_else_statement();
	else if (this->match(FOR_STATEMENT))
		return this->for_statement();
	else this->variable_statement();
}

Node* Parser::variable_statement() {
	bool is_const = false;
	if (this->get(0)->type == ONE_WORD && (this->get(0)->value == "const")) {
		is_const = true;
		this->match(ONE_WORD);
	}
	if (this->get(0)->value == "let") {
		this->match(ONE_WORD);//Временно пропускаем ключевые слова const и let
	}
	if (this->get(0)->type == ONE_WORD && this->get(1)->type == EQUAL) {
		string var_name = this->get(0)->value;
		this->match(ONE_WORD);
		this->match(EQUAL);
		return new VariableStatement(var_name, is_const, Parser::current_block, this->evaluate_expression());
	}
	return this->evaluate_expression();
}

Node* Parser::if_else_statement() {
	Expression* condition = this->evaluate_expression();
	Node* if_statement = this->evaluate_statement();
	Node* else_statement = NULL;
	if (this->match(ELSE_STATEMENT)) {
		else_statement = this->evaluate_statement();
	}

	return new IfStatement(condition, if_statement, else_statement);
}

Node* Parser::for_statement() {
	this->match(L_BRACKET);
	Node* from = this->evaluate_statement();
	this->match(SEMICOLON);
	Node* to = this->evaluate_statement();
	this->match(SEMICOLON);
	Node* action = this->evaluate_statement();
	this->match(R_BRACKET);
	Node* iterated_act = this->evaluate_statement();

	return new ForStatement(from, to, action, iterated_act);
}

Expression* Parser::evaluate_expression() {
	return this->orLogical();
}

Expression* Parser::orLogical() {
	Expression* first = this->andLogical();
	while (true) {
		if (this->match(AND_OP)) {
			first = new LogicalExpression(AND_OP, first, this->andLogical());
			continue;
		}
		break;
	}

	return first;
}

Expression* Parser::andLogical() {
	Expression* first = this->logical();
	while (true) {
		if (this->match(OR_OP)) {
			first = new LogicalExpression(OR_OP, first, this->logical());
			continue;
		}
		break;
	}

	return first;
}

Expression* Parser::logical() {
	Expression* first = this->additive();

	while (true) {
		if (this->match(NOT_EQ_CHECKING)) {
			first = new LogicalExpression(NOT_EQ_CHECKING, first, this->additive());
			continue;
		}
		if (this->match(NOT_EQ_STRICT_CHECKING)) {
			first = new LogicalExpression(NOT_EQ_STRICT_CHECKING, first, this->additive());
			continue;
		}
		if (this->match(EQ_CHECKING)) {
			first = new LogicalExpression(EQ_CHECKING, first, this->additive());
			continue;
		}
		if (this->match(EQ_STRICT_CHECKING)) {
			first = new LogicalExpression(EQ_STRICT_CHECKING, first, this->additive());
			continue;
		}
		if (this->match(LT)) {
			first = new LogicalExpression(LT, first, this->additive());
			continue;
		}
		if (this->match(GT)) {
			first = new LogicalExpression(GT, first, this->additive());
			continue;
		}
		if (this->match(GTE)) {
			first = new LogicalExpression(GTE, first, this->additive());
			continue;
		}
		if (this->match(LTE)) {
			first = new LogicalExpression(LTE, first, this->additive());
			continue;
		}
		break;
	}

	return first;
}

Expression* Parser::additive() {
	Expression* first = this->complexity();

	while (true) {
		if (this->match(PLUS)) {
			first = new BinaryExpression(PLUS, first, this->complexity());
			continue;
		}
		if (this->match(MINUS)) {
			first = new BinaryExpression(MINUS, first, this->complexity());
			continue;
		}
		break;
	}

	return first;
}

Expression* Parser::complexity() {
	Expression* first = this->increment_expression();

	while (true) {
		if (this->match(STAR)) {
			first = new BinaryExpression(STAR, first, this->increment_expression());
			continue;
		}
		if (this->match(DIV)) {
			first = new BinaryExpression(DIV, first, this->increment_expression());
			continue;
		}
		break;
	}

	return first;
}

Expression* Parser::function_expression() {
	FunctionExpression* func = new FunctionExpression(this->get(0)->value);
	this->match(ONE_WORD);
	this->match(L_BRACKET);

	while (!this->match(R_BRACKET)) {
		this->match(COMMA);
		func->add(this->evaluate_expression());
	}

	return func;
}

Expression* Parser::increment_expression() {
	Expression* result = NULL;
	token_t next_token_type = this->get(1)->type;
	if (this->get(0)->type == ONE_WORD && (next_token_type == INCREMENT || next_token_type == DECREMENT)) {
		result = new IncrementExpression('r', next_token_type, this->unary(), this->get(0)->value, Parser::current_block);
		this->match(this->get(0)->type);
	}

	if (result == NULL) return this->unary();

	return result;
}

Expression* Parser::unary() {
	if (this->match(MINUS)) {
		return new UnaryExpression(MINUS, this->primary());
	}
	if (this->match(PLUS)) {
		return new UnaryExpression(PLUS, this->primary());
	}
	if (this->match(INVERSE)) {
		return new UnaryExpression(INVERSE, this->primary());
	}

	return this->primary();
}

Expression* Parser::primary() {
	Token* current = this->get(0);
	if (this->match(NUMBER)) {
		NumberExpression* exp = new NumberExpression(current->value);
		return exp;
	}
	if (this->match(PLAIN_TEXT)) {
		StringExpression* exp = new StringExpression(current->value);
		return exp;
	}
	if (current->type == ONE_WORD && this->get(1)->type == L_BRACKET) {
		return this->function_expression();
	}
	if (this->match(ONE_WORD)) {
		VariableExpression* exp = new VariableExpression(current->value, Parser::current_block);
		return exp;
	}
	if (this->match(L_BRACKET)) {
		Expression* result = this->evaluate_expression();
		if (this->match(R_BRACKET)) return result;
	}
	if (this->match(BOOLEAN_ELEMENT)) {
		BooleanExpression* exp = new BooleanExpression(current->value);
		return exp;
	}
	if (this->match(INCREMENT)) {
		return new IncrementExpression('l', INCREMENT, this->unary(), this->get(0)->value, Parser::current_block);
	}
	if (this->match(DECREMENT)) {
		return new IncrementExpression('l', DECREMENT, this->unary(), this->get(0)->value, Parser::current_block);
	}
	if (this->match(SIMPLE_COMMENT) || this->match(MULTILINE_COMMENT) || this->match(SEMICOLON)) {
		NumberExpression* exp = new NumberExpression("");//Временное решение чтобы пропустить все комментарии
		return exp;
	}

	throw "Unknown token exception";
}

bool Parser::match(token_t token_type) {
	Token* t = this->get(0);
	if (t->type != token_type) return false;
	this->pos += 1;
	return true;
}

Token* Parser::get(int position) {
	return &this->lexems->at(position+pos);
}

void Parser::set_current_block(BlockStatement* block){
	Parser::current_block = block;
}