#ifndef EXCEPTION_BASE_H
#define EXCEPTION_BASE_H

#include "string";
#include "exceptionTypes.h"

using namespace std;

class Errors
{
public:
	static string throw_error(ExceptionTypes type, string text);
};

#endif