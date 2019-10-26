#pragma once
#include <vector>
#include <string>
#include "Production.h"

struct behave
{
	int behavior = -1;//0 移进终结符  1 移进非终结符   2 归约
	std::string value;//移进的符号 或者 归约产生式的左部符号
	int aim = -1;//移进之后到达的状态和归约的产生式序号
};
class DFANode
{
private:
	static int totalNum;
	DFANode();
	DFANode(vector<Production>* productions);
	int index;
	static DFANode* lastNode;
	vector<Production>* productions;
	vector<behave>* behaviors;
	virtual~DFANode();

public:
	static DFANode* createNewNode();
	static DFANode* createNewNode(vector<Production>* productions);
	int getTotalNum();
	bool theSameAs(DFANode* node);
	vector<Production>* getProductions();
	static void distory(DFANode* node);
	int getIndex();
	void push_behavior(behave b);
	vector<behave>* getBehaviors();
	void show();
};

