#include "DFATools.h"
#include "Reader.h"
#include <map>
#include "FirstFollowTools.h"
#include <fstream>

DFATools::DFATools(const char* productionfileName,string empty_str)
{
	this->productions = Reader::readProductions(productionfileName);
	this->nodes = new vector<DFANode*>();
	this->empty_str = empty_str;
	this->SLR1_table = nullptr;
	FirstFollowTools* firstFollowTool = new FirstFollowTools(empty_str, productionfileName);
	this->followSet = firstFollowTool->getFollow();
	dealWithEmpty();
}

int DFATools::alreadyInDFAGroup(DFANode* node)
{
	for (int i = 0; i < nodeNum; i++)//nodes->size()
	{
		if (node->theSameAs(nodes->at(i)))
		{
			return i;
		}
	}
	return -1;
}

void DFATools::buildNodes()
{
	if (productions == nullptr || productions->size() <= 0)
	{
		cout << "no productions! at DFATools::buildNodes()" << endl;
		system("pause");
		exit(1);
	}
	vector<Production>* pros = new vector<Production>();
	pros->push_back(*(productions->at(0)));
	DFANode* node = DFANode::createNewNode(pros);
	derive(node);
	nodes->push_back(node);
	nodeNum++;
	achieve(node);
	for (int j = 1; j < nodeNum; j++)
	{
		achieve(nodes->at(j));//获得行为并加入新的状态
	}
}
int DFATools::getReduceIndex(Production* pro)
{
	for (int i = 0; i < productions->size(); i++)
	{
		if (productions->at(i)->getLeft()->getVal() != pro->getLeft()->getVal()||
			productions->at(i)->getRight()->size() != pro->getRight()->size())
		{
			continue;
		}
		else
		{
			bool theSame = true;
			for (int j = 0; j < productions->at(i)->getRight()->size(); j++)
			{
				if (productions->at(i)->getRight()->at(j)->getVal() != pro->getRight()->at(j)->getVal())
				{
					theSame = false;
					break;
				}
			}
			if (theSame)
			{
				return i;
			}
		}
	}
	return -1;
}

void DFATools::achieve(DFANode* node)//获得i的行为，如移进规约等等,  并且要加入新的项目
{
	int DFAIndex = node->getIndex();
	const int account = node->getProductions()->size();
	map<int, bool> m_map;
	for (int j = 0; j < account; j++)//先处理归约项目
	{
		if (nodes->at(DFAIndex)->getProductions()->at(j).getDotIndex() == nodes->at(DFAIndex)->getProductions()->at(j).getRight()->size())
		{
			behave b;
			b.aim = getReduceIndex(&(nodes->at(DFAIndex)->getProductions()->at(j)));
			if (b.aim == -1)
			{
				cout << "something wrong with DFA! at function DFATools::achieve()" << endl;
				system("pause");
				exit(1);
			}
			b.behavior = 2;
			b.value = nodes->at(DFAIndex)->getProductions()->at(j).getLeft()->getVal();
			m_map[j] = true;
			nodes->at(DFAIndex)->push_behavior(b);
		}
	}
	for (int j = 0; j < account; j++) //处理移进项目
	{
		int k = j;
		while (m_map.count(k) == 1 && k <nodes->at(DFAIndex)->getProductions()->size()) {
			k++;//找到第一个没有移进过的
		}
		if (k < nodes->at(DFAIndex)->getProductions()->size() && nodes->at(DFAIndex)->getProductions()->at(k).getDotIndex() < nodes->at(DFAIndex)->getProductions()->at(k).getRight()->size())//如果是移进项目，则处理他
		{
			vector<Production>* pro_vector = new vector<Production>();//记录了移进当前符号后的产生式 如A->a.b 则记录的是A->ab.  当然，不一定只有一条记录
			ProductionSym* sym = new ProductionSym(nodes->at(DFAIndex)->getProductions()->at(k).getRight()->at(nodes->at(DFAIndex)->getProductions()->at(k).getDotIndex()));
			Production pro = nodes->at(DFAIndex)->getProductions()->at(k);
			pro.addDotIndex();
			pro_vector->push_back(pro);
			m_map[k] = true;
			k++;
			while (k < account) // 后面的如果sym的val和s的val一样，则一定没有加入m_map
			{
				if (m_map.count(k) == 0 && nodes->at(DFAIndex)->getProductions()->at(k).getRight()->at(nodes->at(DFAIndex)->getProductions()->at(k).getDotIndex())->getVal() == sym->getVal())
				{
					Production tpro = nodes->at(DFAIndex)->getProductions()->at(k);
					tpro.addDotIndex();
					pro_vector->push_back(tpro);
					m_map[k] = true;
				}
				k++;
			}
			if (pro_vector->size() > 0)
			{
				DFANode* tnode = DFANode::createNewNode(pro_vector);
				int index = nodes->at(DFAIndex)->getIndex();
				derive(tnode);//将node进行派生
				int indexOfNode = alreadyInDFAGroup(tnode);
				if (indexOfNode == -1)//不在DFAGroup中
				{
					nodes->push_back(tnode);
					nodeNum++;
					behave b;
					b.behavior = sym->isVn() ? 1 : 0;
					b.aim = tnode->getIndex();
					b.value = sym->getVal();
					nodes->at(index)->push_behavior(b);
				}
				else
				{
					behave b;
					b.behavior = sym->isVn() ? 1 : 0;
					b.aim = indexOfNode;
					b.value = sym->getVal();
					nodes->at(index)->push_behavior(b);
					DFANode::distory(tnode);
				}
			}
		}
	}
}

