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
#include "NanExpression.h"
#include "UndefinedExpression.h"
#include "VariableStatement.h"
#include "ForStatement.h"
#include "IfStatement.h"
#include "KusStatement.h"
#include "StringExpression.h"
#include "BooleanExpression.h"
#include "BlockStatement.h"
#include "IncrementExpression.h"
#include "CallExpression.h"
#include "FunctionDeclaration.h"
#include "ReturnExpression.h"
#include "Environment.h"
#include "BlockStatement.h"
#include "FunctionBodyStatement.h"
#include "ObjectExpression.h"
#include "DotExpression.h"
#include "NumberType.h"
#include "ThisExpression.h"
#include "NewExpression.h"
#include "NullExpression.h"

using namespace std;

Environment* Parser::current_block = NULL;

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
	if (this->match(L_BLOCK) && this->get(1)->type != COLON) {
		BlockStatement* statement = new BlockStatement(Parser::current_block);
		Parser::current_block = statement->env;

		while (!this->match(R_BLOCK)) {
			statement->add(this->block_statement());
		}

		Parser::set_current_block(Parser::current_block->outer);

		return statement;
	}

	return this->kus_statement();
}

FunctionBodyStatement* Parser::func_body_statement() {
	if (this->match(L_BLOCK) && this->get(1)->type != COLON) {
		FunctionBodyStatement* statement = new FunctionBodyStatement(Parser::current_block);
		Parser::current_block = statement->env;

		while (!this->match(R_BLOCK)) {
			statement->add(this->block_statement());
		}

		Parser::set_current_block(Parser::current_block->outer);

		return statement;
	}

	throw "error";
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
	if (this->match(RETURN))
		return new ReturnExpression(this->evaluate_expression());
	else if (this->match(FOR_STATEMENT))
		return this->for_statement();
	else this->variable_statement();
}

