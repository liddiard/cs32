#ifndef TANK_INCLUDED
#define TANK_INCLUDED

#include <vector>
#include "globals.h"

class Screen;
class Game;
class Piece;

class Tank
{
  public:
  	Tank(int width, int height);
    const int getWidth();
    const int getHeight();
    const int getXOffset();
    const int getYOffset();
    void display(Screen& screen);
    void redrawContents(Screen& screen);
    Piece * getPiece(); // get currently falling piece
    Piece * getNextPiece();
    bool loadNextPiece(Game& game);
    void setNextPiece(Screen& screen);
    void setPiece(Piece * piece);
    Piece * getRandomPiece(Screen& screen);
    bool pieceCanFall(Piece * piece);
    const char getCharAt(int row, int col);
    void setCharAt(int row, int col, char ch);
    int clearFilledRows(Game& game);
    void removeRow(int r);
    bool fall(Game& game);
    bool fallAll(Game& game);
    bool changeToNewPiece(Game& game);

  private:
    int m_width;
    int m_height;
    int m_x_offset;
    int m_y_offset;
    std::vector<std::vector<char> > m_raster; // rasterized representation of characters inside the tank
                                             // which are static between fall tics
    Piece * m_cur_piece; // currently falling piece
    Piece * m_next_piece;
};

#endif // TANK_INCLUDED
