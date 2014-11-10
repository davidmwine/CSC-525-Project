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

#include <stdlib.h>
#include "GL/glut.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <time.h>
using namespace std;

GLfloat picture[159][318][3];

void openImg()
{
	ifstream file; //Create an ifstream to run through file
	file.open("C:\\TEMP\\centipede.bin", ios::in | ios::binary);
	float readNum;
	int i = 0; //Counter to determine where to place values in array
	int j = 0;
	int color = 0;
	if (file.is_open())
	{//If file is open run loop
		while (file >> readNum)
		{ //Loop through all numbers in file
			if (color == 3)
			{
				color = 0;
				j++; //Increment counter
			}
			if (j == 318)
			{
				j = 0;
				i++;
			}
			//std::cout << "i is: " << i << ", j is: " << j << std::endl;
			picture[i][j][color] = readNum; //Insert pixel
			color++;
		}
		file.close(); //Close file
	}
	else
	{//If file wasn't open display error message
		cout << "File not found. Make sure the file centipede.txt is in TEMP.\n";
		exit(0);
	}
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

void displayShip(GLubyte shipStip[], int startX = -10, int startY = -190)
{
	glEnable(GL_POLYGON_STIPPLE);
	glPolygonStipple(shipStip); //Draw polygon with pattern
	glBegin(GL_POLYGON);
		glColor3f(0, 1, 0); //Draw ship
		glVertex2i(startX, startY);
		glVertex2i(startX + 20, startY);
		glVertex2i(startX + 30, startY + 30);
		glVertex2i(startX + 10, startY + 50);
		glVertex2i(startX - 10, startY + 30);
	glEnd();
	glDisable(GL_POLYGON_STIPPLE);//Draw ship cockpit
	glBegin(GL_POLYGON);
		glColor3f(0, 0, 0);
		glVertex2i(startX + 3, startY + 25);
		glVertex2i(startX + 10, startY + 35);
		glVertex2i(startX + 17, startY + 25);
	glEnd();
	glBegin(GL_POLYGON); //Draw ships side guns
		glVertex2i(startX - 2, startY + 20);
		glVertex2i(startX - 2, startY + 30);
		glVertex2i(startX, startY + 35);
		glVertex2i(startX + 2, startY + 30);
		glVertex2i(startX + 2, startY + 20);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2i(startX + 22, startY + 20);
		glVertex2i(startX + 22, startY + 30);
		glVertex2i(startX + 20, startY + 35);
		glVertex2i(startX + 18, startY + 30);
		glVertex2i(startX + 18, startY + 20);
	glEnd();
}

void displayBullets()
{
	glLineWidth(1);
	glBegin(GL_LINES); //Draw ships bullets
	glColor3f(0, 1, 0);
	for (int i = -135; i < 300; i += 10)
	{
		glVertex2i(0, i);
		glVertex2i(0, i + 5);
	}
	glEnd();
}

void displayImg(GLfloat picture[159][318][3])
{
	glRasterPos2i(-159, -80); //Starting point of centipede image
	glDrawPixels(318, 159, GL_RGB, GL_FLOAT, picture); //Draw centipede image
}
void displayMushroom(GLubyte mushroompattern[])
{
	for (int ang = 30; ang < 390; ang += 40) //Go through degrees
	{
		float rad = ang * 3.14 / 180; //Convert to radians
		float y = sinf(rad) * 70; //Find x and y based on radians and multiply by a constant
		float x = cosf(rad) * 70;
		glColor3f(1, 0.5, 1); //Set color for bitmap
		glRasterPos2f(-x - 16, y - 180); //Position next mushroom for circle around ship
		glBitmap(32, 32, 0.0, 0.0, 0.0, 0.0, mushroompattern); //Place the mushroom
	}
	glColor3f(1, 0.5, 1); //Draw mushrooms
	glRasterPos2i(180, -130);
	glBitmap(32, 32, 0.0, 0.0, 0.0, 0.0, mushroompattern);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glColor3f(1, 0.5, 1);
	glRasterPos2i(-140, 160);
	glBitmap(32, 32, 0.0, 0.0, 0.0, 0.0, mushroompattern);


	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glColor3f(1, 0.5, 1);
	glRasterPos2i(-179, -160);
	glBitmap(32, 32, 0.0, 0.0, 0.0, 0.0, mushroompattern);


	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glColor3f(1, 0.5, 1);
	glRasterPos2i(190, 30);
	glBitmap(32, 32, 0.0, 0.0, 0.0, 0.0, mushroompattern);


	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glColor3f(1, 0.5, 1);
	glRasterPos2i(100, -110);
	glBitmap(32, 32, 0.0, 0.0, 0.0, 0.0, mushroompattern);



	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glColor3f(1, 0.5, 1);
	glRasterPos2i(130, 140);
	glBitmap(32, 32, 0.0, 0.0, 0.0, 0.0, mushroompattern);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glColor3f(1, 0.5, 1);
	glRasterPos2i(-220, -20);
	glBitmap(32, 32, 0.0, 0.0, 0.0, 0.0, mushroompattern);
}

void displayCentipede(double d, double pi, size_t countup)
{
	//Draw Circle 
	srand(time(NULL));//Seeding Random Value for Legs
	countup = 0; //Counter for draw events

	/*Draws Circle for Centipede Body to Rotate around*/
	for (d = 0.1 * pi; d <= 2 * pi; d += 0.004) //Incrementing slowly around Radius
	{

		//Variables for each particular centipede body part
		int rotate = 0;
		int combo = 0;
		int randleg = rand() % 20 + 5;
		float distort = pi / 8;
		if (countup % 64 == 0)
		{
			double xnewrad = GetX(0, 320, d, pi); // SET SECOND ENTRY FOR BIGGER CENTIPEDE RADIUS
			double ynewrad = GetY(0, 320, d, pi); //Gets starting x and y for next body segment center

			for (double t = 0; t <= 2 * pi; t += 0.004) //Incrementing slowly around Radius
			{
				glLineWidth(5);
				glColor3f(0, 0.75, 0);	// change drawing color to green
				glEnable(GL_LINE_STIPPLE);
				glLineStipple(1, 0xEEEE);
				glBegin(GL_LINES);	// use the default point size: 1

					/*SET  SECOND ENTRY FOR BIGGER CENTIPEDE BODY*/
					glVertex2f(xnewrad, ynewrad); //Draws Body segments of centipede
					glVertex2f(GetX(xnewrad, 40, t, pi), GetY(ynewrad, 40, t, pi));//Calls Circle function
				glEnd();
				glDisable(GL_LINE_STIPPLE);

				/******************LEG PART OF CYCLE******************************************************/
				/*Number Theory Here needs work*/
				if (t >= (distort + (5 * pi / 8)) && t <= (distort + (5 * pi / 8) + 0.006) && d < 1.85 * pi) //Draws leg segments of centipede
				{
					distort = distort + pi / 16;
					glLineWidth(6);
					glColor3f(0, 0.8, 0);	// change drawing color to green

					glBegin(GL_LINES);	// use the default point size: 1			
						if (t > pi)
						{
							glVertex2f(GetX(xnewrad, 40, distort, pi), GetY(ynewrad, 40, distort, pi));//Calls Circle function
							glVertex2f(GetX(xnewrad, 40, distort, pi) - 20, GetY(ynewrad, 40, distort, pi) + 20);
						}
						else
						{
							glVertex2f(GetX(xnewrad, 40, distort, pi), GetY(ynewrad, 40, distort, pi));//Calls Circle function
							glVertex2f(GetX(xnewrad, 40, distort, pi) + 20, GetY(ynewrad, 40, distort, pi) - 20);
						}
					glEnd();

				}

				rotate = rotate + 7;

			}


		}
		countup++;
		combo++;
		rotate = rotate - 90;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	}
	/*---------------------------------------------------Draw eyes for centipe-----------------------------------------------------------------------*/
	for (int ang = 0; ang < 360; ang += 1) //Go through degrees
	{
		glPointSize(1);
		glColor3f(1, 1, 1);
		float rad = ang * 3.14 / 180; //Convert to radians
		float y = sinf(rad) * 10; //Find x and y based on radians and multiply by a constant
		float x = cosf(rad) * 10;
		glBegin(GL_LINES); //Draw eyes
			glVertex2f(5, 340);
			glVertex2f(x + 5, y + 340);
			glVertex2f(5, 300);
			glVertex2f(x + 5, y + 300);
		glEnd();
	}
	for (int ang = 0; ang < 360; ang += 1) //Go through degrees
	{
		glColor3f(0, 0, 0);
		float rad = ang * 3.14 / 180; //Convert to radians
		float y = sinf(rad) * 5; //Find x and y based on radians and multiply by a constant
		float x = cosf(rad) * 5;
		glBegin(GL_LINES); //Draw pupils of eyes
			glVertex2f(5, 340);
			glVertex2f(x + 5, y + 340);
			glVertex2f(5, 300);
			glVertex2f(x + 5, y + 300);
		glEnd();
	}
}

void displayText(GLfloat xcor1, GLfloat ycor1)
{
	glColor3f(1, 0, 0);
	glRasterPos2i(xcor1, ycor1);
	int g = xcor1;
	GLint yposition = ycor1;
	bool flag = true;
	string strt = "CLICK TO START";
	for (int i = 0; i < strt.length(); i++)
	{ //Display click to start text

		if (yposition <= ycor1 + 10) //Make characters alternate up and down
		{
			yposition = yposition + 7;
			glRasterPos2i(g, yposition);

		}
		else
		{
			yposition = yposition - 7;
			glRasterPos2i(g, yposition);

		}

		g = g + 21;
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, strt[i]);
	}
}