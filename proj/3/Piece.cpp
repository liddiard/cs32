#include <algorithm>
#include <iostream> // TODO: remove
#include "Piece.h"
#include "Tank.h"
#include "globals.h"
#include "UserInterface.h"

Piece::Piece(Screen& scr) : m_screen(&scr), m_x(PIECE_INITIAL_X), m_y(PIECE_INITIAL_Y)
{}

const int Piece::getXPosition() { return m_x; }
const int Piece::getYPosition() { return m_y; }

void Piece::setPosition(int x, int y) { m_x = x; m_y = y; }

char Piece::getCharAt(int row, int col)
{
	return m_piece[row][col];
}

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

void Piece::rasterize(Tank& tank)
{
	const char FLATTENED_PIECE = '$';
	// for each character in each row, move the cursor there and set the character
	for (int i = 0; i < PIECE_HEIGHT; i++) // for each row of the piece
	{
		for (int j = 0; j < PIECE_WIDTH; j++) // for each column of the piece row
		{
			if (tank.getPiece()->getCharAt(i, j) != ' ') // don't set the character if it's blank (a space char)
			{
				tank.setCharAt(tank.getPiece()->getYPosition()+i, tank.getPiece()->getXPosition()+j, FLATTENED_PIECE);
			}
		}
	}
}

void Piece::fallOne()
{
	int current_x = this->getXPosition();
	int current_y = this->getYPosition();
	this->setPosition(current_x, current_y + 1);
}

bool Piece::inVerticalBounds(Tank& tank, int pos)
{
	return (pos >= tank.getXOffset() && pos < tank.getXOffset() + tank.getWidth());
}

bool Piece::inHorizontalBounds(Tank& tank, int pos)
{
	return (pos >= tank.getYOffset() && pos < tank.getYOffset() + tank.getHeight());
}

bool Piece::overlapsFragment(Tank& tank, int row, int col)
{
	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		for (int j = 0; j < PIECE_WIDTH; j++)
		{
			if (m_piece[i][j] != ' ' && tank.getCharAt(row+i, col+j) != ' ')
				return true;
		}
	}
	return false;
}

void Piece::shift(Tank& tank, bool right)
{
	if (right)
	{
		int right_bound = this->rightBound();
		if (this->inVerticalBounds(tank, m_x + right_bound + 1) &&
			!this->overlapsFragment(tank, m_y, m_x + 1))
			m_x++;
	}
	else // (left)
	{
		// find the left bound of the piece in its current orientation
		int left_bound = this->leftBound();
		if (this->inVerticalBounds(tank, m_x + left_bound - 1) &&
			!this->overlapsFragment(tank, m_y, m_x - 1))
			m_x--;
	}
}

void Piece::rotateClockwise(Tank& tank)
{
	// if piece is rotated 90 degrees, top and bottom become the sides, so we check
	// those bounds against the bounds of the tank and return if they'd fall outside
	if (!this->inVerticalBounds(tank, this->topBound() + m_x) ||
		!this->inVerticalBounds(tank, this->bottomBound() + m_x))
		return;
	// check the right side against the bottom of the tank
	if (!this->inHorizontalBounds(tank, this->rightBound() + m_y))
		return;
	char tmp[PIECE_WIDTH][PIECE_HEIGHT];
	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		for (int j = 0; j < PIECE_WIDTH; j++)
		{
			tmp[j][i] = m_piece[PIECE_WIDTH-i-1][j];
			if (tmp[j][i] != ' ' && tank.getCharAt(j + m_y, i + m_x) != ' ')
				return; // the rotated piece would overlap with a non-blank char in the tank; abort rotate
		}
	}
	for (int i = 0; i < PIECE_HEIGHT; i++)
		std::copy(tmp[i], tmp[i] + PIECE_WIDTH, m_piece[i]);
}

int Piece::rightBound()
{
	int right_bound = 0;
	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		for (int j = 0; j < PIECE_WIDTH; j++)
		{
			if (m_piece[i][j] != ' ' && j > right_bound)
				right_bound = j;
		}
	}
	return right_bound;
}

int Piece::leftBound()
{
	int left_bound = PIECE_WIDTH;
	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		for (int j = 0; j < PIECE_WIDTH; j++)
		{
			if (m_piece[i][j] != ' ' && j < left_bound)
				left_bound = j;
		}
	}
	return left_bound;
}

int Piece::topBound()
{
	int top_bound = PIECE_HEIGHT;
	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		for (int j = 0; j < PIECE_WIDTH; j++)
		{
			if (m_piece[i][j] != ' ' && i < top_bound)
				top_bound = i;
		}
	}
	return top_bound;
}

int Piece::bottomBound()
{
	int bottom_bound = 0;
	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		for (int j = 0; j < PIECE_WIDTH; j++)
		{
			if (m_piece[i][j] != ' ' && i > bottom_bound)
				bottom_bound = i;
		}
	}
	return bottom_bound;
}

void CrazyPiece::shift(Tank& tank, bool right)
{
	// CrazyPiece shifts the OPPOSITE direction of the key user presses
	// '!' on line below reverses directions
	if (!right)
	{
		int right_bound = this->rightBound();
		if (this->inVerticalBounds(tank, m_x + right_bound + 1) &&
			!this->overlapsFragment(tank, m_y, m_x + 1))
			m_x++;
	}
	else // (left)
	{
		int left_bound = this->leftBound();
		if (this->inVerticalBounds(tank, m_x + left_bound - 1) &&
			!this->overlapsFragment(tank, m_y, m_x - 1))
			m_x--;
	}
}

void FoamPiece::rotateClockwise(Tank& tank) {} // FoamPiece doesn't rotate

