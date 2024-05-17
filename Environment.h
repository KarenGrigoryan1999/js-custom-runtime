#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "BaseValue.h"
#include "Variables.h"

using namespace std;

class Environment {
public:
    Variables* records;
    Environment* outer;
};
#endif