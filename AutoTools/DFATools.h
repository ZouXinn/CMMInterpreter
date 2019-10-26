#pragma once
#include "DFANode.h"
#include "structs.cpp"
#include <map>
#include <set>
struct DicIndex//用于map使用 : (state,sym) -> string
{
	int state;
	std::string sym;
	friend bool operator < (const struct DicIndex& d1, const struct DicIndex& d2);
};

class DFATools
{
private:
	vector<Production*>* productions;
	vector<DFANode*>* nodes;
	int nodeNum = 0;
	map<DicIndex,string>* SLR1_table;
	map<string, set<string>>* followSet;
	string empty_str;
	

	void dealWithEmpty();
	int getReduceIndex(Production* pro);//根据产生式获得其在productions中的下标
	void readRules(const char* ruleFileName);


public:
	DFATools(const char* productionfileName,string empty_str);
	int alreadyInDFAGroup(DFANode* node);//若不在Nodes中，则返回-1，否则返回在Nodes中的下标
	void buildNodes();
	void achieve(DFANode* node);//获得i的行为，如移进规约等等,  并且要加入新的项目
	void derive(DFANode* node);//传入里面已经有产生式的I ，进行派生

	void getSLR1Table(const char* ruleFileName);
	void writeSLR1Table(const char* targetFileName, const char* ruleFileName);//将SLR1表持久化
	void show();
	static map<DicIndex, string>* readSLR1Table(const char* sourceFileName);
};

