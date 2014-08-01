#ifndef TANK_INCLUDED
#define TANK_INCLUDED

#include <vector>

class Screen;
class Piece;

class Tank
{
  public:
  	Tank(int width, int height);
    void display(Screen& screen);
    void redrawContents(Screen& screen);

  private:
    int m_width;
    int m_height;
    int m_x_offset;
    int m_y_offset;
    std::vector<Piece *> pieces;
};

#endif // TANK_INCLUDED
