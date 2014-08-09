#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "hash.h"
using namespace std;

const float MAX_LOAD_FACTOR = 0.5;

void spellCheck(istream& inf, istream& wordlistfile, ostream& outf)
{
	// variable initialization
	stringstream ss;
	string line;
	string word;
	int wordlist_size;

	// create a hashtable of appropriate size
	getline(wordlistfile, line);
	ss << line;
	ss >> wordlist_size;
	HashTable * wordlist = new HashTable(wordlist_size / MAX_LOAD_FACTOR);

	// load words into the hashtable
	while (getline(wordlistfile, line)) 
	{
		ss << line;
		ss >> word;
		wordlist->insert(word);
	}

	delete wordlist;
}

int main()
{
	ifstream wordlist("wordlist.txt");
	ifstream input("test_input.txt");
	spellCheck(input, wordlist, cout);
}