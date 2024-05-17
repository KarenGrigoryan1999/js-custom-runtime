#include "FunctionDeclaration.h"
#include "string"
#include "Token.h"
#include "Functions.h"

using namespace std;

FunctionDeclaration::FunctionDeclaration(string name, Environment* block, bool is_const) {
	//Код в конструкторе выполняется на фазе Static Semantic
	this->name = name;
	this->block = block;
	this->is_const = is_const;
	this->function = new AnonumousFuncExpression(block);

	//ClosureStatement. Выполняем инициализацию функции на стадии StaticSemantic
	BaseValue* function = new BaseValue(this->function);
	if (this->block == NULL) {
		Variables::set(this->name, function, this->is_const);
	}
	else {
		Environment* current = this->block->outer;

		if (current == NULL) {
			Variables::set(this->name, function, this->is_const);
		}
		else {
			current->records->set_local(this->name, function, this->is_const);
		}
	}
}

BaseValue* FunctionDeclaration::eval() {
	//метод eval вызывается на фазе Runtime Semantics
	return 0;
}