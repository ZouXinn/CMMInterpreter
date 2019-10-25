#pragma once
#include <vector>
#include <string>
using namespace std;



class AST
{
public:
	int row = -1;
	string content;
	void setRow(int row);
	virtual ~AST();
	
};

