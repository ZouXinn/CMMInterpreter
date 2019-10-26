#pragma once
#include "AST.h"
class IntAST :
	public AST
{
public:
	int integer;
	IntAST(int integer)
	{
		this->integer = integer;
	};
};

