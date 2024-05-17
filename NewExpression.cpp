#include "NewExpression.h"
#include "Token.h"
#include "NumberType.h"
#include "StringType.h"
#include "CallExpression.h"
#include "ObjectExpression.h"

using namespace std;

NewExpression::NewExpression(Expression* exp) {
	this->exp = exp;
}

BaseValue* NewExpression::eval() {
	ObjectExpression* obj = new ObjectExpression(false);//������� ����� ������
	BaseValue* evaluated_obj = obj->eval();
	CallExpression* construct_exp = (CallExpression*)this->exp;//����� �����������
	construct_exp->set_this_object(obj);//������ ��������� ������ ��� this
	construct_exp->eval();//��������� �����������
	evaluated_obj->get_ref()->set_property_value("__proto__", construct_exp->evaluated_function->get_property_value("prototype"));
	
	return evaluated_obj;
}