#include "globals.h"
#include "Game.h"
#include "Tank.h"
#include "UserInterface.h"
#include "Piece.h"
#include <string>
#include <algorithm>
#include <iostream> // TODO: remove


Game::Game(int width, int height)
 : m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_level(5),
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
    unsigned long cur_tic = 1;
    double tic_interval = std::max(1000-(100*(m_level-1)), 100); // time between successive falls
    double level_start_time = getMsecSinceStart();
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
                    break;
                case ARROW_LEFT:
                    m_tank.getPiece()->shift(m_tank, false);
                    break;
                case ARROW_RIGHT:
                    m_tank.getPiece()->shift(m_tank, true);
                    break;
            }
            m_tank.redrawContents(m_screen);
        }
        if (getMsecSinceStart() - level_start_time > tic_interval * cur_tic)
        {
            if (m_tank.pieceCanFall())
                m_tank.getPiece()->fallOne();
            else
            {
                m_tank.rasterizePiece();
                m_tank.clearFilledRows();
                m_tank.getNextPiece(m_screen);
            }
            m_tank.redrawContents(m_screen);
            cur_tic++;
        }
    }
    return false;  // [Replace this with the code to play a level.]
}
