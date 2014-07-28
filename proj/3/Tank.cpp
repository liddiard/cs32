#include "Tank.h"
#include "UserInterface.h"

Tank::Tank(int width, int height)
{
	m_width = width;
	m_height = height;
}

void Tank::display(Screen& screen, int x_offset, int y_offset)
{
	const char TANK_CHAR = '@';
	// left wall of tank
	for (int i = y_offset; i < (y_offset + m_height); i++)
	{
		screen.gotoXY(x_offset, i);
		screen.printChar(TANK_CHAR);
	}
	// right wall of tank
	for (int i = y_offset; i < (y_offset + m_height); i++)
	{
		screen.gotoXY((x_offset + m_width + 1), i); // "+ 1" gives the tank a *capacity* of speficied width, 
													// as opposed to putting a wall at the specified width
		screen.printChar(TANK_CHAR);
	}
	// bottom of tank
	for (int i = x_offset; i < (x_offset + m_width + 2); i++) // "+ 2 " to width accounts for combined thickness 
															  // of the two walls (one column each)
	{
		screen.gotoXY(i, (y_offset + m_height));
		screen.printChar(TANK_CHAR);
	}
	screen.refresh();
}
