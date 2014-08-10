#include <iostream>
#include <fstream>
#include "SpellChecker.h"
using namespace std;

void spellCheck(istream& inf, istream& wordlistfile, ostream& outf)
{
	SpellChecker checker = SpellChecker(wordlistfile);
	checker.spellCheck(inf, outf);
}

int main()
{
	ifstream wordlist("wordlist.txt");
	ifstream input("test_input.txt");
	spellCheck(input, wordlist, cout);
}