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


void displayLoss()
{
	string gameOver = "YOULOSE";
	string tryAgain = "CLICK TO TRY AGAIN";
	glColor3f(1, 0, 0);
	double currDeg = pi;
	double x1 = cos(pi)*100;
	double y1 = sin(pi)*100;
	for (int i = 0; i < gameOver.length(); i++)
	{ //Display click to start text
		glRasterPos2i(x1, y1);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, gameOver[i]);
		currDeg = currDeg - (pi / (gameOver.length()-1));
		x1 = cos(currDeg) * 100;
		y1 = sin(currDeg) * 100;
	}
}