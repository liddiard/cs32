#include <vector>
#include "Tank.h"
#include "UserInterface.h"
#include "Piece.h"
#include "globals.h"

Tank::Tank(int width, int height) : m_width(width), m_height(height), m_x_offset(TANK_X), m_y_offset(TANK_Y)
{
	for (int i = 0; i < m_height; i++)
	{
		std::vector<char> tmp;
		for (int j = 0; j < m_width; j++)
			tmp.push_back(' ');
		m_raster.push_back(tmp);
	}
}

Piece * Tank::getPiece() // get the currently falling piece
{
	return m_cur_piece;
}

void Tank::setPiece(Piece * piece)
{
	m_cur_piece = piece;
}

void Tank::rasterizePiece()
{
	const char FLATTENED_PIECE = '$';
    // for each character in each row, move the cursor there and set the character
    for (int i = 0; i < PIECE_HEIGHT; i++) // for each row of the piece
    {
    	for (int j = 0; j < PIECE_WIDTH; j++) // for each column of the piece row
    	{
    		if (m_cur_piece->getCharAt(i, j) != ' ') // don't set the character if it's blank (a space char)
    			m_raster[m_cur_piece->getYPosition()+i][m_cur_piece->getXPosition()+j] = FLATTENED_PIECE;
    	}
    }
}

bool Tank::pieceCanFall() // does the piece have room below it to continue falling?
{
    for (int i = 0; i < PIECE_HEIGHT; i++) // for each row of the piece
    {
    	for (int j = 0; j < PIECE_WIDTH; j++) // for each column of the piece row
    	{
    		if (m_cur_piece->getCharAt(i, j) != ' ') // don't check below if there's no part of the piece here
    		{
    			if (m_cur_piece->getYPosition() + i + 1 < m_height && 
    				m_raster[m_cur_piece->getYPosition() + i][m_cur_piece->getXPosition() + j + 1] == ' ')
    				continue;
    			else
    				return false;
			}
    	}
    }
    return true;
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
			screen.printChar(m_raster[i][j]);
		}
	}
	m_cur_piece->display(); // print currently falling piece
	screen.refresh();
}
