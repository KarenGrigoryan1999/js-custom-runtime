#include "ObjectExpression.h"
#include "CallExpression.h"

using namespace std;

ObjectExpression::ObjectExpression(bool has_null_proto) {
	this->set_object_proto(has_null_proto);
}

ObjectExpression::ObjectExpression() {
	this->set_object_proto(true);
}

void ObjectExpression::add_property(string property_name, Expression* exp) {
	this->properties.push_back({
		exp->eval(),
		PropertyDescriptorState::TURNED_ON,
		PropertyDescriptorState::TURNED_ON,
		PropertyDescriptorState::TURNED_ON
	});
	this->key_names.push_back(property_name);
}

BaseValue* ObjectExpression::set_hidden_property(HiddenProperties property, Expression* value) {
	switch (property)
	{
	case HiddenProperties::PrimitiveValue:
		return this->primitive_value = value->eval();
	default:
		return this->primitive_value = value->eval();
	}
}

BaseValue* ObjectExpression::get_hidden_property(HiddenProperties property) {
	switch (property)
	{
	case HiddenProperties::PrimitiveValue:
		return this->primitive_value;
		break;
	default:
		return this->primitive_value;
	}
}

void ObjectExpression::add_property(string property_name, object_property property) {
	this->properties.push_back(property);
	this->key_names.push_back(property_name);
}

int ObjectExpression::get_data_size() {
	return sizeof(this->key_names) + sizeof(this->properties);
}

void ObjectExpression::trace() {
	GarbigeCollector::findAndMark(this);
}

vector<string>* ObjectExpression::get_keys() {
	return &this->key_names;
}

BaseValue* ObjectExpression::get_property_value(string name) {
	ObjectExpression* current = this;
	
	while (current != NULL) {
		for (int i = 0; i < current->key_names.size(); i++) {
			if (name == current->key_names.at(i)) {
				object_property property = current->properties.at(i);
				//Сначала проверяем: есть ли геттер?
				if (property.get != NULL) {
					CallExpression* getter_caller = new CallExpression(property.get->get_ref(), NULL);
					getter_caller->set_this_object(current);
					return getter_caller->eval();
				}
				//Если нет, то возвращаем свойство
				return current->properties.at(i).value;
			}
		}

		BaseValue* proto = current->get_property_value("__proto__");
		variable_t var_type = proto->get_type();
		if (var_type == OBJECT_TYPE || var_type == FUNCTION_TYPE) {
			current = proto->get_ref();
		}
		else {
			current = NULL;
		}
	}

	return new UndefinedType();
}

BaseValue* ObjectExpression::set_property_with_descriptors(string name, object_property* props) {
	bool is_exist = false;
	for (int i = 0; i < this->key_names.size(); i++) {
		if (name == this->key_names.at(i)) {
			object_property* property = &this->properties.at(i);
			is_exist = true;
			if (property->configurable != PropertyDescriptorState::TURNED_OFF) {
				if (props->writable != PropertyDescriptorState::UNSET) property->writable = props->writable;
				if (props->configurable != PropertyDescriptorState::UNSET) property->configurable = props->configurable;
				if (props->enumerable != PropertyDescriptorState::UNSET) property->enumerable = props->enumerable;
				if (props->get != NULL) property->get = props->get;
				if (props->set != NULL) property->set = props->set;
				if (props->value != NULL) property->value = props->value;
			}
		}
	}

	if (!is_exist) {
		this->properties.push_back(*props);
		this->key_names.push_back(name);
	}

	return props->value;
}

BaseValue* ObjectExpression::set_property_value(string name, BaseValue* val) {
	bool is_exist = false;

	for (int i = 0; i < this->key_names.size(); i++) {
		if (name == this->key_names.at(i)) {
			object_property* property = &this->properties.at(i);
			is_exist = true;
			//Проверяю, есть ли сеттер
			if (property->set != NULL) {
				CallExpression* setter_caller = new CallExpression(property->set->get_ref(), NULL);
				setter_caller->add(new EmptyExpression(val));
				setter_caller->set_this_object(this);
				property->value = setter_caller->eval();
			}
			else if (property->writable == PropertyDescriptorState::TURNED_ON) {
				//Если сеттера нет, то просто устанавливает значение
				property->value = val;
			}
		}
	}

	if (!is_exist) {
		this->properties.push_back({ val, PropertyDescriptorState::TURNED_ON, PropertyDescriptorState::TURNED_ON, PropertyDescriptorState::TURNED_ON });
		this->key_names.push_back(name);
	}

	return val;
}

BaseValue* ObjectExpression::set_property_value(string name, Expression* exp) {
	BaseValue* val = exp->eval();
	return this->set_property_value(name, val);
}

vector<object_property>* ObjectExpression::get_obj_properties() {
	return &this->properties;
}

int ObjectExpression::get_entity_type() {
	return 3;
}

BaseValue* ObjectExpression::eval() {
	return new BaseValue(this, OBJECT_TYPE);
}

void ObjectExpression::set_object_proto(bool has_null_proto) {
	//Если has_null_proto = true, то мы выставляем __proto__ как null
	this->properties.push_back({
	has_null_proto ? new NullType() : Variables::get("Object")->get_ref()->get_property_value("prototype"),
	PropertyDescriptorState::TURNED_ON,
	PropertyDescriptorState::TURNED_ON,
	PropertyDescriptorState::TURNED_ON
		});
	this->key_names.push_back("__proto__");
}