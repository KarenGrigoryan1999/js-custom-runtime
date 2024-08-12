#ifndef GC_H
#define GC_H

#include <vector>
#include "CollectableEntity.h"
#include "ContextStack.h"
#include "GCItem.h"

#define MAX_HEAP_SIZE 100000000000240

using namespace std;

class GarbigeCollector
{
public:
	GarbigeCollector();
	static void registerObj(CollectableEntity* entity);
	static void findAndMark(CollectableEntity* entity);
	static void removeColectedElements();
	static void init();
private:
	static int heap_size;
	static vector<GCItem> collectableEntities;
	static void startCollecting();
};

#endif