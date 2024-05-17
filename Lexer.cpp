#include <iostream>
#include <vector>
#include <cctype>

#include "Lexer.h"
#include "TokenType.h"

using namespace std;

Lexer::Lexer(string code) {
	this->code = code;
	this->token_list = {};
	pos = 0;
	symbol = code[0];
}

vector<Token>* Lexer::tokenize() {
	while (pos < code.size()) {
		
		if (symbol == '+') {
			this->tokenize_plus_operator();
		}
		else if (symbol == '-') {
			this->tokenize_minus_operator();
		}
		else if (symbol == '!') {
			this->tokenize_inverse_operator();
		}
		else if (symbol == '/') {
			this->tokenize_slash_symbol();
		}
		else if (symbol == '*') {
			this->tokenize_math_operator(token_t::STAR);
		}
		else if (symbol == ',') {
			this->tokenize_math_operator(token_t::COMMA);
		}
		else if (symbol == '(') {
			this->tokenize_math_operator(token_t::L_BRACKET);
		}
		else if (symbol == ')') {
			this->tokenize_math_operator(token_t::R_BRACKET);
		}
		else if (symbol == ';') {
			this->tokenize_math_operator(token_t::SEMICOLON);
		}
		else if (symbol == '{') {
			this->tokenize_math_operator(token_t::L_BLOCK);
		}
		else if (symbol == ':') {
			this->tokenize_math_operator(token_t::COLON);
		}
		else if (symbol == '[') {
			this->tokenize_math_operator(token_t::SQ_BRACKET_L);
		}
		else if (symbol == ']') {
			this->tokenize_math_operator(token_t::SQ_BRACKET_R);
		}
		else if (symbol == '}') {
			this->tokenize_math_operator(token_t::R_BLOCK);
		}
		else if (symbol == '.') {
			this->tokenize_math_operator(token_t::DOT_OP);
		}
		else if (symbol == '=') {
			this->equal_operator();
		}
		else if (symbol == '<') {
			this->tokenize_relative_operator(LT);
		}
		else if (symbol == '>') {
			this->tokenize_relative_operator(GT);
		}
		else if (symbol == '&') {
			this->tokenize_amp_operator();
		}
		else if (symbol == '|') {
			this->tokenize_or_operator();
		}
		else if (symbol == '\'' || symbol == '\"') {
			this->tokenize_plain_text(symbol);
		}
		else if(std::isdigit(symbol)) {
			this->tokenize_numeric(token_t::NUMBER);
		}
		else if (isalpha(symbol) || symbol == '_') {
			this->tokenize_word(token_t::ONE_WORD);
		}
		else {
			this->next();
		}
	}

	return &this->token_list;
}

void Lexer::next() {
	this->pos += 1;
	symbol = this->peek();
}

char Lexer::peek() {
	if (pos < code.size()) {
		return code[pos];
	}
	else {
		return '\0';
	}
}

void Lexer::tokenize_inverse_operator() {
	this->next();
	if (symbol == '=') {
		this->next();
		if (symbol == '=') {
			this->next();
			this->base_tokenize(token_t::NOT_EQ_STRICT_CHECKING);
		}
		else {
			this->base_tokenize(token_t::NOT_EQ_CHECKING);
		}
	} else
	this->base_tokenize(token_t::INVERSE);
}

void Lexer::tokenize_bracket_operator(token_t type) {
	this->base_tokenize(type);
	this->next();
}

void Lexer::tokenize_plus_operator() {
	this->next();
	while(symbol == ' ')this->next();
	if (symbol == '+') {
		this->base_tokenize(token_t::INCREMENT);
		this->next();
	} else
	this->base_tokenize(token_t::PLUS);
}

void Lexer::tokenize_minus_operator() {
	this->next();
	while (symbol == ' ')this->next();
	if (symbol == '-') {
		this->base_tokenize(token_t::DECREMENT);
		this->next();
	}
	else
		this->base_tokenize(token_t::MINUS);
}

void Lexer::tokenize_slash_symbol() {
	this->tokenize_temp += symbol;
	this->next();
	this->tokenize_temp += symbol;
	this->next();
	if (this->tokenize_temp == "//") {
		while (symbol != '\n') {
			this->tokenize_temp += symbol;
			this->next();
		}
		this->base_tokenize(SIMPLE_COMMENT);
	}
	else if (this->tokenize_temp == "/*") {
		this->next();
		this->next();
		while (symbol != '/' || code[pos-1] != '*') {
			this->tokenize_temp += symbol;
			this->next();
		}
		this->next();
		this->base_tokenize(MULTILINE_COMMENT);
	}
	else {
		this->tokenize_temp = "/";
		this->base_tokenize(DIV);
	}
	this->tokenize_temp = "";
}

