#include "DirectTypeSpecifyAST.h"


DirectTypeSpecifyAST::DirectTypeSpecifyAST(TypeAST* type)
{
	this->type = type;
}

DirectTypeSpecifyAST::DirectTypeSpecifyAST(IdentifierAST* structNameIdentifier)
{
	this->structNameIdentifier = structNameIdentifier;
}

DirectTypeSpecifyAST::~DirectTypeSpecifyAST()
{
	if (this->type != nullptr)
	{
		delete this->type;
	}
	if (this->structNameIdentifier != nullptr)
	{
		delete this->structNameIdentifier;
	}
}
