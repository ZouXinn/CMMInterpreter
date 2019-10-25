#include "IdItemAST.h"

IdItemAST::IdItemAST(DecVarNameAST* decVarNameAST)
{
	this->decVarNameAST = decVarNameAST;
}

IdItemAST::IdItemAST(DecVarNameAST* decVarNameAST, ExpAST* exp)
{
	this->decVarNameAST = decVarNameAST;
	this->exp = exp;
}

IdItemAST::IdItemAST(DecVarNameAST* decVarNameAST, ExpListAST* exps)
{
	this->decVarNameAST = decVarNameAST;
	this->exps = exps;
}

IdItemAST::~IdItemAST()
{
	delete this->decVarNameAST;
	if (this->exp != nullptr)
	{
		delete this->exp;
	}
	if (this->exps != nullptr)
	{
		delete this->exps;
	}
}