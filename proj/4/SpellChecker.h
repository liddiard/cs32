#ifndef SPELL_CHECKER_INCLUDED
#define SPELL_CHECKER_INCLUDED

#include <string>
#include "hash.h"

const int ALPHABET_LENGTH = 26;

class SpellChecker
{
public:
	SpellChecker(std::istream& wordlistfile);
	~SpellChecker();
	void spellCheck(std::istream& inf, std::ostream& outf);

private:
	char m_alphabet[ALPHABET_LENGTH];
	int m_wordlist_size;
	HashTable * m_wordlist;
	std::vector<std::string> * m_suggestions;

	std::vector<std::string> * suggest(std::string misspelling);
	void swapAdjacent(std::string misspelling);
	void insertChar(std::string misspelling);
};

#endif // SPELL_CHECKER_INCLUDED