#ifndef BLOCK_STATEMENT_H
#define BLOCK_STATEMENT_H

#include "Environment.h"
#include "BlockBaseStatement.h"

using namespace std;

class BlockStatement : public BlockBaseStatement
{
public:
	BlockStatement(Environment* statement) : BlockBaseStatement(statement) {};
	const char* plain_name = "BlockStatement";
};

#endif