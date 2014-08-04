#include <string>
#include <algorithm>
#include <iostream> // TODO: remove
#include <sstream>
#include "globals.h"
#include "Game.h"
#include "Tank.h"
#include "UserInterface.h"
#include "Piece.h"

Game::Game(int width, int height)
 : m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_level(0), 
   m_tank(width, height), m_score(0), m_rows_left(ROWS_PER_LEVEL_MULTIPLIER)
{
}

Screen * Game::getScreen() { return &m_screen; }

void Game::addToScore(int n) { m_score += n; }

void Game::setRowsLeft(int n) { m_rows_left = n; }

const int Game::getRowsLeft() { return m_rows_left; }

int Game::getLevel() { return m_level; }

void Game::incrementLevel()
{
    m_level++;
}

void Game::play()
{
    m_tank.display(m_screen);
    displayStatus();  //  score, rows left, level
    displayPrompt("Press the Enter key to begin playing Imitris!");
    waitForEnter();  // [in UserInterface.h]

    for(;;)
    {
        if ( ! playOneLevel())
            break;
        displayPrompt("Good job!  Press the Enter key to start next level!");
        waitForEnter();
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

std::string intToPaddedStr(int n, int length)
{
    std::stringstream ss;
    ss << n;
    std::string str = ss.str();
    while (str.size() < length)
        str = " " + str;
    return str;
}

void Game::displayStatus()
{
    // next piece
    m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y-1);
    m_screen.printString("Next piece:");
    if (m_tank.getNextPiece())
        m_tank.getNextPiece()->displayAt(NEXT_PIECE_X, NEXT_PIECE_Y);

    // score
    m_screen.gotoXY(SCORE_X, SCORE_Y);
    m_screen.printStringClearLine("Score:     ");
    m_screen.printString(intToPaddedStr(m_score, STATUS_NUM_WIDTH));

    // rows left
    m_screen.gotoXY(ROWS_LEFT_X, ROWS_LEFT_Y);
    m_screen.printStringClearLine("Rows left: ");
    m_screen.printString(intToPaddedStr(m_rows_left, STATUS_NUM_WIDTH));

    // level
    m_screen.gotoXY(LEVEL_X, LEVEL_Y);
    m_screen.printStringClearLine("Level:     ");
    m_screen.printString(intToPaddedStr(m_level, STATUS_NUM_WIDTH));
}

bool Game::playOneLevel()
{
    this->incrementLevel();
    this->setRowsLeft(ROWS_PER_LEVEL_MULTIPLIER*m_level);
    m_tank.removeContents();

    double tic_interval = std::max(1000-(100*(m_level-1)), 100); // milliseconds between successive falls
    double last_fall = getMsecSinceStart();

    Piece * piece = m_tank.getRandomPiece(m_screen);
    m_tank.setPiece(piece);
    m_tank.setNextPiece(m_screen);
    this->displayStatus();
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
                    if (!m_tank.fall(*this))
                        return false; 
                    if (m_rows_left < 1) return true;
                    last_fall = getMsecSinceStart();
                    break;
                case ARROW_LEFT:
                    m_tank.getPiece()->shift(m_tank, false);
                    break;
                case ARROW_RIGHT:
                    m_tank.getPiece()->shift(m_tank, true);
                    break;
                case ' ':
                    if (!m_tank.fallAll(*this))
                        return false;
                    if (m_rows_left < 1) return true;
                    break;
                case 'q': case 'Q':
                    return false;
            }
            m_tank.redrawContents(m_screen);
            this->displayStatus();
        }
        if (getMsecSinceStart() > last_fall + tic_interval)
        {
            if (!m_tank.fall(*this))
                return false;
            if (m_rows_left < 1) return true;
            m_tank.redrawContents(m_screen);
            this->displayStatus();
            last_fall = getMsecSinceStart();
        }
    }
    return false;  // [Replace this with the code to play a level.]
}
