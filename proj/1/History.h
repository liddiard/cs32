#ifndef HISTORY_INCLUDED
#define HISTORY_INCLUDED

#include <vector>
#include "globals.h"

class History
{
    public:
        History(int nRows, int nCols);
        bool record(int r, int c);
        void display() const;
    private:
        int m_nRows;
        int m_nCols;
        char m_alphabet[ALPHABET_LENGTH];
        int m_history[MAXROWS][MAXCOLS];
};

#endif
