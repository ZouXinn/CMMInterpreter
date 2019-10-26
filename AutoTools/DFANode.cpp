#include "DFANode.h"

int DFANode::totalNum = 0;
DFANode* DFANode::lastNode = nullptr;
DFANode::DFANode()
{
	this->index = totalNum;
	this->productions = new vector<Production>();
	this->behaviors = new vector<behave>();
}

DFANode::DFANode(vector<Production>* productions)
{
	this->index = totalNum;
	this->productions = productions;
	this->behaviors = new vector<behave>();
}

DFANode* DFANode::createNewNode()
{
	DFANode* ret = new DFANode();
	totalNum++;
	lastNode = ret;
	return ret;
}

DFANode* DFANode::createNewNode(vector<Production>* productions)
{
	DFANode* ret = new DFANode(productions);
	totalNum++;
	lastNode = ret;
	return ret;
}

int DFANode::getTotalNum()
{
	return DFANode::totalNum;
}

int DFANode::getIndex()
{
	return this->index;
}

void DFANode::push_behavior(behave b)
{
	this->behaviors->push_back(b);
}

bool DFANode::theSameAs(DFANode* node)//判断两个DFA是否相等
{
	if (productions->size() != node->productions->size())
	{
		return false;
	}
	for (int i = 0; i < productions->size(); i++)
	{
		bool canMatch = false;
		for (int j = 0; j < node->productions->size(); j++)
		{
			if (productions->at(i).theSameAs(&(node->productions->at(j))))
			{
				canMatch = true;
				break;
			}
		}
		if (!canMatch) {
			return false;
		}
	}
	return true;
}

vector<Production>* DFANode::getProductions()
{
	return this->productions;
}

DFANode::~DFANode()
{
	delete this->productions;
	delete this->behaviors;
}

void DFANode::distory(DFANode* node)
{
	if (lastNode == nullptr)
	{
		cout << "不能连续销毁Node" << endl;
		exit(0);
	}
	else if (node == lastNode)
	{
		delete node;
		totalNum--;
		lastNode = nullptr;
	}
	else
	{
		cout << "只能销毁最近产生的一个DFANode" << endl;
		exit(0);
	}
}


vector<behave>* DFANode::getBehaviors()
{
	return behaviors;
}

void DFANode::show()
{
	for (int i = 0; i < productions->size(); i++)
	{
		cout << productions->at(i).getLeft()->getVal() << "  ->  ";
		for (int j = 0; j < productions->at(i).getRight()->size(); j++)
		{
			if (j == productions->at(i).getDotIndex())
			{
				cout << "@ ";
			}
			cout << productions->at(i).getRight()->at(j)->getVal() << ' ';
		}
		if (productions->at(i).getDotIndex() == productions->at(i).getRight()->size())
		{
			cout << "@";
		}
		cout << endl;
	}
}