void DFATools::derive(DFANode* node)//传入里面已经有产生式的node ，进行派生
{
	vector<Production>* pros = node->getProductions();
	for (int k = 0; k < pros->size(); k++)
	{
		if (pros->at(k).getDotIndex() < pros->at(k).getRight()->size())//不是归约项目
		{
			bool isVt = !(pros->at(k).getRight()->at(pros->at(k).getDotIndex())->isVn());//是否是终结符
			if (!isVt)//是非终结符
			{
				string aim = pros->at(k).getRight()->at(pros->at(k).getDotIndex())->getVal();
				for (int j = 0; j < productions->size(); j++)
				{
					if (productions->at(j)->getLeft()->getVal() == aim)
					{
						bool canAdd = true;
						for (int m = 0; m < pros->size(); m++)
						{
							if (pros->at(m).theSameAs(productions->at(j)))
							{
								canAdd = false;
								break;
							}
						}
						if (canAdd)
						{
							pros->push_back(*(productions->at(j)));
						}
					}
				}
			}
		}
	}
}

void DFATools::getSLR1Table(const char* ruleFileName)
{
	this->SLR1_table = new map<DicIndex, string>();
	//FirstFollowTools* firstFollowTool = new FirstFollowTools(empty_str,productions);
	//map<string, set<string>>* followSet = firstFollowTool->getFollow();
	for (int i = 0; i < nodeNum; i++)
	{
		/*if (i == 114)
		{
			cout << i;
		}*/
		vector<behave>* behaviors = nodes->at(i)->getBehaviors();
		for (int j = 0; j < behaviors->size(); j++)
		{
			if (behaviors->at(j).behavior == 0)//移进终结符
			{
				DicIndex dicIndex;
				dicIndex.state = nodes->at(i)->getIndex();
				dicIndex.sym = behaviors->at(j).value;
				int aimState = behaviors->at(j).aim;
				string s = "S" + to_string(aimState);
				if (this->SLR1_table->count(dicIndex) == 1)//已存在，需解决冲突,应该是不会存在的()
				{
					//先使用旧的人工解决方案
					cout << "the table at(" << dicIndex.state << "," << dicIndex.sym << ") is already " <<
						(*SLR1_table)[dicIndex] << endl;
					cout << "but we are going to insert " << s << " at that place" << endl;
					cout << "the state is:" << endl;
					nodes->at(i)->show();
					cout << "press \"y\" to insert new and \"n\" to keep old" << endl;
					char c = '\0';
					cin >> c;
					while (true) {
						if (c == 'y') {//可以写进文本，之后就不用再输入
							(*SLR1_table)[dicIndex] = s;
							break;
						}
						else if (c == 'n') {
							break;
						}
						else {
							cout << "please give the right input!" << endl;
						}
					}

					//使用配置文件实现自动化的解决方案???
				}
				else//不存在冲突
				{
					(*SLR1_table)[dicIndex] = s;
				}
			}
			else if (behaviors->at(j).behavior == 1)//移进非终结符
			{
				DicIndex dicIndex;
				dicIndex.state = nodes->at(i)->getIndex();
				dicIndex.sym = behaviors->at(j).value;
				int aimState = behaviors->at(j).aim;
				string s = to_string(aimState);
				if (this->SLR1_table->count(dicIndex) == 1)//已存在，需解决冲突,应该是不会存在的()
				{
					//先使用旧的人工解决方案
					cout << "the table at(" << dicIndex.state << "," << dicIndex.sym << ") is already " <<
						(*SLR1_table)[dicIndex] << endl;
					cout << "but we are going to insert " << s << " at that place" << endl;
					cout << "the state is:" << endl;
					nodes->at(i)->show();
					cout << "press \"y\" to insert new and \"n\" to keep old" << endl;
					char c = '\0';
					cin >> c;
					while (true) {
						if (c == 'y') {//可以写进文本，之后就不用再输入
							(*SLR1_table)[dicIndex] = s;
							break;
						}
						else if (c == 'n') {
							break;
						}
						else {
							cout << "please give the right input!" << endl;
						}
					}
				}
				else//不存在冲突
				{
					(*SLR1_table)[dicIndex] = s;
				}
			}
			else if(behaviors->at(j).behavior == 2)//规约
			{
				//单独提出acc状态
				DicIndex dicIndex;
				dicIndex.state = nodes->at(i)->getIndex();
				if (dicIndex.state == 1) {//acc
					dicIndex.sym = "$";
					string s = "acc";
					(*SLR1_table)[dicIndex] = s;
				}
				else//其他归约项目
				{
					int aimProductionIndex = behaviors->at(j).aim;
					string s = "r" + to_string(aimProductionIndex);
					//要归约的左部符号
					string left = behaviors->at(j).value;
					//要先求左部符号follow集
					set<string> follows = (*followSet)[left];
					for (set<string>::iterator iter = follows.begin(); iter != follows.end(); iter++)//对follow集中的元素进行遍历
					{
						dicIndex.sym = *iter;
						if (SLR1_table->count(dicIndex) == 1)//已存在，出现冲突
						{
							//分情况讨论，要根据文法讨论
							//先使用旧的人工解决方案
							cout << "the table at(" << dicIndex.state << "," << dicIndex.sym << ") is already " <<
								(*SLR1_table)[dicIndex] << endl;
							cout << "but we are going to insert " << s << " at that place" << endl;
							cout << "the state is:" << endl;
							nodes->at(i)->show();
							cout << "press \"y\" to insert new and \"n\" to keep old" << endl;
							char c = '\0';
							cin >> c;
							while (true) {
								if (c == 'y') {//可以写进文本，之后就不用再输入
									(*SLR1_table)[dicIndex] = s;
									break;
								}
								else if (c == 'n') {
									break;
								}
								else {
									cout << "please give the right input!" << endl;
								}
							}
						}
						else
						{
							(*SLR1_table)[dicIndex] = s;
						}
					}
				}
			}
			else
			{
				cout << "behave结构体的behavior属性只能是0、1、2! from: DFATools::getSLR1Table()" << endl;
				system("pause");
				exit(0);
			}
		}
	}
}



