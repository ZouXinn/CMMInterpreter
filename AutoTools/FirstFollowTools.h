#pragma once
#include"Production.h"
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct FF
{
	map<string, set<string>>* firstPointer;
	map<string, set<string>>* followPointer;
};

class FirstFollowTools
{
private:
	void buildFirstOf(string aim);
	void buildFollowOf(string aim);
	void buildFirst();
	void buildFollow();
	void buildFirst_Follow();//获取first集和follow集

	static bool saveFirst_Follow(FF* ffPointer);
	map<string, set<string>>* firstSetP;
	map<string, set<string>>* followSetP;
	string empty_str;
	vector<Production*>* prosPointerVectorP;
public:
	bool saveFirst_Follow(const char* fileName);
	

	FirstFollowTools(string empty_str, const char * fileName);
	FirstFollowTools(string empty_str, vector<Production*>* prosPointerVectorP);
	void printFirst();
	void printFollow();

	map<string, set<string>>* getFollow();
	//static void 

};

