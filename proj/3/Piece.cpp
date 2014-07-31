#include "Piece.h"

Piece::Piece() : m_screen(scr) {}

void Piece::displayAtPosition(int x_offset, int y_offset)
{
    // for each character in each row, move the cursor there and print the character
    for (int i = 0; i < PIECE_HEIGHT; i++) // for each row of the piece
    {
    	for (int j = 0; j < PIECE_WIDTH; j++)
    	{
    		m_screen->gotoXY(x_offset + j, y_offset + i);
    		m_screen->printChar(m_piece[i][j]);
    	}
    }
}

IPiece::IPiece()
{
	m_piece = {
		{' ', ' ', ' ', ' '},
		{'#', '#', '#', '#'},
		{' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' '}
	}
}