#ifndef OBJECT_EXPRESSION_H
#define OBJECT_EXPRESSION_H

#include <vector>
#include "string"
#include "ObjectBase.h"
#include "BaseValue.h"
#include "ObjectProperty.h"

using namespace std;

class ObjectExpression : public ObjectBase
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
	void set_object_proto(bool has_null_proto);
private:
	vector<object_property> properties;
	vector<string> key_names;
};

#endif