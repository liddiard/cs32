#include "globals.h"
#include "Game.h"
#include "Tank.h"
#include "UserInterface.h"
#include <string>


Game::Game(int width, int height)
 : m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_level(1),
   m_tank(TANK_WIDTH, TANK_HEIGHT)
{
}

void Game::play()
{
    m_tank.display(m_screen, TANK_X, TANK_Y);
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
    return false;  // [Replace this with the code to play a level.]
}
