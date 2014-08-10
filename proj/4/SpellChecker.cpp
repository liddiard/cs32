#include <iostream>
#include <sstream>
#include <algorithm>
#include "SpellChecker.h"
#include "utilities.cpp"
using namespace std;

SpellChecker::SpellChecker(istream& wordlistfile)
{
	// populate the alphabet array
	for (int i = 0; i < ALPHABET_LENGTH; i++)
	{
		m_alphabet[i] = (char)(65 + i);
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
		transform(word.begin(), word.end(), word.begin(), ::toupper); // convert to upper case
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
			if (m_wordlist->find(misspelling))
				m_suggestions.push_back(misspelling);
		}
		misspelling[i] = orig;
	}
}

void SpellChecker::splitWord(string misspelling)
{
	string s1;
	string s2;
	for (int i = 1; i < misspelling.size(); i++)
	{
		s1 = misspelling.substr(0, i);
		s2 = misspelling.substr(i, misspelling.size());
		if (m_wordlist->find(s1) && m_wordlist->find(s2))
			m_suggestions.push_back(s1 + " " + s2);
	}
}

void SpellChecker::suggest(string misspelling)
{
	if (!m_suggestions.empty()) m_suggestions.clear(); // clear suggestions from previous misspellings
	swapAdjacent(misspelling);
	insertChar(misspelling);
	deleteChar(misspelling);
	replaceChar(misspelling);
	splitWord(misspelling);
}

void SpellChecker::collectSuggestions() // sort and de-dup suggestions
{
	// sort suggestions
	sort(m_suggestions.begin(), m_suggestions.end());

	// remove duplicates
	vector<int> dups;
	for (vector<string>::size_type i = 0; i != m_suggestions.size() - 1; i++)
	{
		if (m_suggestions[i] == m_suggestions[i+1]) dups.push_back(i+1);
	}
	for (vector<int>::size_type i = 0; i != dups.size(); i++)
	{
		m_suggestions.erase(m_suggestions.begin()+ dups[i] - i);
	}
}

void SpellChecker::outputSuggestions(string line, string misspelling, ostream& outf)
{
	this->collectSuggestions();

	// output suggestions
	outf << line << endl;
	outf << "word not found: " << misspelling << endl;
	outf << "perhaps you meant: " << endl;
	for (vector<string>::iterator it = m_suggestions.begin(); it != m_suggestions.end(); ++it)
	{
		outf << *it << endl;
	}
	outf << endl;
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
			transform(word.begin(), word.end(), word.begin(), ::toupper); // convert to upper case
			if (!m_wordlist->find(word))
			{
				this->suggest(word);
				this->outputSuggestions(line, word, outf);
			}
		}
	}
}