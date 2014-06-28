// main.cpp

#include <cstdlib>
#include "Game.h"
#include "Game.cpp"
#include "Colosseum.h"
#include "Colosseum.cpp"
#include "History.h"
#include "History.cpp"
#include "Player.h"
#include "Player.cpp"
#include "Villain.h"
#include "Villain.cpp"
#include "globals.h"
#include "utilities.cpp"

using namespace std;

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
