#ifndef NODE_H
#define NODE_H

#include "BaseValue.h"

using namespace std;

class Node
{
public:
	Node();
	virtual BaseValue* eval();
};

#endif