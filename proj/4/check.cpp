#include <iostream>
#include <string>
#include "hash.h"

using namespace std;

void spellCheck(istream& inf, istream& wordlistfile, ostream& outf)
{

}

int main()
{
	HashTable* words = new HashTable(100);
	cout << "1" << endl;
	words->insert("apple");
	cout << "2" << endl;
	words->insert("monkey");
	cout << "3" << endl;
	if (words->find("apple"))
		cout << "Found 'apple'";
	if (words->find("happy"))
		cout << "Found 'happy'";
}