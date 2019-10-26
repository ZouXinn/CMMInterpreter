#include "MyLexer.h"


void testLexer()
{
	MyLexer* lexer = nullptr;
	try {
		lexer = new MyLexer("..//Files//sourceCode.txt");
		lexer->printResult();
	}
	catch (Exception e) {
		e.print();
	}
}