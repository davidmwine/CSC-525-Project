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
#include <math.h>
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <sstream>
#include "events.h"
#include "game.h"
using namespace std;

//***********************************************************************************

void splashScreen()
{
	displayShip(shipStip);
	displayBullets();
	displayImg(picture);
	displayMushroom(mushroompattern);
	displayCentipede(d, pi, countup);
	displayText(xcor1, ycor1);
}

void playGame()
{
	Grid *g = new Grid();
	Ship *s = new Ship(shipStip, shipX, shipY);
}

//***********************************************************************************

//***********************************************************************************
void myDisplayCallback()
{
	//glutFullScreen();
	glClear(GL_COLOR_BUFFER_BIT);	// draw the background

	splashScreen();
	glFlush(); // flush out the buffer contents
}

void myDisplayCallback2()
{
	glClear(GL_COLOR_BUFFER_BIT);
	playGame();
	glFlush();
}

void backgroundCallback()
{

	glClear(GL_COLOR_BUFFER_BIT);	// draw the background

	glFlush(); // flush out the buffer contents

}

void myInit()
{
	glClearColor(0, 0, 0, 0);			// specify a background clor: white 
	gluOrtho2D(-375, 375, -375, 375);  // specify a viewing area
}
void myInit2()
{
	glClearColor(0.75, 0, 1, 0);			// specify a background clor: white 
	gluOrtho2D(-300, 300, -300, 300);  // specify a viewing area
}
void backgroundmyInit()
{
	glClearColor(0, 0, 0, 0);			// specify a background color: white 
	gluOrtho2D(-400, 400, -300, 300);  // specify a viewing area
}

//***********************************************************************************
void main(int argc, char ** argv)
{
	glutInit(& argc, argv);

 glutInitWindowSize(750, 750);				// specify a window size
 glutInitWindowPosition(0, 0);			// specify a window position
 splashId = glutCreateWindow("CENTIPEDE");	// create a titled window
 openImg();
 myInit();									// setting up

 glutDisplayFunc(myDisplayCallback);		// register a callback
 glutMouseFunc(startGame);
 glutMainLoop();							// get into an infinite loop
 //glutLeaveGameMode();
}
