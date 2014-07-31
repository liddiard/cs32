#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED

#include "globals.h"

class Screen;

class Piece
{
public:
	Piece();
	void displayAtPosition(int x_offset, int y_offset);
	// void fallOne();
	// void fallAll();
	// void rotateClockwise();
	// void rotateCounterclockwise();

private:
	char m_piece[PIECE_HEIGHT][PIECE_WIDTH];
	Screen * m_screen;
};

class IPiece : public Piece
{
public:
	IPiece(Screen * scr, char piece[][]);
};

#endif