/*
此项目的作用: 1、自动求First、Follow集
			  2、自动构造项目规范集族
*/
#include <iostream>
#include <string>
#include "Reader.h"
#include "FirstFollowTools.h"
#include "DFATools.h"
#include "unitTest.h"
using namespace std;
/*void testReader();
void testFirstFollowTools();
void testDFATools();
void testReadSLR1Table();*/


int main()
{
	
	//
	//testReader();
	//
	testFirstFollowTools();
	//
	testDFATools();
	//
	testReadSLR1Table();

	return 0;
}