Node* Parser::variable_statement() {
	bool is_const = false;
	bool is_declaration = false;
	if (this->get(0)->type == ONE_WORD && (this->get(0)->value == "const")) {
		is_const = true;
		is_declaration = true;
		this->match(ONE_WORD);
	}
	if (this->get(0)->value == "let") {
		is_declaration = true;
		this->match(ONE_WORD);
	}
	if (this->get(0)->type == FUNCTION && this->get(1)->type == ONE_WORD) {
		string var_name = this->get(1)->value;
		this->match(FUNCTION);
		this->match(ONE_WORD);
		FunctionDeclaration* func = new FunctionDeclaration(var_name, Parser::current_block, is_const);

		int args_length = 0;

		this->match(L_BRACKET);

		while (!this->match(R_BRACKET))
		{
			func->function->add(this->get(0)->value);
			this->consume(ONE_WORD);
			this->match(COMMA);
			args_length += 1;
		}

		func->function->add_property("length", {
			new NumberType(args_length),
			PropertyDescriptorState::TURNED_ON,
			PropertyDescriptorState::TURNED_ON,
			PropertyDescriptorState::TURNED_ON
		});

		FunctionBodyStatement* block = this->func_body_statement();

		func->function->setBody(block);

		return func;
	}
	else if (this->get(0)->type == ONE_WORD && this->get(1)->type == EQUAL) {
		string var_name = this->get(0)->value;
		this->match(ONE_WORD);
		this->match(EQUAL);

		return new VariableStatement(var_name, Parser::current_block, (Expression*)this->variable_statement(), is_const, is_declaration);
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
	return this->object_expression();
}

Expression* Parser::object_expression() {
	if (this->match(L_BLOCK)) {
		ObjectExpression* object = new ObjectExpression(false);
		while (!this->match(R_BLOCK)) {
			string key = this->get(0)->value;
			this->match(ONE_WORD);
			this->match(COLON);
			object->add_property(key, this->evaluate_expression());
			this->match(COMMA);
		}

		return object;
	}

	return this->orLogical();
}

Expression* Parser::orLogical() {
	Expression* first = this->andLogical();
	while (true) {
		if (this->match(BITWISE_OR_EXPRESSION)) {
			first = new LogicalExpression(BITWISE_OR_EXPRESSION, first, this->andLogical());
			continue;
		}
		break;
	}

	return first;
}

Expression* Parser::andLogical() {
	Expression* first = this->logical();
	while (true) {
		if (this->match(LOGICAL_AND_EXPRESSION)) {
			first = new LogicalExpression(LOGICAL_AND_EXPRESSION, first, this->logical());
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
	Expression* first = this->new_expression();

	while (true) {
		if (this->match(STAR)) {
			first = new BinaryExpression(STAR, first, this->new_expression());
			continue;
		}
		if (this->match(DIV)) {
			first = new BinaryExpression(DIV, first, this->new_expression());
			continue;
		}
		break;
	}

	return first;
}

Expression* Parser::new_expression() {
	if (this->match(NEW_OPERATOR)) {
		return new NewExpression(this->increment_expression());
	}

	return this->increment_expression();
}

Expression* Parser::get_property_from_object(Expression* current) {
	Expression* prev_exp = NULL;
	while (true) {
		if (this->match(DOT_OP)) {
			prev_exp = current;
			current = new DotExpression(current, this->get(0)->value);
			this->match(ONE_WORD);
			continue;
		}
		break;
	}
	if (this->match(L_BRACKET)) {
		return this->method_expression(current, prev_exp);
	}
	if (this->match(EQUAL)) {
		//Если обнаруживаем знак равенства, то выполняем запись в property объекта
		((DotExpression*)current)->set_expression_to_write(this->evaluate_expression());
	}

	return current;
}

Expression* Parser::function_expression() {
	CallExpression* func = new CallExpression(this->get(0)->value, Parser::current_block);
	this->match(ONE_WORD);
	this->match(L_BRACKET);

	while (!this->match(R_BRACKET)) {
		this->match(COMMA);
		func->add(this->evaluate_expression());
	}

	return func;
}

Expression* Parser::method_expression(Expression* exp, Expression* obj_exp) {
	CallExpression* func = new CallExpression(exp, Parser::current_block);
	func->set_this_object(obj_exp);

	while (!this->match(R_BRACKET)) {
		this->match(COMMA);
		func->add(this->evaluate_expression());
	}

	return func;
}

Expression* Parser::increment_expression() {
	string token_type = this->get(0)->value;
	Expression* result = this->unary();
	if (this->match(INCREMENT) || this->match(DECREMENT)) {
		return new IncrementExpression('r', INCREMENT, result, token_type, Parser::current_block);
	}

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
	if (current->type == FUNCTION && this->get(1)->type == L_BRACKET) {
		this->match(FUNCTION);
		this->match(L_BRACKET);

		AnonumousFuncExpression* func = new AnonumousFuncExpression(Parser::current_block);
		
		int args_length = 0;

		while (!this->match(R_BRACKET))
		{
			func->add(this->get(0)->value);
			args_length += 1;
			this->consume(ONE_WORD);
			this->match(COMMA);
		}

		func->add_property("length", {
			new NumberType(args_length),
			PropertyDescriptorState::TURNED_ON,
			PropertyDescriptorState::TURNED_ON,
			PropertyDescriptorState::TURNED_ON
		});

		FunctionBodyStatement* block = this->func_body_statement();

		func->setBody(block);

		return func;
	}
	if (this->match(NAN_EXPRESSION)) {
		return new NanExpression();
	}
	if (this->match(THIS_KEYWORD)) {
		Expression* exp = new ThisExpression();
		if (this->get(0)->type != DOT_OP)
			return exp;
		else
			return this->get_property_from_object(exp);
	}
	if (this->match(UNDEFINED_EXPRESSION)) {
		return new UndefinedExpression();
	}
	if (this->match(NULL_EXPRESSION)) {
		return new NullExpression();
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
		if (this->get(0)->type != DOT_OP) {//Если после слова не стоит точка, то делаем вывод что мы имем дело с переменной
			return exp;
		}
		else {
			//Если после слова точка, то, вероятно мы достаем свойство из объекта
			return this->get_property_from_object(exp);
		}
	}
	if (this->match(L_BRACKET)) {
		Expression* result = this->evaluate_expression();
		if (this->match(R_BRACKET)) return result;
		else {
			throw string("Uncaught SyntaxError: missing ) after argument list");
		}
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

	throw string("Unknown token exception ") + current->value;
}

bool Parser::match(token_t token_type) {
	Token* t = this->get(0);
	if (t->type != token_type) return false;
	this->pos += 1;
	return true;
}

bool Parser::consume(token_t token_type) {
	Token* t = this->get(0);
	if (t->type != token_type) throw string("Uncaught token ") + t->value;
	this->pos += 1;
	return true;
}

Token* Parser::get(int position) {
	return &this->lexems->at(position+pos);
}

void Parser::set_current_block(Environment* block){
	Parser::current_block = block;
}