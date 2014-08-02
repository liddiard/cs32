#ifndef TANK_INCLUDED
#define TANK_INCLUDED

#include <vector>
#include "globals.h"

class Screen;
class Piece;

class Tank
{
  public:
  	Tank(int width, int height);
    void display(Screen& screen);
    void redrawContents(Screen& screen);
    Piece * getPiece();
    void setPiece(Piece * piece);
    void rasterizePiece();

  private:
    int m_width;
    int m_height;
    int m_x_offset;
    int m_y_offset;
    std::vector<std::vector<char> > m_raster; // rasterized representation of characters inside the tank 
                                             // which are static between fall tics
    Piece * m_cur_piece; // currently falling piece
};

#endif // TANK_INCLUDED
