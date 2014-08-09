#include <string>
using namespace std;

string swapChars(string& str, int i)
{
	char tmp;
	tmp = str[i];
	str[i] = str[i+1];
	str[i+1] = tmp;
	return str;
}