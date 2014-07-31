#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED

#include "globals.h"

class Screen;

class Piece
{
public:
	Piece(Screen * scr);
	const int getXPosition();
	const int getYPosition();
	void setXPosition(int x);
	void setYPosition(int y);
	void displayAtPosition(int x_offset, int y_offset);
	// void fallOne();
	// void fallAll();
	// void rotateClockwise();
	// void rotateCounterclockwise();

private:
	Screen * m_screen;
	static char m_piece[PIECE_HEIGHT][PIECE_WIDTH];
	int m_x; // offset of piece's top left corner 
	int m_y; // from the top left corner of the game
	bool m_falling; // is the piece falling or at rest?
};

class IPiece : public Piece
{
public:
	IPiece(Screen * scr);
};

#endif