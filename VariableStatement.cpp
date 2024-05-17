#include "VariableStatement.h"
#include "Expression.h"
#include "Variables.h"
#include "ContextStack.h"
#include "TDZValue.h"

VariableStatement::VariableStatement(string name, Environment* block, Expression* exp, bool is_const, bool is_declaration) {
	this->name = name;
	this->exp = exp;
	this->is_const = is_const;
	this->is_declaration = is_declaration;
	this->block = block;

	if (is_declaration) {
		//���� � ��� ���������� ���������� ����������, �� �� ������ StaticSemantic ��� ���������� LexicalStatement ������ ��������� ��������, �� ��, ��� ���������� �� ���� ���������� ����� � �����
		bool was_declared = false;
		if (this->block != NULL) {
			try {
				BaseValue* val = this->block->records->get_local(name);
				was_declared = true;
			} catch(string e) {}
		}

		if (was_declared) {
			throw string("Uncaught SyntaxError: Identifier ") + name + string(" has already been declared");
		}
	}
	if (this->block == NULL)
		Variables::set(name, new TDZValue(), is_const);
	else
	this->block->records->set_local(name, new TDZValue(), is_const);//TDZ - Temporary Dead Zone - ���� ���������� �� ����������, ����� ����� �� ����������� ���� ���������� - ��� ������� ����
}

BaseValue* VariableStatement::eval() {
	BaseValue* evaluated_data = this->exp->eval();
	if (block != NULL) {
		if(block->records != NULL) {
			try {
				block->records->get_local(this->name);
			}
			catch (string error_message) {
				block->records->set_local(this->name, evaluated_data, this->is_const);
				return evaluated_data;
			}
		}
	}
	else {
		Variables::set(this->name, evaluated_data, this->is_const);
		return evaluated_data;
	}
	return evaluated_data;
}