void Lexer::tokenize_relative_operator(token_t type) {
	this->tokenize_temp += symbol;
	this->next();
	this->tokenize_temp += symbol;
	this->next();
	if ((this->tokenize_temp == ">=" && type == GT) || (this->tokenize_temp == "<=" && type == LT)) {
		this->base_tokenize(type == GT ? GTE : LTE);
		this->next();
	}
	else {
		this->base_tokenize(type);
	}
	this->tokenize_temp = "";
}

void Lexer::tokenize_amp_operator() {
	this->tokenize_temp += symbol;
	this->next();
	this->tokenize_temp += symbol;
	this->next();
	if (this->tokenize_temp == "&&") {
		this->base_tokenize(LOGICAL_AND_EXPRESSION);
		this->next();
	} else {
		this->base_tokenize(LOGICAL_AND_EXPRESSION);
	}
	this->tokenize_temp = "";
}

void Lexer::tokenize_or_operator() {
	this->tokenize_temp += symbol;
	this->next();
	this->tokenize_temp += symbol;
	this->next();
	if (this->tokenize_temp == "||") {
		this->base_tokenize(BITWISE_OR_EXPRESSION);
		this->next();
	}
	else {
		this->base_tokenize(BITWISE_OR_EXPRESSION);
	}
	this->tokenize_temp = "";
}

void Lexer::tokenize_math_operator(token_t type) {
	this->base_tokenize(type);
	this->next();
}

void Lexer::equal_operator() {
	while (symbol == '=') {
		this->tokenize_temp += symbol;
		this->next();
	}

	if (this->tokenize_temp.size() == 1) {
		this->base_tokenize(token_t::EQUAL);
	}
	if (this->tokenize_temp.size() == 2) {
		this->base_tokenize(token_t::EQ_CHECKING);
	}
	if (this->tokenize_temp.size() == 3) {
		this->base_tokenize(token_t::EQ_STRICT_CHECKING);
	}
	this->tokenize_temp = "";
}

void Lexer::tokenize_plain_text(char quotation_symbol) {
	this->next();
	while (symbol != quotation_symbol) {
		if (this->pos >= code.size() || symbol == '\n') {
			throw "Uncaught SyntaxError: Invalid or unexpected token";
		}
		this->tokenize_temp += symbol;
		this->next();
	}
	this->next();
	this->base_tokenize(PLAIN_TEXT);
	this->tokenize_temp = "";

}

void Lexer::tokenize_word(token_t type) {
	while (std::isdigit(symbol) || isalpha(symbol) || symbol == '_') {
		this->tokenize_temp += symbol;
		this->next();
	}
	if (this->tokenize_temp == "if") {
		while (symbol == ' ') this->next();
		if (symbol == '(') this->base_tokenize(IF_STATEMENT);
		else throw "unexpected token";
	}
	else if (this->tokenize_temp == "for") {
		while (symbol == ' ') this->next();
		if (symbol == '(') this->base_tokenize(FOR_STATEMENT);
		else throw "unexpected token";
	}
	else if (this->tokenize_temp == "else") {
		this->tokenize_math_operator(ELSE_STATEMENT);
	}
	else if (this->tokenize_temp == "NaN") {
		this->base_tokenize(NAN_EXPRESSION);
	}
	else if (this->tokenize_temp == "function") {
		this->base_tokenize(FUNCTION);
	}
	else if (this->tokenize_temp == "undefined") {
		this->tokenize_math_operator(UNDEFINED_EXPRESSION);
	}
	else if (this->tokenize_temp == "null") {
		this->tokenize_math_operator(NULL_EXPRESSION);
	}
	else if (this->tokenize_temp == "this") {
		this->base_tokenize(THIS_KEYWORD);
	}
	else if (this->tokenize_temp == "new") {
		this->base_tokenize(NEW_OPERATOR);
	}
	else if (this->tokenize_temp == "return") {
		this->tokenize_math_operator(RETURN);
	}
	else if (this->tokenize_temp == "kus") {
		this->tokenize_math_operator(KUS);
	}
	else if (this->tokenize_temp == "true" || this->tokenize_temp == "false") {
		this->base_tokenize(BOOLEAN_ELEMENT);
	}
	else {
		this->base_tokenize(type);
	}
	this->tokenize_temp = "";
}

void Lexer::tokenize_numeric(token_t type) {
	bool was_point_added = false;
	while (std::isdigit(symbol) || symbol == '.') {
		if (symbol == '.') {
			if (was_point_added == true) throw "error";
			was_point_added = true;
		}
		this->tokenize_temp += symbol;
		this->next();
	}
	this->base_tokenize(type);
	this->tokenize_temp = "";
}

void Lexer::base_tokenize(token_t type) {
	Token token(type, this->tokenize_temp);
	token_list.push_back(token);
}
