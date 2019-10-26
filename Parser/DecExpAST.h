#pragma once
#include "AST.h"
class DecExpAST:public AST
{
public:
	int son = -1;//0 表示<var_dec>    1表示  <struct_dec>
};