void VaporPiece::rotateClockwise(Tank& tank) {} // VaporPiece doesn't rotate

void VaporPiece::rasterize(Tank& tank) // VaporPiece blasts out surrounding chars
{
	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		for (int j = 0; j < PIECE_WIDTH; j++)
		{
			if (m_piece[i][j] != ' ')
			{
				tank.setCharAt(m_y+i, m_x+j, ' ');
				// clear any fragments within 2 blocks above and below piece
				const int BLAST_AREA = 4;
				int in_blast_radius[BLAST_AREA] = {m_y+i+1, m_y+i+2, m_y+i-1, m_y+i-2};
				for (int i = 0; i < BLAST_AREA; i++)
				{
					if (this->inHorizontalBounds(tank, in_blast_radius[i]))
						tank.setCharAt(in_blast_radius[i], m_x+j, ' ');
				}
			}
		}
	}
}

void fillWithFoam(Tank& tank, Piece& piece, int row, int col, int times)
{
	if (times > 3)
		return;
	if (piece.inVerticalBounds(tank, col) &&
		piece.inHorizontalBounds(tank, row) &&
		tank.getCharAt(row, col) == ' ')
		tank.setCharAt(row, col, '*');
	times++;
	fillWithFoam(tank, piece, row+1, col, times);
	fillWithFoam(tank, piece, row-1, col, times);
	fillWithFoam(tank, piece, row, col+1, times);
	fillWithFoam(tank, piece, row, col-1, times);
}

void FoamPiece::rasterize(Tank& tank) // FoamPiece fills surrounding areas with "foam"
{
	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		for (int j = 0; j < PIECE_WIDTH; j++)
		{
			if (m_piece[i][j] != ' ')
				fillWithFoam(tank, *this, m_y+i, m_x+j, 0);
		}
	}
}

IPiece::IPiece(Screen& scr) : Piece(scr) {
	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		char p[PIECE_HEIGHT][PIECE_WIDTH] = {
			{' ', ' ', ' ', ' '},
			{'#', '#', '#', '#'},
			{' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' '}
		};
		std::copy(p[i], p[i] + PIECE_WIDTH, m_piece[i]);
	}
}

LPiece::LPiece(Screen& scr) : Piece(scr) {
	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		char p[PIECE_HEIGHT][PIECE_WIDTH] = {
			{' ', ' ', ' ', ' '},
			{'#', '#', '#', ' '},
			{'#', ' ', ' ', ' '},
			{' ', ' ', ' ', ' '}
		};
		std::copy(p[i], p[i] + PIECE_WIDTH, m_piece[i]);
	}
}

JPiece::JPiece(Screen& scr) : Piece(scr) {
	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		char p[PIECE_HEIGHT][PIECE_WIDTH] = {
			{' ', ' ', ' ', ' '},
			{' ', '#', '#', '#'},
			{' ', ' ', ' ', '#'},
			{' ', ' ', ' ', ' '}
		};
		std::copy(p[i], p[i] + PIECE_WIDTH, m_piece[i]);
	}
}

TPiece::TPiece(Screen& scr) : Piece(scr) {
	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		char p[PIECE_HEIGHT][PIECE_WIDTH] = {
			{' ', '#', ' ', ' '},
			{'#', '#', '#', ' '},
			{' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' '}
		};
		std::copy(p[i], p[i] + PIECE_WIDTH, m_piece[i]);
	}
}

OPiece::OPiece(Screen& scr) : Piece(scr) {
	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		char p[PIECE_HEIGHT][PIECE_WIDTH] = {
			{'#', '#', ' ', ' '},
			{'#', '#', ' ', ' '},
			{' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' '}
		};
		std::copy(p[i], p[i] + PIECE_WIDTH, m_piece[i]);
	}
}

SPiece::SPiece(Screen& scr) : Piece(scr) {
	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		char p[PIECE_HEIGHT][PIECE_WIDTH] = {
			{' ', ' ', ' ', ' '},
			{' ', '#', '#', ' '},
			{'#', '#', ' ', ' '},
			{' ', ' ', ' ', ' '}
		};
		std::copy(p[i], p[i] + PIECE_WIDTH, m_piece[i]);
	}
}

ZPiece::ZPiece(Screen& scr) : Piece(scr) {
	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		char p[PIECE_HEIGHT][PIECE_WIDTH] = {
			{' ', ' ', ' ', ' '},
			{'#', '#', ' ', ' '},
			{' ', '#', '#', ' '},
			{' ', ' ', ' ', ' '}
		};
		std::copy(p[i], p[i] + PIECE_WIDTH, m_piece[i]);
	}
}

VaporPiece::VaporPiece(Screen& scr) : Piece(scr) {
	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		char p[PIECE_HEIGHT][PIECE_WIDTH] = {
			{' ', '#', '#', ' '},
			{' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' '}
		};
		std::copy(p[i], p[i] + PIECE_WIDTH, m_piece[i]);
	}
}

FoamPiece::FoamPiece(Screen& scr) : Piece(scr) {
	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		char p[PIECE_HEIGHT][PIECE_WIDTH] = {
			{' ', ' ', ' ', ' '},
			{' ', '#', ' ', ' '},
			{' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' '}
		};
		std::copy(p[i], p[i] + PIECE_WIDTH, m_piece[i]);
	}
}

CrazyPiece::CrazyPiece(Screen& scr) : Piece(scr) {
	for (int i = 0; i < PIECE_HEIGHT; i++)
	{
		char p[PIECE_HEIGHT][PIECE_WIDTH] = {
			{'#', ' ', ' ', '#'},
			{' ', '#', '#', ' '},
			{' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' '}
		};
		std::copy(p[i], p[i] + PIECE_WIDTH, m_piece[i]);
	}
}
