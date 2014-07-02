#include <string>
#include <iostream>
#include <stdlib.h>
#include "globals.h"
#include "Game.h"
#include "Colosseum.h"
#include "Player.h"

Game::Game(int rows, int cols, int nVillains)
{
    if (nVillains < 0  ||  nVillains > MAXVILLAINS)
    {
        std::cout << "***** Game created with invalid number of villains:  "
             << nVillains << std::endl;
        exit(1);
    }
    int nEmpty = rows * cols - nVillains - 1;  // 1 for Player
    if (nEmpty < 0)
    {
        std::cout << "***** Game created with a " << rows << " by "
             << cols << " colosseum, which is too small too hold a player and "
             << nVillains << " villains!" << std::endl;
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

std::string Game::takePlayerTurn()
{
    for (;;)
    {
        std::cout << "Your move (n/e/s/w/h/p or nothing): ";
        std::string playerMove;
        getline(std::cin, playerMove);

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
            if (tolower(playerMove[0]) == 'h')
            {
                m_colosseum->history().display();
                std::cin.ignore(10000,'\n');
                m_colosseum->display("");
                std::cout << "Press enter to continue.";
                continue;
            }
            else if (tolower(playerMove[0]) == 'p')
                return player->push();
            else if (charToDir(playerMove[0], dir))
                return player->move(dir);
        }
        std::cout << "Player move must be nothing, or 1 character n/e/s/w/h/p." << std::endl;
    }
}

void Game::play()
{
    m_colosseum->display("");
    while ( ! m_colosseum->player()->isDead()  &&  m_colosseum->villainCount() > 0)
    {
        std::string msg = takePlayerTurn();
        Player* player = m_colosseum->player();
        if (player->isDead())
            break;
        m_colosseum->moveVillains();
        m_colosseum->display(msg);
    }
    if (m_colosseum->player()->isDead())
        std::cout << "You lose." << std::endl;
    else
        std::cout << "You win." << std::endl;
}
