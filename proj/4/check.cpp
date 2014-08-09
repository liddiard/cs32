#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "hash.h"
#include "utilities.cpp"
using namespace std;

const int ALPHABET_LENGTH = 26;
const float MAX_LOAD_FACTOR = 0.5;

char ALPHABET[ALPHABET_LENGTH];
for (int i = 0; i < ALPHABET_LENGTH; i++)
{
	ALPHABET[i] = (char)(65 + i);
}


void swapAdjacent(string misspelling, HashTable * wordlist, vector<string> * suggestions)
{
	for (int i = 0; i < misspelling.size() - 1; i++)
	{
		swapChars(misspelling, i);
		if (wordlist->find(misspelling))
			suggestions->push_back(misspelling);
		swapChars(misspelling, i); // swap them back to original positions
	}
}

void insertChar(string misspelling, HashTable * wordlist, vector<string> * suggestions)
{
	for (int i = 0; i < misspelling.size(); i++)
	{
		for (int j = 0; j < ALPHABET_LENGTH; j++)
		{
			misspelling.insert(misspelling.begin()+i, ALPHABET[j]);
			cout << "attempting: " << misspelling << endl;
			if (wordlist->find(misspelling))
				suggestions->push_back(misspelling);
			misspelling.erase(i);
		}
	}
}

vector<string> * suggest(string misspelling, HashTable * wordlist)
{
	vector<string> * suggestions;
	swapAdjacent(misspelling, wordlist, suggestions);
	return suggestions;
}

void spellCheck(istream& inf, istream& wordlistfile, ostream& outf)
{
	// variable initialization
	stringstream ss;
	string line;
	string word;
	int wordlist_size;
	vector<string> * suggestions;

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
			transform(word.begin(), word.end(), word.begin(), ::tolower); // convert to lower case
			if (!wordlist->find(word))
			{
				suggestions = suggest(word, wordlist);
				// print suggestions
			}
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