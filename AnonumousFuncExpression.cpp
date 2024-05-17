#include "AnonumousFuncExpression.h"
#include "string"
#include "Token.h"
#include "Functions.h"
#include "FunctionBodyStatement.h"
#include "ObjectProperty.h"

using namespace std;

AnonumousFuncExpression::AnonumousFuncExpression(Environment* block) {
	this->block = block;

	ObjectExpression* obj = new ObjectExpression();
	this->add_property("prototype", {
		new BaseValue(obj),
		PropertyDescriptorState::TURNED_OFF,
		PropertyDescriptorState::TURNED_OFF,
		PropertyDescriptorState::TURNED_OFF
	});//Сразу задаем prototype, равный пустому объекту
}

void AnonumousFuncExpression::add(string arg) {
	this->args.push_back(arg);
}

vector<string>* AnonumousFuncExpression::get_arg_list() {
	return &this->args;
}

void AnonumousFuncExpression::setBody(FunctionBodyStatement* body) {
	this->body = body;
}

FunctionBodyStatement* AnonumousFuncExpression::getBody() {
	return this->body;
}

BaseValue* AnonumousFuncExpression::eval() {
	BaseValue* function = new BaseValue(this);
	
	return function;
}