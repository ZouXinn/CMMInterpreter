#include "FormalParaItemAST.h"


FormalParaItemAST::FormalParaItemAST(TypeSpecifyAST* typeSpecifyAST, DecVarNameAST* decVarNameAST)
{
	this->typeSpecifyAST = typeSpecifyAST;
	this->decVarNameAST = decVarNameAST;
}

FormalParaItemAST::~FormalParaItemAST()
{
	delete this->typeSpecifyAST;
	delete this->decVarNameAST;
}