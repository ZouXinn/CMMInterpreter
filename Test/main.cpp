#include <set>
#include <vector>
#include <algorithm>
#include <iostream>
#include<map>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
const int maxn = 123;
int n;
int num[maxn];
enum Token{a,b,c};
struct DicIndex//用于map使用 : (state,sym) -> string
{
	int state;
	string sym;
	friend bool operator < (const struct DicIndex& d1, const struct DicIndex& d2);
};
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
struct MyStruct
{
	int a;
	int b;
};
void testVec();
void testCopyClass();
void testMap();
void testStr2Int();
void testStr2Double();
void testMap1();
void testReadFile();
int main()
{

	/*int min = INT32_MIN;
	int a = SHRT_MIN+1;
	cout << min << " " << -min;*/
	//testMap1();
	/*cout << (min < a);
	cout << endl;
	cout << (-min > -a);*/
	//testStr2Double();
	//Token token = a;
	testReadFile();
	
}
void testReadFile()
{
	const char* file = "..//Files//MyProductions.txt";
	string str;

	ifstream fin;
	fin.open(file, ios::in);
	stringstream buf;
	buf << fin.rdbuf();
	str = buf.str();

	const char* ccp = str.c_str();
	char* cp = const_cast<char*>(ccp);
	cout << cp;
	fin.close();
	system("pause");
	
}
void testStr2Double()
{
	string s = "15.3";
	double d;
	stringstream ss;
	ss << s;
	ss >> d;
	cout << d << endl;
}

void testStr2Int()
{
	string s = "15";
	int i = std::stoi(s, nullptr, 0);
	cout << i << endl;
}
void testMap()
{
	map<DicIndex, string> Map;
	cout << "ss";

}
struct As {
	int a;
};
void testMap1()
{
	map<int, As>* m = new map<int, As>();
	As a;
	a.a = 0;
	(*m)[0] = a;
	(*m)[0].a = 3;
	cout << (*m)[0].a;
}
class A {
public:
	int* a;
	int b;
	A() {
		a = new int;
		b = 0;
		*a = 1;
	}
	A(const A& a)
	{
		this->a = new int;
		*(this->a) = *(a.a);
		this->b = a.b;
	}
};

void testCopyClass()
{
	A pa;
	A pb = pa;
	*(pa.a) = 3;
	cout << *(pb.a);
}

void testVec()
{
	vector<MyStruct>* vec = new vector<MyStruct>();
	MyStruct s;
	s.a = 1;
	s.b = 2;
	vec->push_back(s);
	s.a = 3;
	cout << vec->at(0).a;
	vec->at(0).a = 5;
	cout << vec->at(0).a;
}


void testSet()
{
	set<string> a, b;
	vector<string> c;
	a = { "a", "b" , "cc" };
	b = { "a","b","e","f" };
	//传入的a，b不一定是set， 但一定要有序
	set_union(a.begin(), a.end(), b.begin(), b.end(), back_inserter(c));//并集
	for (string n : c) cout << n << " "; puts("");
	c.clear();



	set_intersection(a.begin(), a.end(), b.begin(), b.end(), back_inserter(c));//交集
	for (string n : c) cout << n << " "; puts("");
	c.clear();

	set_difference(a.begin(), a.end(), b.begin(), b.end(), back_inserter(c)); //差集(b中属于a的元素去掉)
	for (string n : c) cout << n << " "; puts("");
	c.clear();
}