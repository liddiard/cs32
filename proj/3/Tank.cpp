#include <vector>
#include <iostream> // TODO: remove
#include "Tank.h"
#include "UserInterface.h"
#include "Piece.h"
#include "globals.h"
#include "randPieceType.h"

Tank::Tank(int width, int height) : m_width(width), m_height(height),
									m_x_offset(TANK_X), m_y_offset(TANK_Y)
{
	for (int i = 0; i < m_height; i++)
	{
		std::vector<char> tmp;
		for (int j = 0; j < m_width; j++)
			tmp.push_back(' ');
		m_raster.push_back(tmp);
	}
}

const int Tank::getWidth() { return m_width; }
const int Tank::getHeight() { return m_height; }
const int Tank::getXOffset() { return m_x_offset; }
const int Tank::getYOffset() { return m_y_offset; }

Piece * Tank::getPiece() // get the currently falling piece
{
	return m_cur_piece;
}

void Tank::setNextPiece(Screen& screen)
{
	m_next_piece = this->getRandomPiece(screen);
}

void Tank::setPiece(Piece * piece)
{
	m_cur_piece = piece;
}

const char Tank::getCharAt(int row, int col)
{
	return m_raster[row][col];
}

void Tank::setCharAt(int row, int col, char ch)
{
	m_raster[row][col] = ch;
}

bool Tank::loadNextPiece(Screen& screen) // returns true if piece was added successfully; false if there's no room
{
	delete m_cur_piece;
	m_cur_piece = m_next_piece;
	m_next_piece = this->getRandomPiece(screen);
	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		for (int j = 0; j < PIECE_WIDTH; j++)
		{
			if (m_raster[m_cur_piece->getYPosition()+i][m_cur_piece->getXPosition()+j] != ' ')
				return false; // piece overlaps; game over
		}
	}
	return true;
}

Piece * Tank::getRandomPiece(Screen& screen)
{
	switch(randPieceType())
	{
		case PIECE_I:
			return new IPiece(screen);
		case PIECE_L:
			return new LPiece(screen);
		case PIECE_J:
			return new JPiece(screen);
		case PIECE_T:
			return new TPiece(screen);
		case PIECE_O:
			return new OPiece(screen);
		case PIECE_S:
			return new SPiece(screen);
		case PIECE_Z:
			return new ZPiece(screen);
    	case PIECE_VAPOR:
    		return new VaporPiece(screen);
    	case PIECE_FOAM:
    		return new FoamPiece(screen);
    	case PIECE_CRAZY:
    		return new CrazyPiece(screen);
	}
}

bool Tank::pieceCanFall(Piece * piece) // does the piece have room below it to continue falling?
{
    return (piece->inHorizontalBounds(*this, piece->getYPosition()+piece->bottomBound()+1) &&
			!piece->overlapsFragment(*this, piece->getYPosition()+1, piece->getXPosition()));
}

bool Tank::changeToNewPiece(Screen& screen) // returns true if piece successfully added; false if no room in tank
{
    m_cur_piece->rasterize(*this);
    this->clearFilledRows();
    if (!this->loadNextPiece(screen))
    	return false;
    return true;
}

bool Tank::fall(Screen& screen)
{
    if (this->pieceCanFall(m_cur_piece))
    {
        this->getPiece()->fallOne();
        return true;
    }
    return this->changeToNewPiece(screen);
}

bool Tank::fallAll(Screen& screen)
{
	while (this->pieceCanFall(m_cur_piece))
	{
		this->getPiece()->fallOne();
	}
    return this->changeToNewPiece(screen);
}

int Tank::clearFilledRows()
{
	int filled = 0;
	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++)
		{
			if (m_raster[i][j] == ' ')
				break; // we've hit a blank; this row isn't filled
			else if (j == m_width - 1) // final iteration of the loop
			{
				this->removeRow(i);
				filled++;
			}
		}
	}
	return filled;
}

void Tank::removeRow(int r)
{
	for (int i = r - 1 ; i > 0; i--) // traverse the array backwards (up) starting from the row above the one to fill
	{
		for (int j = 0; j < m_width; j++)
		{
			m_raster[i+1][j] = m_raster[i][j];
		}
	}
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
