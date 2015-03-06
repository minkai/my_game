#include "convert to str.h"

string convert_to_str(double para)
{
	stringstream obj;
	obj << para;
	return obj.str();
}
string convert_to_str(const char* para)
{
	string temp = para;
	return temp;
}