#pragma once
#include "AST.h"
//#include "..//Lexer/header.h"
#include "..//Parser/FromLexer/header.h"
class OtherSymAST :
	public AST
{
public:
	Token sym_token;
	OtherSymAST(Token sym_token)
	{
		this->sym_token = sym_token;
	};
};

