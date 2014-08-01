#include "Tank.h"
#include "UserInterface.h"

Tank::Tank(int width, int height)
{
	m_width = width;
	m_height = height;
    m_x_offset = 0;
    m_y_offset = 0;
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

}