void DFATools::writeSLR1Table(const char* targetFileName, const char* ruleFileName)//将SLR1表持久化
{
	fstream out;
	out.open(targetFileName, ios::out);
	if (out.is_open()) {
		map<DicIndex, string>::iterator it;
		it = SLR1_table->begin();
		while (it != SLR1_table->end()) {
			out << '@' << it->first.state << '#' << it->first.sym << '#' << it->second << "@\n";
			it++;
		}
		out << '$';
		out.close();
	}
}
void doErrorInSLRReading() {
	cout << "something wrong while reading SLR" << endl;
	system("pause");
	exit(0);
}
int strToInt(string s) {
	int ret = 0;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] > '9' || s[i] < '0') {
			doErrorInSLRReading();
		}
		else {
			int t = s[i] - '0';
			ret *= 10;
			ret += t;
		}
	}
	return ret;
}
map<DicIndex, string>* DFATools::readSLR1Table(const char* sourceFileName)
{
	map<DicIndex, string>* table = new map<DicIndex, string>();
	fstream in;
	in.open(sourceFileName, ios::in);
	in.seekg(0, ios::end);//移动到末尾
	int length = in.tellg();//获得长度
	in.seekg(0, ios::beg);//移动到开头
	char* buffer = new char[length];
	in.read(buffer, length);
	in.close();
	int num = 0;
	char c = *buffer;
	while (c != '$') {
		if (c != '@') {
			cout << "@ worng , at func DFATools::readSLR1Table()" << endl;
			doErrorInSLRReading();
		}
		buffer++;
		num++;
		c = *buffer;
		string s = "";
		while (c != '#') {
			s += c;
			buffer++;
			num++;
			c = *buffer;
		}
		DicIndex dicIndex;
		dicIndex.state = strToInt(s);
		s = "";
		buffer++;
		num++;
		c = *buffer;
		while (c != '#') {
			s += c;
			buffer++;
			num++;
			c = *buffer;
		}
		dicIndex.sym = s;
		s = "";
		buffer++;
		num++;
		c = *buffer;
		while (c != '@') {
			s += c;
			buffer++;
			num++;
			c = *buffer;
		}
		buffer++;
		num++;
		if (*buffer != '\n') {
			cout << "enter wrong" << endl;
			doErrorInSLRReading();
		}
		else {
			(*table)[dicIndex] = s;
			buffer++;
			num++;
			c = *buffer;
		}
	}
	return table;
}

