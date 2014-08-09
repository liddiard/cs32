#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
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
	vector<string> paragraph;

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

	// spellcheck each word
	while (getline(inf, line)) // while we have lines (paragraphs)
	{
		ss << line;
		while (ss >> word) // while we have words in the line
		{
			transform(word.begin(), word.end(), word.begin(), ::tolower);
			if (!wordlist->find(word))
				cout << "didn't find " << word << endl;
		}
	}

	delete wordlist;
}

int main()
{
	ifstream wordlist("wordlist.txt");
	ifstream input("test_input.txt");
	spellCheck(input, wordlist, cout);
}