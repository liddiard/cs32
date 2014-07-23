#include <queue>
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

bool movable(char position) { return (position != 'X' && position != '*'); }

void visit(int row, int col, char maze[][10], queue<Coord>& coordQueue)
{
    coordQueue.push(Coord(row, col));
    maze[row][col] = '*';
}

bool findsMinotaur(char maze[][10], int er, int ec)
{
    queue<Coord> coordQueue;
    if (maze[er][ec] == 'M') return true; // we've found the minotaur!

    visit(er, ec, maze, coordQueue);

    while (!coordQueue.empty())
    {
        Coord cur = coordQueue.front();
        coordQueue.pop();
        int row = cur.r();
        int col = cur.c();

        Coord coords_to_try[NUM_DIRECTIONS] = {Coord(row, col+1), Coord(row+1, col), Coord(row, col-1), Coord(row-1, col)};

        for (int i = 0; i < NUM_DIRECTIONS; i++)
        {
            int t_row = coords_to_try[i].r();
            int t_col = coords_to_try[i].c();
            if (movable(maze[t_row][t_col]))
            {
                if (maze[t_row][t_col] == 'M') 
                {
                    return true; // we've found the minotaur!
                }
                visit(t_row, t_col, maze, coordQueue);
            }
        }
    }
    return false; // no path to minotaur
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
