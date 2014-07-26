#include <stack>
#include <iostream> 
using namespace std;

const int NUM_DIRECTIONS = 4;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool findsMinotaur(char maze[][10], int row, int col)
{
    if (maze[row][col] == 'M') return true; // maze solved
    maze[row][col] = '*';   
    Coord dir[] = {Coord(row+1, col), Coord(row-1, col), Coord(row, col+1), Coord(row, col-1)};
    for (int i = 0; i < 4; i++)
    {
        char cur = maze[dir[i].r()][dir[i].c()];
        if (cur != '*' && cur != 'X')
            if (findsMinotaur(maze, dir[i].r(), dir[i].c())) return true;
    }
    return false;
}

int main()
{
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X'},
        { 'X','M','.','.','.','.','.','.','.','X'},
        { 'X','X','.','X','.','X','X','X','X','X'},
        { 'X','.','.','X','.','X','.','.','.','X'},
        { 'X','.','.','X','.','.','.','X','.','X'},
        { 'X','X','X','X','.','X','X','X','.','X'},
        { 'X','.','.','X','.','.','.','X','X','X'},
        { 'X','.','.','X','X','.','X','X','.','X'},
        { 'X','.','.','.','X','.','.','.','.','X'},
        { 'X','X','X','X','X','X','X','X','X','X'}
    };

    if (findsMinotaur(maze, 6,4))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
