#ifndef TANK_INCLUDED
#define TANK_INCLUDED

class Screen;

class Tank
{
  public:
    void display(Screen& screen, int x, int y);

  private:
    int m_width;
    int m_height;
};

#endif // TANK_INCLUDED
