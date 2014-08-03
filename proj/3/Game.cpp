#include "globals.h"
#include "Game.h"
#include "Tank.h"
#include "UserInterface.h"
#include "Piece.h"
#include <string>
#include <algorithm>
#include <iostream> // TODO: remove


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
    // next piece
    m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y-1);
    m_screen.printString("Next piece:");
    m_tank.getNextPiece()->displayAt(NEXT_PIECE_X, NEXT_PIECE_Y);

    // score
    m_screen.gotoXY(SCORE_X, SCORE_Y);
    m_screen.printString("Score:     ");

    // rows left
    m_screen.gotoXY(ROWS_LEFT_X, ROWS_LEFT_Y);
    m_screen.printString("Rows left: ");

    // level
    m_screen.gotoXY(LEVEL_X, LEVEL_Y);
    m_screen.printString("Level:     ");    
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
                    break;
                case ARROW_DOWN:
                    if (!m_tank.fall(m_screen))
                        return false;
                    last_fall = getMsecSinceStart();
                    break;
                case ARROW_LEFT:
                    m_tank.getPiece()->shift(m_tank, false);
                    break;
                case ARROW_RIGHT:
                    m_tank.getPiece()->shift(m_tank, true);
                    break;
                case ' ':
                    if (!m_tank.fallAll(m_screen))
                        return false;
                    break;
                case 'q': case 'Q':
                    return false;
            }
            m_tank.redrawContents(m_screen);
            this->displayStatus();
        }
        if (getMsecSinceStart() > last_fall + tic_interval)
        {
            if (!m_tank.fall(m_screen))
                return false;
            m_tank.redrawContents(m_screen);
            this->displayStatus();
            last_fall = getMsecSinceStart();
        }
    }
    return false;  // [Replace this with the code to play a level.]
}
