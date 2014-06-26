// main.cpp

#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cctype>
#include <cassert>

#include "globals.h"
#include "Villain.h"
#include "Villain.cpp"

using namespace std;


///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Colosseum
{
  public:
      // Constructor/destructor
    Colosseum(int nRows, int nCols);
    ~Colosseum();

      // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     villainCount() const;
    int     getCellStatus(int r, int c) const;
    int     numberOfVillainsAt(int r, int c) const;
    void    display(string msg) const;

      // Mutators
    void setCellStatus(int r, int c, int status);
    bool addVillain(int r, int c);
    bool addPlayer(int r, int c);
    void moveVillains();
    void pushAllVillains(int r, int c, int dir); // pushes all villains at [r,c] in the given direction

  private:
    int     m_grid[MAXROWS][MAXCOLS];
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Villain* m_villains[MAXVILLAINS];
    int     m_nVillains;
    int     m_turns;

      // Helper functions
    void checkPos(int r, int c) const;
    bool isPosInBounds(int r, int c) const;
};

class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nVillains);
    ~Game();

      // Mutators
    void play();

  private:
    Colosseum* m_colosseum;

      // Helper functions
    string takePlayerTurn();
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int randInt(int lowest, int highest);
bool charToDir(char ch, int& dir);
bool attemptMove(const Colosseum& colosseum, int dir, int& r, int& c);
bool recommendMove(const Colosseum& colosseum, int r, int c, int& bestDir);
int computeDanger(const Colosseum& colosseum, int r, int c);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Colosseum implementation
///////////////////////////////////////////////////////////////////////////

Colosseum::Colosseum(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Colosseum created with invalid size " << nRows << " by "
             << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = NULL;
    m_nVillains = 0;
    m_turns = 0;
    for (int r = 1; r <= m_rows; r++)
        for (int c = 1; c <= m_cols; c++)
            setCellStatus(r, c, EMPTY);
}

Colosseum::~Colosseum()
{
    for (int k = 0; k < m_nVillains; k++)
        delete m_villains[k];
    delete m_player;
}

int Colosseum::rows() const
{
    return m_rows;
}

int Colosseum::cols() const
{
    return m_cols;
}

Player* Colosseum::player() const
{
    return m_player;
}

int Colosseum::villainCount() const
{
    return m_nVillains;
}

int Colosseum::getCellStatus(int r, int c) const
{
    checkPos(r, c);
    return m_grid[r-1][c-1];
}

int Colosseum::numberOfVillainsAt(int r, int c) const
{
    int count = 0;
    for (int k = 0; k < m_nVillains; k++)
    {
        Villain* vp = m_villains[k];
        if (vp->row() == r  &&  vp->col() == c)
            count++;
    }
    return count;
}

void Colosseum::display(string msg) const
{
    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;

      // Fill displayGrid with dots (empty)
    for (r = 1; r <= rows(); r++)
        for (c = 1; c <= cols(); c++)
            displayGrid[r-1][c-1] = (getCellStatus(r,c) == EMPTY ? '.' : '*');

        // Indicate each villain's position
    for (int k = 0; k < m_nVillains; k++)
    {
        const Villain* vp = m_villains[k];
        char& gridChar = displayGrid[vp->row()-1][vp->col()-1];
        switch (gridChar)
        {
          case '.':  gridChar = 'V'; break;
          case 'V':  gridChar = '2'; break;
          case '9':  break;
          default:   gridChar++; break;  // '2' through '8'
        }
    }

      // Indicate player's position
    if (m_player != NULL)
        displayGrid[m_player->row()-1][m_player->col()-1] = (m_player->isDead() ? 'X' : '@');

      // Draw the grid
    clearScreen();
    for (r = 1; r <= rows(); r++)
    {
        for (c = 1; c <= cols(); c++)
            cout << displayGrid[r-1][c-1];
        cout << endl;
    }
    cout << endl;

      // Write message, villain, and player info
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << villainCount() << " villains remaining." << endl;
    if (m_player == NULL)
        cout << "There is no player!" << endl;
    else if (m_player->isDead())
        cout << "The player is dead." << endl;
    cout << m_turns << " turns have been taken." << endl;
}

void Colosseum::setCellStatus(int r, int c, int status)
{
    checkPos(r, c);
    m_grid[r-1][c-1] = status;
}

