#pragma once
#include "AST.h"
#include "Enums_Structs.h"
using namespace zx;
class TypeAST :
	public AST
{
public:
	zx::Type type;
	TypeAST(zx::Type type)
	{
		this->type = type;
	}
};