void DFATools::dealWithEmpty()
{
	if (productions != nullptr)
	{
		for (int i = 0; i < productions->size(); i++)
		{
			Production* temp = productions->at(i);
			vector<ProductionSym*>* tright = temp->getRight();
			if (tright->size() == 1 && tright->at(0)->getVal() == empty_str)
			{
				delete tright->at(0);
				tright->clear();
			}
		}
	}
}


void DFATools::readRules(const char* ruleFileName)
{

}

void DFATools::show()
{
	for (int i = 0; i < nodes->size(); i++)
	{
		cout << "state " << to_string(i) << " :" << endl;
		nodes->at(i)->show();
		cout << "behaviors:" << endl;
		for (int j = 0; j < nodes->at(i)->getBehaviors()->size();j++)
		{
			behave behavior = nodes->at(i)->getBehaviors()->at(j);
			cout << "(" << behavior.behavior << "," << behavior.value << ")" << "  ";
		}
		cout << endl << endl << endl;
	}
}

inline bool operator <(const struct DicIndex& d1, const struct DicIndex& d2) {
	if (d1.state != d2.state) {
		return d1.state < d2.state;
	}
	else {
		if (d1.sym.length() != d2.sym.length()) {
			return d1.sym.length() < d2.sym.length();
		}
		else {
			for (int i = 0; i < d1.sym.length(); i++) {
				if (d1.sym[i] != d2.sym[i]) {
					return d1.sym[i] < d2.sym[i];
				}
			}
			return d1.sym[0] < d2.sym[0];
		}
	}
}