#include "Exception.h"
#include <iostream>

Exception::Exception(ExType type,int row,const char* detail)
{
	this->row = row;
	this->detail = detail;
	this->type = type;
}


void Exception::printException()
{
	std::cout << "µÚ" << row << "ÐÐ³ö´í£º";
	std::cout << '(';
	switch (this->type)
	{
	case LexerEx:
		std::cout << "´Ê·¨´íÎó";
		break;
	case ParserEx:
		std::cout << "Óï·¨´íÎó";
		break;
	case StaticSemaEx:
		std::cout << "¾²Ì¬ÓïÒå´íÎó";
		break;
	case DynamicSemaEx:
		std::cout << "¶¯Ì¬ÓïÒå´íÎó";
		break;
	case OtherEx:
		std::cout << "ÆäËû´íÎó";
		break;
	}
	std::cout << ')';
	std::cout << std::endl;
	std::cout << "    " << detail << std::endl;
}
