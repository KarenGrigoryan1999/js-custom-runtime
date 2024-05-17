#include "Errors.h"

string Errors::throw_error(ExceptionTypes type, string text) {
	switch (type)
	{
	case ExceptionTypes::ReferenceError:
		return "Uncaught ReferenceError: " + text;
		break;
	case ExceptionTypes::SyntaxError:
		return "Uncaught SyntaxError: " + text;
		break;
	case ExceptionTypes::TypeError:
		return "Uncaught TypeError: " + text;
		break;
	default:
		return "UnknownError";
		break;
	}
}