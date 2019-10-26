#include "StmtsAST.h"

StmtsAST::StmtsAST()
{
	this->stmtASTs = new vector<StmtAST*>();
}

StmtsAST::~StmtsAST()
{
	if (this->stmtASTs != nullptr)
	{
		for (int i = 0; i < this->stmtASTs->size(); i++)
		{
			delete this->stmtASTs->at(i);
		}
		delete this->stmtASTs;
	}
}

void StmtsAST::addStmtAST(StmtAST* ast)
{
	this->stmtASTs->push_back(ast);
}