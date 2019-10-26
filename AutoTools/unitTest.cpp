#include "unitTest.h"
#include "Production.h"
#include "Reader.h"
#include <iostream>
#include <string>
#include "FirstFollowTools.h"
#include "DFATools.h"
using namespace std;
void testReader()
{
	//读取产生式

	vector<Production*>* pros = Reader::readProductions("..//Files//MyProductions.txt");
}

void testFirstFollowTools()
{
	FirstFollowTools* tool = new FirstFollowTools("empty", "..//Files//MyProductions.txt");
	cout << "First:" << endl;
	tool->printFirst();
	cout << endl << endl;
	cout << "Follow:" << endl;
	tool->printFollow();
}

void testDFATools()
{
	const char* ruleFileName = "";
	DFATools* tool = new DFATools("..//Files//MyProductions.txt", "empty");
	//DFATools* tool = new DFATools("productions.txt", "empty");
	tool->buildNodes();
	tool->show();
	tool->getSLR1Table(ruleFileName);
	tool->writeSLR1Table("..//Files//SLR1.txt", ruleFileName);
}

void testReadSLR1Table()
{
	map<DicIndex, string>* table = DFATools::readSLR1Table("..//Files//SLR1.txt");
}