bool Colosseum::addVillain(int r, int c)
{
    if (! isPosInBounds(r, c))
        return false;
    if (m_player != NULL  &&  m_player->row() == r  &&  m_player->col() == c)
        return false;
    if (m_nVillains == MAXVILLAINS)
        return false;
    m_villains[m_nVillains] = new Villain(this, r, c);
    m_nVillains++;
    return true;
}

bool Colosseum::addPlayer(int r, int c)
{
    if (m_player != NULL  ||  ! isPosInBounds(r, c))
        return false;
    if (numberOfVillainsAt(r, c) > 0)
        return false;
    m_player = new Player(this, r, c);
    return true;
}

void Colosseum::moveVillains()
{
      // Move all villains
    for (int k = m_nVillains-1; k >= 0; k--)
    {
        Villain* vp = m_villains[k];
        vp->move();

        if (m_player != NULL  &&
                vp->row() == m_player->row()  &&  vp->col() == m_player->col())
            m_player->setDead();

    }


      // Another turn has been taken
    m_turns++;
}

void Colosseum::pushAllVillains(int r, int c, int dir)
{
    // pushes all villains at [r,c] in the given direction
    // Note that if r,c isn't a valid location, this will
    //      do nothing.  We could instead have checked
    //      to see if it's in range, and skipped the loop
    //      in that case.
    //	(or we could do bounds checking before calling, etc)
    for (int k = m_nVillains-1; k >= 0; k--)
    {
        Villain* vp = m_villains[k];
        if( vp->row() == r && vp->col() == c )
        {
            vp->push( dir );
            if (vp->isDead())
            {
                delete vp;

                // The order of Villain pointers in the m_villains array is
                // irrelevant, so it's easiest to move the last pointer to
                // replace the one pointing to the now-deleted villain.  Since
                // we are traversing the array from last to first, we know this
                // last pointer does not point to a dead villain.

                m_villains[k] = m_villains[m_nVillains-1];
                m_nVillains--;
            }
        }
    }
}


bool Colosseum::isPosInBounds(int r, int c) const
{
    return (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols);
}

void Colosseum::checkPos(int r, int c) const
{
    if (!isPosInBounds(r, c))
    {
        cout << "***** " << "Invalid colosseum position (" << r << ","
             << c << ")" << endl;
        exit(1);
    }
}

///////////////////////////////////////////////////////////////////////////
//  Game implementation
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nVillains)
{
    if (nVillains < 0  ||  nVillains > MAXVILLAINS)
    {
        cout << "***** Game created with invalid number of villains:  "
             << nVillains << endl;
        exit(1);
    }
    int nEmpty = rows * cols - nVillains - 1;  // 1 for Player
    if (nEmpty < 0)
    {
        cout << "***** Game created with a " << rows << " by "
             << cols << " colosseum, which is too small too hold a player and "
             << nVillains << " villains!" << endl;
        exit(1);
    }

      // Create Colosseum
    m_colosseum = new Colosseum(rows, cols);

      // Add player
    int rPlayer;
    int cPlayer;
    do
    {
        rPlayer = randInt(1, rows);
        cPlayer = randInt(1, cols);
    } while (m_colosseum->getCellStatus(rPlayer, cPlayer) != EMPTY);
    m_colosseum->addPlayer(rPlayer, cPlayer);

      // Populate with villains
    while (nVillains > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        if (r == rPlayer && c == cPlayer)
            continue;
        m_colosseum->addVillain(r, c);
        nVillains--;
    }
}

Game::~Game()
{
    delete m_colosseum;
}

string Game::takePlayerTurn()
{
    for (;;)
    {
        cout << "Your move (n/e/s/w/p or nothing): ";
        string playerMove;
        getline(cin, playerMove);

        Player* player = m_colosseum->player();
        int dir;

        if (playerMove.size() == 0)
        {
            if (recommendMove(*m_colosseum, player->row(), player->col(), dir))
                return player->move(dir);
            else
                return player->push();
        }
        else if (playerMove.size() == 1)
        {
            if (tolower(playerMove[0]) == 'p')
                return player->push();
            else if (charToDir(playerMove[0], dir))
                return player->move(dir);
        }
        cout << "Player move must be nothing, or 1 character n/e/s/w/p." << endl;
    }
}

