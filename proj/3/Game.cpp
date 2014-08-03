#include "globals.h"
#include "Game.h"
#include "Tank.h"
#include "UserInterface.h"
#include "Piece.h"
#include <string>
#include <algorithm>
#include <iostream> // TODO: remove
#include <stdlib.h>


Game::Game(int width, int height)
 : m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_level(6), // TODO: return to default 1 for prod
   m_tank(width, height)
{
}

void Game::play()
{
    m_tank.display(m_screen);
    Piece * ipiece = new IPiece(m_screen);
    m_tank.setPiece(ipiece);
    m_tank.setNextPiece(m_screen);
    displayStatus();  //  score, rows left, level
    displayPrompt("Press the Enter key to begin playing Imitris!");
    waitForEnter();  // [in UserInterface.h]

    for(;;)
    {
        if ( ! playOneLevel())
            break;
        displayPrompt("Good job!  Press the Enter key to start next level!");
        waitForEnter();
        m_level++;
    }
    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
}

void Game::displayPrompt(std::string s)     
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);   // overwrites previous text
    m_screen.refresh();
}

void Game::displayStatus()
{
}

bool Game::playOneLevel()
{
    double tic_interval = std::max(1000-(100*(m_level-1)), 100); // milliseconds between successive falls
    double last_fall = getMsecSinceStart();
    m_tank.redrawContents(m_screen);
    while(1)
    {
        char key;
        if (getCharIfAny(key))
        {
            switch(key)
            {
                case ARROW_UP:
                    m_tank.getPiece()->rotateClockwise(m_tank);
                case ARROW_DOWN:
                    m_tank.fall(m_screen);
                    last_fall = getMsecSinceStart();
                    break;
                case ARROW_LEFT:
                    m_tank.getPiece()->shift(m_tank, false);
                    break;
                case ARROW_RIGHT:
                    m_tank.getPiece()->shift(m_tank, true);
                    break;
                case ' ':
                    m_tank.fallAll(m_screen);
                    break;
                case 'q': case 'Q':
                    exit(0); // TODO: fix this. it's being weird in the terminal
                    break;
            }
            m_tank.redrawContents(m_screen);
        }
        if (getMsecSinceStart() > last_fall + tic_interval)
        {
            m_tank.fall(m_screen);
            last_fall = getMsecSinceStart();
        }
    }
    return false;  // [Replace this with the code to play a level.]
}
