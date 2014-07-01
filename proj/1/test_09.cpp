#include "Colosseum.h"
#include "Player.h"
#include "History.h"
#include "globals.h"
int main()
{
    Colosseum c(2, 2);
    c.addPlayer(1, 1);
    c.player()->move(EAST);
    c.player()->push();
    c.player()->move(SOUTH);
    c.history().display();
}
