#include "IdListAST.h"


IdListAST::IdListAST()
{
	this->idItemASTs = new vector<IdItemAST*>();
}

IdListAST::IdListAST(IdItemAST* item)
{
	this->idItemASTs = new vector<IdItemAST*>();
	addIdItem(item);
}

IdListAST::~IdListAST()
{
	for (int i = 0; i < idItemASTs->size(); i++)
	{
		delete idItemASTs->at(i);
	}
	delete idItemASTs;
}

void IdListAST::addIdItem(IdItemAST* item)
{
	this->idItemASTs->push_back(item);
}