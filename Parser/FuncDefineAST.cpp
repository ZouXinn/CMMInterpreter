#include "FuncDefineAST.h"


FuncDefineAST::FuncDefineAST(TypeSpecifyAST* typeSpecifyAST, FormalParaListAST* formalParaListAST, StmtsAST* stmtsAST, IdentifierAST* funcNameIdentifier)
{
	this->typeSpecifyAST = typeSpecifyAST;
	this->formalParaListAST = formalParaListAST;
	this->stmtsAST = stmtsAST;
	this->funcNameIdentifier = funcNameIdentifier;
}
FuncDefineAST::~FuncDefineAST()
{
	if (this->formalParaListAST != nullptr)
	{
		delete this->formalParaListAST;
	}
	if (this->typeSpecifyAST != nullptr)
	{
		delete this->typeSpecifyAST;
	}
	if (this->stmtsAST != nullptr)
	{
		delete this->stmtsAST;
	}
	if (this->funcNameIdentifier != nullptr)
	{
		delete this->funcNameIdentifier;
	}
}