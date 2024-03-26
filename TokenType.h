#pragma once
typedef enum
{
	PLUS,//+
	INCREMENT,//++
	DECREMENT,//--
	MINUS,
	STAR,
	DIV,
	NUMBER,
	NAN_EXPRESSION,
	UNDEFINED_EXPRESSION,
	ONE_WORD,
	PLAIN_TEXT,
	BOOLEAN_ELEMENT,
	EQUAL,
	KUS,
	L_BRACKET,
	R_BRACKET,
	COMMA,
	SEMICOLON,
	FOR_STATEMENT,
	L_BLOCK,
	R_BLOCK,
	FUNCTION,
	RETURN,

	//Logical
	IF_STATEMENT,
	ELSE_STATEMENT,
	LT,
	GT,
	NOT_EQ_CHECKING,
	EQ_CHECKING,
	NOT_EQ_STRICT_CHECKING,
	EQ_STRICT_CHECKING,
	INVERSE, //!
	LTE,
	GTE,
	AND_OP,
	OR_OP,
	//Comments
	SIMPLE_COMMENT,
	MULTILINE_COMMENT,

	CODE_EOF
} token_t;