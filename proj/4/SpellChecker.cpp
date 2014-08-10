#include <iostream>
#include <sstream>
#include "SpellChecker.h"
#include "utilities.cpp"
using namespace std;

SpellChecker::SpellChecker(istream& wordlistfile)
{
	// populate the alphabet array
	for (int i = 0; i < ALPHABET_LENGTH; i++)
	{
		m_alphabet[i] = (char)(97 + i);
	}

	// local variable init
	stringstream ss;
	int wordlist_size;
	string line;
	string word;

	// get the size of the wordlist and create a hash table of apporpriate size
	getline(wordlistfile, line);
	ss << line;
	ss >> wordlist_size;
	m_wordlist = new HashTable(wordlist_size);

	// load words into the hashtable
	while (getline(wordlistfile, line)) 
	{
		ss << line;
		ss >> word;
		m_wordlist->insert(word);
	}
}

SpellChecker::~SpellChecker()
{
	delete m_wordlist;
}


void SpellChecker::swapAdjacent(string misspelling)
{
	for (int i = 0; i < misspelling.size() - 1; i++)
	{
		swapChars(misspelling, i);
		if (m_wordlist->find(misspelling))
			m_suggestions.push_back(misspelling);
		swapChars(misspelling, i); // swap them back to original positions
	}
}

void SpellChecker::insertChar(string misspelling)
{
	for (int i = 0; i < misspelling.size() + 1; i++)
	{
		for (int j = 0; j < ALPHABET_LENGTH; j++)
		{
			misspelling.insert(misspelling.begin()+i, m_alphabet[j]);
			if (m_wordlist->find(misspelling))
				m_suggestions.push_back(misspelling);
			misspelling.erase(i, 1);
		}
	}
}

void SpellChecker::deleteChar(string misspelling)
{
	char orig;
	for (int i = 0; i < misspelling.size(); i++)
	{
		orig = misspelling[i];
		misspelling.erase(i, 1);
		if (m_wordlist->find(misspelling))
			m_suggestions.push_back(misspelling);
		misspelling.insert(misspelling.begin()+i, orig);
	}
}

void SpellChecker::replaceChar(string misspelling)
{
	char orig;
	for (int i = 0; i < misspelling.size(); i++)
	{
		orig = misspelling[i];
		for (int j = 0; j < ALPHABET_LENGTH; j++)
		{
			misspelling[i] = m_alphabet[j];
			cout << "attempting: " << misspelling << endl;
			if (m_wordlist->find(misspelling))
				m_suggestions.push_back(misspelling);
		}
		misspelling[i] = orig;
	}
}

void SpellChecker::suggest(string misspelling)
{
	if (!m_suggestions.empty()) m_suggestions.clear(); // clear suggestions from previous misspellings
	swapAdjacent(misspelling);
	insertChar(misspelling);
	deleteChar(misspelling);
	replaceChar(misspelling);
}

void SpellChecker::spellCheck(istream& inf, ostream& outf)
{
	stringstream ss;
	string line;
	string word;

	// spellcheck each word
	while (getline(inf, line)) // while we have lines (paragraphs)
	{
		ss << line;
		while (ss >> word) // while we have words in the line
		{
			transform(word.begin(), word.end(), word.begin(), ::tolower); // convert to lower case
			if (!m_wordlist->find(word))
			{
				this->suggest(word);
				// print suggestions
			}
		}
	}
}