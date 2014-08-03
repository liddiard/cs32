#include <algorithm>
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

void Piece::fallOne()
{
	int current_x = this->getXPosition();
	int current_y = this->getYPosition();
	this->setPosition(current_x, current_y + 1);
}

void Piece::shift(Tank& tank, bool right)
{
	if (right)
	{
		if (m_x + PIECE_WIDTH + 1 <= tank.getXOffset() + tank.getWidth())
			m_x++;
	} 
	else // (left)
	{
		if (m_x - 1 >= tank.getXOffset())
			m_x--;
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
