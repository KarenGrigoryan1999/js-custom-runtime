#ifndef OBJECT_EXPRESSION_H
#define OBJECT_EXPRESSION_H

#include <vector>
#include <iostream>
#include "string"
#include "ObjectBase.h"
#include "BaseValue.h"
#include "ObjectProperty.h"
#include "NullType.h"
#include "UndefinedType.h"
#include "Token.h"
#include "NumberType.h"
#include "BoolType.h"
#include "EmptyExpression.h"
#include "GarbigeCollector.h"
#include "HiddenProperties.h"

using namespace std;

class ObjectExpression : public CollectableEntity, public ObjectBase
{
public:
	ObjectExpression(bool has_null_proto);
	ObjectExpression();
	void add_property(string property_name, Expression* exp);
	void add_property(string property_name, object_property property);
	BaseValue* eval() override;
	BaseValue* get_property_value(string name);
	vector<string>* get_keys();
	BaseValue* set_property_value(string name, Expression* exp);
	BaseValue* set_property_value(string name, BaseValue* val);
	BaseValue* set_property_with_descriptors(string name, object_property* props);
	BaseValue* set_hidden_property(HiddenProperties property, Expression* value);
	BaseValue* get_hidden_property(HiddenProperties property);
	int get_data_size() override;
	void trace() override;
	void set_object_proto(bool has_null_proto);
	int get_entity_type() override;
	vector<object_property>* get_obj_properties();
	const char* plain_name = "ObjectExpression";
private:
	vector<object_property> properties;
	vector<string> key_names;

	//Скрытые ключи объектов
	BaseValue* primitive_value;
};

#endif
