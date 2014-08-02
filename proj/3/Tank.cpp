#include <vector>
#include "Tank.h"
#include "globals.h"
#include "UserInterface.h"
#include "Piece.h"

Tank::Tank(int width, int height)
{
	m_width = width;
	m_height = height;
    m_x_offset = TANK_X;
    m_y_offset = TANK_Y;
}

std::vector<Piece *> * Tank::getPieces()
{
	return &m_pieces;
}


void Tank::addPiece(Piece * piece)
{
	m_pieces.push_back(piece);
}

void Tank::display(Screen& screen)
{
	const char TANK_CHAR = '@';
	// left wall of tank
	for (int i = m_y_offset; i < (m_y_offset + m_height); i++)
	{
		screen.gotoXY(m_x_offset, i);
		screen.printChar(TANK_CHAR);
	}
	// right wall of tank
	for (int i = m_y_offset; i < (m_y_offset + m_height); i++)
	{
		screen.gotoXY((m_x_offset + m_width + 1), i); // "+ 1" gives the tank a *capacity* of speficied width, 
													// as opposed to putting a wall at the specified width
		screen.printChar(TANK_CHAR);
	}
	// bottom of tank
	for (int i = m_x_offset; i < (m_x_offset + m_width + 2); i++) // "+ 2 " to width accounts for combined thickness 
															  // of the two walls (one column each)
	{
		screen.gotoXY(i, (m_y_offset + m_height));
		screen.printChar(TANK_CHAR);
	}
	screen.refresh();
}

void Tank::redrawContents(Screen& screen)
{
	// clear everything that's displayed the tank now
	for (int i = m_y_offset; i < (m_y_offset + m_height); i++) // for each row
	{
		for (int j = m_x_offset; j < (m_x_offset + m_width); j++)
		{
			screen.gotoXY(j + 1, i); // x-axis is offset by one because tank wall has a width of 1 column
			screen.printChar(' ');
		}
	}
	// print pieces in their current positions
	for (std::vector<Piece *>::iterator it = m_pieces.begin(); it != m_pieces.end(); ++it)
	{
		(*it)->display();
	}
	screen.refresh();
}
