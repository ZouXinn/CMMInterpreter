#include "FirstFollowTools.h"
#include "Reader.h"
#include "Production.h"
#include <algorithm>
#include <iterator>

vector<string>* getVns(vector<Production*>* pointer);

struct DependNode//a->b  表示 a U= b
{
	string name;//非终结符号
};
void FirstFollowTools::buildFirst_Follow()
{
	firstSetP = new map<string, set<string>>();
	followSetP = new map<string, set<string>>();
	buildFirst();
	//cout << "First集:" << endl << endl;
	//printFirst();
	//cout << endl << endl << endl;
	buildFollow();
	//cout << "Follow集:" << endl << endl;
	//printFollow();
	return;
}
void FirstFollowTools::printFirst()
{
	vector<string>* Vns = getVns(prosPointerVectorP);
	for (int i = 0; i < Vns->size(); i++)
	{
		string Vn = (*Vns)[i];
		cout << Vn << "\t\t\t\t\t\t";
		set<string> firstSet = (*firstSetP)[Vn];
		for (string s : firstSet)
		{
			cout << s << " ";
		}
		cout <<endl;
	}
}

void FirstFollowTools::printFollow()
{
	vector<string>* Vns = getVns(prosPointerVectorP);
	for (int i = 0; i < Vns->size(); i++)
	{
		string Vn = (*Vns)[i];
		cout << Vn << "\t\t\t\t\t\t";
		set<string> followSet = (*followSetP)[Vn];
		for (string s : followSet)
		{
			cout << s << " ";
		}
		cout << endl;
	}
}

bool in(string s, vector<string>* p)
{
	for (int i = 0; i < p->size(); i++)
	{
		if (p->at(i) == s)
		{
			return true;
		}
	}
	return false;
}
vector<string>* getVns(vector<Production*>* pointer)
{
	vector<string>* ret = new vector<string>();
	for (int i = 0; i < pointer->size(); i++)
	{
		ProductionSym* left = pointer->at(i)->getLeft();
		string s = left->getVal();
		if (!in(s, ret))
		{
			ret->push_back(s);
		}
	}
	return ret;
}

void FirstFollowTools::buildFirst()//求First集   空必须表示为<empty>
{
	vector<string>* aim_str_vec = getVns(this->prosPointerVectorP);
	for (int i = 0; i < aim_str_vec->size(); i++)
	{
		buildFirstOf(aim_str_vec->at(i));
	}
}

void FirstFollowTools::buildFollow()//求Follow集
{
	vector<string>* aim_str_vec = getVns(this->prosPointerVectorP);
	set<string> startSet;
	startSet.insert("$");
	(*followSetP)["<start>"] = startSet;
	for (int i = 1; i < aim_str_vec->size(); i++) // i从1开始
	{
		buildFollowOf(aim_str_vec->at(i));
	}
}

void FirstFollowTools::buildFirstOf(string aim)//求First集
{
	//map<string, bool> *toEmpty;//终结符能否推出空？
	//cout << "getting first of " << aim << endl;
	for (int i = 0; i < prosPointerVectorP->size(); i++)
	{
		Production* production = prosPointerVectorP->at(i);
		if (production->getLeft()->getVal() == aim)//
		{
			ProductionSym* left = production->getLeft();
			vector<ProductionSym*>* right = production->getRight();
			for (int j = 0; j < right->size(); j++)
			{
				ProductionSym* temp = right->at(j);
				if (!temp->isVn())//如果当前符号为终结符
				{
					set<string> curAimSet = (*firstSetP)[aim];
					curAimSet.insert(temp->getVal());
					(*firstSetP)[aim] = curAimSet;
					//pair<string, set<string>> value(aim, Set);
					//firstSetP->insert(value);
					break;
				}
				else if (temp->getVal() == empty_str)//为空
				{
					if (j == right->size() - 1)
					{
						set<string> curAimSet = (*firstSetP)[aim];
						curAimSet.insert(empty_str);
						(*firstSetP)[aim] = curAimSet;
					}
				}
				else// 为非终结符
				{
					if (temp->getVal() != aim)//不是直接左递归则执行
					{//求并集
						buildFirstOf(temp->getVal());
						set<string> curAimSet = (*firstSetP)[aim];
						set<string> tempSet = (*firstSetP)[temp->getVal()];
						if (tempSet.find(empty_str) != tempSet.end())// 空在此set中
						{
							tempSet.erase(empty_str);
							set<string> theUnion;
							//vector<string> vec;
							//set_union(curAimSet.begin(), curAimSet.end(), tempSet.begin(), tempSet.end(), back_inserter(vec));
							set_union(curAimSet.begin(), curAimSet.end(), tempSet.begin(), tempSet.end(), inserter(theUnion,theUnion.begin()));
							//copy(vec.begin(), vec.end(), theUnion.begin());
							(*firstSetP)[aim] = theUnion;
						}
						else//set不包含空，直接跳出循环
						{
							set<string> theUnion;
							set_union(curAimSet.begin(), curAimSet.end(), tempSet.begin(), tempSet.end(), inserter(theUnion, theUnion.begin()));
							(*firstSetP)[aim] = theUnion;
							break;
						}
					}
					else//是直接左递归则跳过
					{
						break;
					}
				}
			}
		}
	}
}

