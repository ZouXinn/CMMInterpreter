#include "IfStmtAST.h"


IfStmtAST::IfStmtAST(ExpAST* expAST, StmtsAST* thenStmts)
{
	this->expAST = expAST;
	this->thenStmts = thenStmts;
}

IfStmtAST::IfStmtAST(ExpAST* expAST, StmtsAST* thenStmts, StmtsAST* elseStmts):IfStmtAST(expAST,thenStmts)
{
	this->elseStmts = elseStmts;
}

IfStmtAST::~IfStmtAST()
{
	if (this->expAST != nullptr)
	{
		delete this->expAST;
	}
	if (this->thenStmts != nullptr)
	{
		delete this->thenStmts;
	}
	if (this->elseStmts != nullptr)
	{
		delete this->elseStmts;
	}
}