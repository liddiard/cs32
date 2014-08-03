#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED

#include "globals.h"

class Screen;
class Tank;

class Piece
{
public:
	Piece(Screen& scr);;
	const int getXPosition();
	const int getYPosition();
	void setPosition(int x, int y);
	void display();
	void fallOne();
	char getCharAt(int row, int col);
	virtual void shift(Tank& tank, bool right);
	virtual void rotateClockwise(Tank& tank);
	int rightBound();
	int leftBound();
	int topBound();
	int bottomBound();
	virtual void rasterize(Tank& tank);
	bool inVerticalBounds(Tank& tank, int pos);
	bool inHorizontalBounds(Tank& tank, int pos);

protected:
	char m_piece[PIECE_WIDTH][PIECE_HEIGHT];
	int m_x; // offset of piece's top left corner
	int m_y; // from the top left corner of the game

private:
	Screen * m_screen;
};

class IPiece : public Piece
{
public:
	IPiece(Screen& scr);
};

class LPiece : public Piece
{
public:
	LPiece(Screen& scr);
};

class JPiece : public Piece
{
public:
	JPiece(Screen& scr);
};

class TPiece : public Piece
{
public:
	TPiece(Screen& scr);
};

class OPiece : public Piece
{
public:
	OPiece(Screen& scr);
};

class SPiece : public Piece
{
public:
	SPiece(Screen& scr);
};

class ZPiece : public Piece
{
public:
	ZPiece(Screen& scr);
};

class VaporPiece : public Piece
{
public:
	VaporPiece(Screen& scr);
	virtual void rotateClockwise(Tank& tank);
	virtual void rasterize(Tank& tank);
};

class FoamPiece : public Piece
{
public:
	FoamPiece(Screen& scr);
	virtual void rotateClockwise(Tank& tank);
	virtual void rasterize(Tank& tank);
};

class CrazyPiece : public Piece
{
public:
	CrazyPiece(Screen& scr);
	virtual void shift(Tank& tank, bool right);
};

#endif
