#include "Piece.h"
#include "globals.h"
#include "UserInterface.h"

Piece::Piece(Screen * scr) : m_screen(scr), m_falling(true), 
							 m_x(PIECE_INITIAL_X), m_y(PIECE_INITIAL_Y)
{}

const int Piece::getXPosition() { return m_x; }
const int Piece::getYPosition() { return m_y; }

void Piece::setPosition(int x, int y) { m_x = x; m_y = y; }

void Piece::display()
{
    // for each character in each row, move the cursor there and print the character
    for (int i = 0; i < PIECE_HEIGHT; i++) // for each row of the piece
    {
    	for (int j = 0; j < PIECE_WIDTH; j++) // for each column of the piece row
    	{
    		m_screen->gotoXY(m_x + j + 1, m_y + i); // +1 for tank wall width
    		if (m_piece[i][j] != ' ') // don't print the character if it's blank (a space char)
    			m_screen->printChar(m_piece[i][j]);
    	}
    }
}

void Piece::fallOne()
{
	int current_x = this->getXPosition();
	int current_y = this->getYPosition();
	this->setPosition(current_x, current_y + 1);
}

char Piece::m_piece[PIECE_HEIGHT][PIECE_WIDTH] = {
	{' ', ' ', ' ', ' '},
	{'#', '#', '#', '#'},
	{' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' '}
};

IPiece::IPiece(Screen * scr) : Piece(scr) {}