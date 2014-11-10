/*==================================================================================================
PROGRAMMER:			David Wine, Joshua Stark
COURSE:				CSC 525/625
MODIFIED BY:			N/A
LAST MODIFIED DATE:	Oct. 29, 2014
DESCRIPTION:			Advertisement/Demo for game called Centipede Bomber
NOTE:					N/A
FILES:					csc525Project.cpp, splash.cpp, splash.h, variables.h
IDE/COMPILER:			MicroSoft Visual Studio 2013
INSTRUCTION FOR COMPILATION AND EXECUTION:
1.		Double click on hwProject.sln	to OPEN the project
2.		Press Ctrl+F7					to COMPILE
3.		Press Ctrl+Shift+B				to BUILD (COMPILE+LINK)
4.		Press Ctrl+F5					to EXECUTE
==================================================================================================*/
#include "splash.h"
#include "variables.h"

class Grid
{
	private:
		int leftX;
		int botY;
		int rightX;
		int topY;
	public:
		Grid(int minX = -288, int minY = -288, int maxX = 288, int maxY = 288)
		{ //Fill 600x600 area with grid
			leftX = minX; //Variables for area grid covers
			botY = minY;
			rightX = maxX;
			topY = maxY;
			glColor3f(0, 0, 0);
			for (int x = leftX; x <= rightX; x += 24) //Grid squares are 24x24
			{
					glBegin(GL_LINES); //Draw vertical lines for grid
					glVertex2i(x, botY);
					glVertex2i(x, topY);
					glEnd();
			}
			for (int y = botY; y <= topY; y += 24)
			{
				glBegin(GL_LINES); //Draw horizontal lines for grid
				glVertex2i(leftX, y);
				glVertex2i(rightX, y);
				glEnd();
			}
		}

};

class Ship
{
	private:
		int xLoc;
		int yLoc;
		int width;
		int height;
		//Ship() { }
	public:
		Ship(GLubyte shipStip[], int x, int y)
		{
			//Ship should stay between -288 and 288 for x
			//And -288 and -192 for y
			int xLoc = x; //X and Y locations pass in as parameters
			int yLoc = y;
			displayShip(shipStip, xLoc, yLoc); //Display the ship starting at it's current location
			/*glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glColor3f(1, 0.5, 1);
			glRasterPos2i(-288, -288);
			glBitmap(32, 32, 0.0, 0.0, 0.0, 0.0, mushroompattern);*/
		}
};