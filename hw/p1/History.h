#ifndef HISTORY_INCLUDED
#define HISTORY_INCLUDED

#include <vector>

struct Coordinate
{
    int x;
    int y;
};

class History
{
    public:
        History(int nRows, int nCols);
        bool record(int r, int c);
        void display() const;
    private:
        int m_nRows;
        int m_nCols;
        std::vector<Coordinate> history;
};

#endif
