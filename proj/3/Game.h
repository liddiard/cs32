#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Tank.h"
#include "UserInterface.h"
#include <string>

class Screen;

class Game
{
  public:
    Game(int width, int height);
    void play();
    bool playOneLevel();
    void displayPrompt(std::string s);
    void displayStatus();
    Screen * getScreen();
    void addToScore(int n);
    const int getRowsLeft();
    void setRowsLeft(int n);
    int getLevel();
    void incrementLevel();

  private:
    Tank    m_tank;
    Screen  m_screen;
    int     m_level;
    int     m_rows_left;
    int     m_score;
};

#endif // GAME_INCLUDED
