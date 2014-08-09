#ifndef UTILITIES_INCLUDED
#define UTILITIES_INCLUDED

#include <string>

std::string swapChars(std::string& str, int i)
{
	char tmp;
	tmp = str[i];
	str[i] = str[i+1];
	str[i+1] = tmp;
	return str;
}

#endif // UTILITIES_INCLUDED