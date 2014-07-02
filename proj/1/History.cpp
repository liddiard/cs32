#include <iostream>
#include "History.h"
#include "globals.h"

History::History(int nRows, int nCols)
{
    m_nRows = nRows;
    m_nCols = nCols;    
    for (int i = 0; i < ALPHABET_LENGTH; i++)
    {
        m_alphabet[i] = (char)(65+i);
    }
    for (int i = 0; i < m_nRows; i++)
    {
        for (int j = 0; j < m_nCols; j++)
        {
            m_history[i][j] = 0;
        }
    }
}

bool History::record(int r, int c)
{
    if (r > 0 && r <= m_nRows && c > 0 && c <= m_nCols)
    {
        m_history[r-1][c-1] += 1;
        return true;
    } else return false;
}

void History::display() const
{
    clearScreen();
    for (int i = 0; i < m_nRows; i++)
    {
        for (int j = 0; j < m_nCols; j++)
        {
            if (m_history[i][j] == 0)
                std::cout << ".";
            else if (m_history[i][j] < ALPHABET_LENGTH)
                std::cout << m_alphabet[m_history[i][j]-1];
            else
                std::cout << m_alphabet[ALPHABET_LENGTH-1];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
