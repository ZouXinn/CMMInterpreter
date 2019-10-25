#include "WhileStmtAST.h"

WhileStmtAST::WhileStmtAST(ExpAST* expAST, StmtsAST* stmtsAST)
{
	this->expAST = expAST;
	this->stmtsAST = stmtsAST;
}

WhileStmtAST::~WhileStmtAST()
{
	if (this->expAST != nullptr)
	{
		delete this->expAST;
	}
	if (this->stmtsAST != nullptr)
	{
		delete this->stmtsAST;
	}
}