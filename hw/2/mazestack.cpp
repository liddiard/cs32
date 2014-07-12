#include <stack>
#include <iostream> // TODO: remove
using namespace std;

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

bool visit (int row, int col, stack<Coord> &coordStack, char maze[][10])
{
    coordStack.push(Coord(row, col));
    maze[row][col] = '*';
    cout << "pushing " << row << "," << col << endl;
}

bool movable(char position) { return (position != 'X' && position != '*'); }

bool findsMinotaur(char maze[][10], int er, int ec)
{
    stack<Coord> coordStack;
    visit(er, ec, coordStack, maze);

    while (!coordStack.empty())
    {
        Coord cur = coordStack.top();
        coordStack.pop();
        int row = cur.r();
        int col = cur.c();
        cout << maze[row][col] << " ";
        if (maze[row][col] == 'M') return true; // we've found the minotaur!
 
        if (movable(maze[row][col+1]))
        {
            visit(row, col+1, coordStack, maze); 
        }
        if (movable(maze[row+1][col]))
        {
            visit(row+1, col, coordStack, maze); 
        }
        if (movable(maze[row][col-1]))
        {
            visit(row, col-1, coordStack, maze); 
        }
        if (movable(maze[row-1][col]))
        {
            visit(row-1, col, coordStack, maze); 
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
