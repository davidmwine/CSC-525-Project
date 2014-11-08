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
#include <vector>
#include <stdlib.h>
#include "GL/glut.h"
using namespace std;

class Segments
{
private:
	int r = 32;
	double pi = 3.1415;
	int width, height = 32;
	int minxlocation, minylocation;
public:
	Segments(int x, int y) {
		minxlocation = x;
		minylocation = y;
		draw(minxlocation, minylocation);


	}
	void draw(int x, int y)
	{
		glLineWidth(6);
		glColor3f(0, 0.8, 0);
		glBegin(GL_LINES);	// use the default point size: 1
		for (double t = 0; t <= 2 * pi; t += 0.04) //Incrementing slowly around Radius
		{
			glVertex2f(GetX(minxlocation, r, t, pi), GetY(minylocation, r, t, pi));//Calls Circle function

		}
		glEnd();
	}
	int GetX(int rx, int r, double d, double pi) //Gets an x point from the center of a circle
	{

		int x;

		x = rx + (sin(d))*r;

		return x;
	}
	int GetY(int ry, int r, double d, double pi) //Gets a y point from the center of a circle
	{
		int y;
		y = ry + (sin(d + (pi / 2)))*r;
		return y;
	}


};



class Centipede {
private:
	vector<Segments*> body;
	//Centipede(){}
	//Segments *Y;
public:

	Centipede(){};
	void initdraw(int startx = -100, int startyc = 100)
	{
		int decreaseX = startx;
		int decreaseY = startyc;
		for (int i = 0; i < 8; i++)
		{
			Segments *Y = new Segments(decreaseX, decreaseY);
			body.push_back(Y);
			decreaseX = decreaseX - 16;
			//decreaseY = decreaseY - 16;
		}

	}




};

