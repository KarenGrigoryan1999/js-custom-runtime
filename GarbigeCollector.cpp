#include "GarbigeCollector.h"
#include <iostream>
#include "ObjectExpression.h"
#include "TDZValue.h"
#include "UndefinedType.h"
#include "BoolType.h"
#include "NullType.h"
#include "NumberType.h"

GarbigeCollector::GarbigeCollector() {}

int GarbigeCollector::heap_size = 0;
vector<GCItem> GarbigeCollector::collectableEntities;

void GarbigeCollector::init() {
	GarbigeCollector::heap_size = 0;
}

void GarbigeCollector::registerObj(CollectableEntity* entity) {
	GarbigeCollector::collectableEntities.push_back({entity, false});

	GarbigeCollector::heap_size += entity->get_data_size();

	if (GarbigeCollector::heap_size > MAX_HEAP_SIZE) {
		GarbigeCollector::startCollecting();
	}
}

void GarbigeCollector::findAndMark(CollectableEntity* entity) {
	for (auto it = GarbigeCollector::collectableEntities.begin(); it != GarbigeCollector::collectableEntities.end(); ++it)
	{
		if (it->entity == entity) {
			it->wasMarked = true;
		}
	}
}

void GarbigeCollector::removeColectedElements() {
	vector<int> elementsForRemoving;
	int i = 0;
	for (auto it = GarbigeCollector::collectableEntities.begin(); it != GarbigeCollector::collectableEntities.end(); ++it) {
		if (!it->wasMarked) {
			CollectableEntity* entity = it->entity;

			it->entity = nullptr;
			elementsForRemoving.push_back(i);
			GarbigeCollector::heap_size -= entity->get_data_size();

			if (entity->get_entity_type() == 1) {
				BaseValue* val = (BaseValue*)(entity);
				delete val;
			}
			else if (entity->get_entity_type() == 3) {
				ObjectExpression* val = (ObjectExpression*)(entity);
				delete val;
			}
			else if (entity->get_entity_type() == 4) {
				TDZValue* val = (TDZValue*)(entity);
				GarbigeCollector::heap_size -= val->get_data_size();
				delete val;
			}
			else if (entity->get_entity_type() == 5) {
				UndefinedType* val = (UndefinedType*)(entity);
				delete val;
			}
			else if (entity->get_entity_type() == 6) {
				BoolType* val = (BoolType*)(entity);
				delete val;
			}
			else if (entity->get_entity_type() == 7) {
				NullType* val = (NullType*)(entity);
				delete val;
			}
			else if (entity->get_entity_type() == 8) {
				NumberType* val = (NumberType*)(entity);
				delete val;
			}
		}
		else {
			it->wasMarked = false;
		}
		i++;
	}

	for (int i = elementsForRemoving.size() - 1; i >= 0; --i) {
		GarbigeCollector::collectableEntities.erase(GarbigeCollector::collectableEntities.begin() + elementsForRemoving.at(i));
	}
}

// Метод, который начинает сборку мусора
void GarbigeCollector::startCollecting() {
	ExecutionContext* executionContext = ContextStack::top();
	int stack_size = ContextStack::size();

	std::map<string, Variables::var_t> *current = &Variables::global_identifiers;

	std::deque<ExecutionContext*>* q;
	q = (std::deque<ExecutionContext*>*) & ContextStack::context_stack;

	//Проходимся по стеку
	for (int i = 0; i <= stack_size; i++) {
		if(i > 0) current = &((*q)[i-1]->get_environment_record()->records->identifiers);

		for (auto it = current->begin(); it != current->end(); ++it)
		{
			auto variable = it->second.value;
			variable->trace();
		}
	}

	//Удаляем не маркнутые элементы
	GarbigeCollector::removeColectedElements();
}