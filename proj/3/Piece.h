#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED

#include "globals.h"

class Piece
{
	public:
		Piece();
		virtual void displayAtPosition(int x, int y);
		virtual void fallOne();
		virtual void fallAll();
		virtual void rotateClockwise();
		virtual void rotateCounterclockwise();

	private:
		char m_piece[PIECE_HEIGHT][PIECE_WIDTH];
};

#endif