void Game::play()
{
    m_colosseum->display("");
    while ( ! m_colosseum->player()->isDead()  &&  m_colosseum->villainCount() > 0)
    {
        string msg = takePlayerTurn();
        Player* player = m_colosseum->player();
        if (player->isDead())
            break;
        m_colosseum->moveVillains();
        m_colosseum->display(msg);
    }
    if (m_colosseum->player()->isDead())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementation
///////////////////////////////////////////////////////////////////////////

  // Return a uniformly distributed random int from lowest to highest, inclusive
int randInt(int lowest, int highest)
{
    if (highest < lowest)
        swap(highest, lowest);
    return lowest + (rand() % (highest - lowest + 1));
}

bool charToDir(char ch, int& dir)
{
    switch (tolower(ch))
    {
      default:  return false;
      case 'n': dir = NORTH; break;
      case 'e': dir = EAST;  break;
      case 's': dir = SOUTH; break;
      case 'w': dir = WEST;  break;
    }
    return true;
}

  // Return false without changing anything if moving one step from (r,c)
  // in the indicated direction would hit a run off the edge of the colosseum.
  // Otherwise, update r and c to the position resulting from the move and
  // return true.
bool attemptMove(const Colosseum& colosseum, int dir, int& r, int& c)
{
    int rnew = r;
    int cnew = c;
    switch (dir)
    {
      case NORTH:  if (r <= 1)        return false; else rnew--; break;
      case EAST:   if (c >= colosseum.cols()) return false; else cnew++; break;
      case SOUTH:  if (r >= colosseum.rows()) return false; else rnew++; break;
      case WEST:   if (c <= 1)        return false; else cnew--; break;
    }
    r = rnew;
    c = cnew;
    return true;
}

  // Recommend a move for a player at (r,c):  A false return means the
  // recommendation is that the player should push and not move;
  // otherwise, this function sets bestDir to the recommended direction
  // to move and retus true.
bool recommendMove(const Colosseum& colosseum, int r, int c, int& bestDir)
{
      // How dangerous is it to stand?
    int standDanger = computeDanger(colosseum, r, c);

      // if it's not safe, see if moving is safer
    if (standDanger > 0)
    {
        int bestMoveDanger = standDanger;
        int bestMoveDir = NORTH;  // arbitrary initialization

          // check the four directions to see if any move is
          // better than standing, and if so, record the best
        for (int dir = 0; dir < NUMDIRS; dir++)
        {
            int rnew = r;
            int cnew = c;
            if (attemptMove(colosseum, dir, rnew, cnew))
            {
                int danger = computeDanger(colosseum, rnew, cnew);
                if (danger < bestMoveDanger)
                {
                    bestMoveDanger = danger;
                    bestMoveDir = dir;
                }
            }
        }

          // if moving is better than standing, recommend move
        if (bestMoveDanger < standDanger)
        {
            bestDir = bestMoveDir;
            return true;
        }
    }
    return false;  // recommend standing
}

int computeDanger(const Colosseum& colosseum, int r, int c)
{
      // Our measure of danger will be the number of villains that might move
      // to position r,c.  If a villain is at that position, it is fatal,
      // so a large value is returned.

    if (colosseum.numberOfVillainsAt(r,c) > 0)
        return MAXVILLAINS+1;

    int danger = 0;
    if (r > 1)
        danger += colosseum.numberOfVillainsAt(r-1,c);
    if (r < colosseum.rows())
        danger += colosseum.numberOfVillainsAt(r+1,c);
    if (c > 1)
        danger += colosseum.numberOfVillainsAt(r,c-1);
    if (c < colosseum.cols())
        danger += colosseum.numberOfVillainsAt(r,c+1);

    return danger;
}

// DO NOT MODIFY THE CODE BETWEEN HERE AND THE MAIN ROUTINE
#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                                                        &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <cstring>

void clearScreen()
{
    static const char* term = getenv("TERM");
    static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
    if (term == NULL  ||  strcmp(term, "dumb") == 0)
        cout << endl;
     else
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
}

#endif

///////////////////////////////////////////////////////////////////////////
// main()
///////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
      // Initialize the random number generator
    srand(static_cast<unsigned int>(time(0)));

      // Create a game
      // Use this instead to create a mini-game:
      Game g(3, 5, 2);
      //Game g(10, 12, 40);

      // Play the game
    g.play();
}
