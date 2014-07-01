#include "Player.h"
#include "Colosseum.h"
int main()
{
    Colosseum c(10, 20);
    Player p(&c, 2, 3);
    Villain r(&c, 1, 1);
}
