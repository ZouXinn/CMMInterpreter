#pragma once
enum ExType{LexerEx,ParserEx,StaticSemaEx, DynamicSemaEx,OtherEx};
class Exception
{
private:
	int row;
	const char* detail;
	ExType type;
public:
	void printException();
	Exception(ExType type,int row, const char* detail);
};

