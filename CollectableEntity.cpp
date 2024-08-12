#include "CollectableEntity.h"
#include "GarbigeCollector.h"

CollectableEntity::CollectableEntity() {}

void CollectableEntity::registerInHeap() {
	GarbigeCollector::registerObj(this);
}

int CollectableEntity::get_data_size() {
	return 0;
}

int CollectableEntity::get_entity_type() {
	return 1;
}

void CollectableEntity::trace() {
	
}