#ifndef EXCEPTION_BASE_H
#define EXCEPTION_BASE_H

#include "string";
#include "exceptionTypes.h"
#include "BaseException.h"
#include "ReferenceError.h"

using namespace std;

class Errors
{
public:
	static BaseException* throw_error(ExceptionTypes type, string text);
};

#endif