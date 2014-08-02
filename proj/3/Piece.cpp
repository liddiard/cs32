#include "Piece.h"
#include "UserInterface.h"

Piece::Piece(Screen * scr) : m_screen(scr), m_falling(true), 
							 m_y(-1) // sentinel value to indicate that the piece has just appeared and is not coming from a previous position
{}

const int Piece::getXPosition() { return m_x; }
const int Piece::getYPosition() { return m_y; }

void Piece::setXPosition(int x) { m_x = x; }
void Piece::setYPosition(int y) { m_y = y; }

void Piece::displayAtPosition(int x_offset, int y_offset)
{
    // for each character in each row, move the cursor there and print the character
    for (int i = 0; i < PIECE_HEIGHT; i++) // for each row of the piece
    {
    	for (int j = 0; j < PIECE_WIDTH; j++) // for each column of the piece row
    	{
    		m_screen->gotoXY(x_offset + j, y_offset + i); 
    		if (m_piece[i][j] != ' ') // don't print the character if it's blank (a space char)
    			m_screen->printChar(m_piece[i][j]);
	    		if (m_y != -1)
	    		{
	    			// erase previous position's character to prevent "ghosting"
		    		m_screen->gotoXY(x_offset + j, y_offset + i -1); 
		    		m_screen->printChar(' ');
	    		}
    	}
    }
    // update the Pieces's internal representation of where it is
    this->setXPosition(x_offset);
    this->setYPosition(y_offset);
}

void Piece::fallOne()
{
	int current_x = this->getXPosition();
	int current_y = this->getYPosition();
	this->displayAtPosition(current_x, current_y + 1);
}

char Piece::m_piece[PIECE_HEIGHT][PIECE_WIDTH] = {
	{' ', ' ', ' ', ' '},
	{'#', '#', '#', '#'},
	{' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' '}
};

IPiece::IPiece(Screen * scr) : Piece(scr) {}