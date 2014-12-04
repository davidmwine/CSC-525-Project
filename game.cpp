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
#include <GL/glut.h>				// include GLUT library
#include <iostream>
#include <math.h>
#include <string>
#include <fstream>
#include <stdio.h>
const double pi = 3.14159265;
using namespace std;

void displaySkull(GLfloat pixMap[][300][4])
{
	glEnable(GL_BLEND); //Use GL_BLEND to enable transparency of bomb
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glRasterPos2i(-145, -145); //Starting point of centipede image
	glDrawPixels(300, 300, GL_RGBA, GL_FLOAT, pixMap); //Draw centipede image
	glDisable(GL_BLEND);
}

void displayLoss(GLfloat pixMap[][300][4])
{
	string gameOver = "YOU LOSE";
	string tryAgain = "CLICK TO TRY AGAIN";
	glColor3f(1, 0, 0);
	double currDeg = 5*pi/6;
	double x1 = cos(currDeg)*200;
	double y1 = sin(currDeg)*200;
	for (int i = 0; i < gameOver.length(); i++)
	{ //Display click to start text
		glRasterPos2i(x1, y1);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, gameOver[i]);
		currDeg = currDeg - (((2*pi/3) / (gameOver.length()-1)));
		x1 = cos(currDeg) * 200;
		y1 = sin(currDeg) * 200;
	}

	currDeg = 7 * pi / 6;
	x1 = cos(currDeg) * 200;
	y1 = sin(currDeg) * 200;

	for (int i = 0; i < tryAgain.length(); i++)
	{ //Display click to start text
		glRasterPos2i(x1, y1);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, tryAgain[i]);
		currDeg = currDeg + (((2 * pi / 3) / (tryAgain.length() - 1)));
		x1 = cos(currDeg) * 200;
		y1 = sin(currDeg) * 200;
	}
	displaySkull(pixMap);
}

void displayWin()
{
	string levelWon1 = "CLICK TO PLAY";
	string levelWon2 = "NEXT LEVEL";
	glColor3f(1, 0, 0);
	double currDeg = 5 * pi / 6;
	double x1 = cos(currDeg) * 200;
	double y1 = sin(currDeg) * 200;
	for (int i = 0; i < levelWon1.length(); i++)
	{ //Display click to start text
		glRasterPos2i(x1, y1);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, levelWon1[i]);
		currDeg = currDeg - (((2 * pi / 3) / (levelWon1.length() - 1)));
		x1 = cos(currDeg) * 200;
		y1 = sin(currDeg) * 200;
	}

	currDeg = 7 * pi / 6;
	x1 = cos(currDeg) * 200;
	y1 = sin(currDeg) * 200;

	for (int i = 0; i < levelWon2.length(); i++)
	{ //Display click to start text
		glRasterPos2i(x1, y1);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, levelWon2[i]);
		currDeg = currDeg + (((2 * pi / 3) / (levelWon2.length() - 1)));
		x1 = cos(currDeg) * 200;
		y1 = sin(currDeg) * 200;
	}
}

void displayFinish()
{
	string buyGame1 = "DON'T FORGET TO";
	string buyGame2 = "BUY OUR GAME";
	glColor3f(1, 0, 0);
	double currDeg = 5 * pi / 6;
	double x1 = cos(currDeg) * 200;
	double y1 = sin(currDeg) * 200;
	for (int i = 0; i < buyGame1.length(); i++)
	{ //Display click to start text
		glRasterPos2i(x1, y1);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buyGame1[i]);
		currDeg = currDeg - (((2 * pi / 3) / (buyGame1.length() - 1)));
		x1 = cos(currDeg) * 200;
		y1 = sin(currDeg) * 200;
	}

	currDeg = 7 * pi / 6;
	x1 = cos(currDeg) * 200;
	y1 = sin(currDeg) * 200;

	for (int i = 0; i < buyGame2.length(); i++)
	{ //Display click to start text
		glRasterPos2i(x1, y1);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buyGame2[i]);
		currDeg = currDeg + (((2 * pi / 3) / (buyGame2.length() - 1)));
		x1 = cos(currDeg) * 200;
		y1 = sin(currDeg) * 200;
	}
}