void FirstFollowTools::buildFollowOf(string aim)//求Follow集
{
	int curIndex = 0;
	for (int i = 0; i < prosPointerVectorP->size(); )
	{
		bool find = false;
		Production* production = prosPointerVectorP->at(i);
		ProductionSym* left = production->getLeft();
		vector<ProductionSym*>* right = production->getRight();
		int j = curIndex;
		for (; j < right->size(); j++)
		{
			if (aim == right->at(j)->getVal())// A-> bBcB   ?
			{
				find = true;
				break;
			}
		}
		if (find)
		{
			curIndex = j;
			if (j == right->size() - 1 && aim != left->getVal())//aim 是产生式的最右边一个并且aim与产生式左部不同(如果相同则什么都不用做)
			{
				if (followSetP->count(left->getVal()) != 1)//map 中还没有 left的follow集
				{
					buildFollowOf(left->getVal());
				}
				set<string> curAimSet = (*followSetP)[aim];
				set<string> leftSet = (*followSetP)[left->getVal()];
				set<string> theUnion;
				set_union(curAimSet.begin(), curAimSet.end(), leftSet.begin(), leftSet.end(), inserter(theUnion, theUnion.begin()));
				(*followSetP)[aim] = theUnion;
				i++;
				curIndex = 0;
			}
			else if (j == right->size() - 1 && aim == left->getVal())//aim 是产生式的最右边一个并且aim与产生式左部相同
			{
				i++;
				curIndex = 0;
			}
			else // aim 右边还有内容
			{
				for (; j < right->size()-1; j++)
				{
					ProductionSym* temp = right->at(j+1);
					if (!temp->isVn())//如果是终结符,则加入follow集
					{
						set<string> curAimSet = (*followSetP)[aim];
						curAimSet.insert(temp->getVal());
						(*followSetP)[aim] = curAimSet;
						i++;
						curIndex = 0;
						break;
					}
					else//是非终结符
					{
						set<string> firstSet = (*firstSetP)[temp->getVal()];
						if (firstSet.find(empty_str) != firstSet.end())//此非终结符的first集包含 空
						{
							//并上temp的(first-empty)和follow
							//本文法只有<formal_para_list> <real_para_list> <stmts> 他们的follow都是简单的终结符 )  )  }
							cout << "进入了麻烦的地方,可能陷入死循环" << endl;
							//暂且简单处理，因为本文法暂时不会进入此分支
							if (followSetP->count(temp->getVal()) != 1)//map 中还没有 aim的follow集
							{
								buildFollowOf(temp->getVal());
							}
							set<string> curAimSet = (*followSetP)[aim];
							set<string> tempFollowSet = (*followSetP)[temp->getVal()];
							set<string> tempFirstSet = (*firstSetP)[temp->getVal()];
							tempFirstSet.erase(empty_str);// first(temp) - empty
							set<string> theUnion1,theUnion;
							set_union(curAimSet.begin(), curAimSet.end(), tempFollowSet.begin(), tempFollowSet.end(), inserter(theUnion1, theUnion1.begin()));
							set_union(theUnion1.begin(), theUnion1.end(), tempFirstSet.begin(), tempFirstSet.end(), inserter(theUnion, theUnion.begin()));
							(*followSetP)[aim] = theUnion;
							if (j + 1 >= right->size() - 1)
							{
								curIndex = j + 1;
							}
						}
						else//此非终结符的first集不包含 空, 则直接将first并入aim的follow集中
						{
							set<string> followSet = (*followSetP)[aim];
							set<string> theUnion;
							set_union(firstSet.begin(), firstSet.end(), followSet.begin(), followSet.end(), inserter(theUnion, theUnion.begin()));
							(*followSetP)[aim] = theUnion;
							//i++和j改变的问题
							//如果后面不再有aim  则 i++ ，并令curIndex = 0
							//如果后面还有aim 则i不变，令curIndex = 下一个aim所在的下标
							bool hasAnother = false;
							for (j = curIndex + 1; j < right->size(); j++)
							{
								if (aim == right->at(j)->getVal())
								{
									hasAnother = true;
									break;
								}
							}
							if (hasAnother) {
								curIndex = j;
							}
							else
							{
								i++;
								curIndex = 0;
							}
							break;
						}
					}
				}
				/*if (j == right->size() - 1)
				{
					ProductionSym* temp = right->at(j);
					if (temp->isVn())
					{
						set<string> firstSet = (*firstSetP)[temp->getVal()];
					}
				}*/
			}
		}
		else
		{
			i++;
			curIndex = 0;
		}
	}
}

bool FirstFollowTools::saveFirst_Follow(const char* fileName)
{
	
	return true;
}

bool FirstFollowTools::saveFirst_Follow(FF* ffPointer)
{
	return true;
}

bool toEmpty(vector<Production*>* productionVector,string s)//s 是否能推出空？
{
	return true;
}

FirstFollowTools::FirstFollowTools(string empty_str, const char* fileName)
{
	this->firstSetP = nullptr;
	this->followSetP = nullptr;
	this->empty_str = empty_str;
	this->prosPointerVectorP = Reader::readProductions(fileName);
	buildFirst_Follow();
}

FirstFollowTools::FirstFollowTools(string empty_str,vector<Production*>* prosPointerVectorP)
{
	this->firstSetP = nullptr;
	this->followSetP = nullptr;
	this->empty_str = empty_str;
	this->prosPointerVectorP = prosPointerVectorP;
	buildFirst_Follow();
}

map<string, set<string>>* FirstFollowTools::getFollow()
{
	return this->followSetP;
}