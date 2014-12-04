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
#include <windows.h>
#include "events.h"
#include "game.h"
using namespace std;
Grid *g = new Grid(-288, -288, 288, 288); //Display grid
Bomb *b = new Bomb();
Ship *s = new Ship(shipStip, shipX, shipY);
Centipede *Cent = new Centipede();
mushrooms *mushmush = new mushrooms();
int explode = 0;
bool lost = false;

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
	if (!lost)
	{
		g->drawGrid(); //Display grid
		mushmush->create();
		if (bombShot) //If there is a bomb on field, display it
		{
			if (explode == 0)
			{
				b->drawBomb(bombX, bombY);
			}
			if (b->checkHit(Cent)) hit = true;
			if (!hit) bombY++; //Change bombs location every time to simulate movement
		}
		s->drawShip(shipStip, shipX, shipY); //Display ships current location
		bool popped = false;
		if (!blown || !Cent->blowUp(bombX, bombY))
		{
			Cent->DrawTrue();
			Cent->move(mushmush->getField());
		}
		else if (blown && Cent->blowUp(bombX, bombY))
		{
			Cent->DrawFalse();
			popped = true;
		}
		glColor3f(1, 0.5, 1);
		glRasterPos2i(-47, 48);
		glBitmap(24, 24, 0.0, 0.0, 0.0, 0.0, mushroompattern2);

		if (explode < 100 && blown)
		{
			glEnable(GL_BLEND); //Use GL_BLEND to enable transparency of bomb
			glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
			glRasterPos2i(bombX - 24, bombY - 24); //Starting point of centipede image
			glDrawPixels(72, 72, GL_RGBA, GL_FLOAT, explosionPic); //Draw centipede image
			glDisable(GL_BLEND);
			explode++;
		}
		else
		{
			blown = false;
			explode = 0;
			if (popped)
			{
				Cent->popSeg();
			}
		}
		if (s->centColl(Cent)) lost = true;
	}
	else
	{
		displayLoss();
	}
	
}

//***********************************************************************************

//***********************************************************************************
void myDisplayCallback()
{
	//glutFullScreen();
	glClear(GL_COLOR_BUFFER_BIT);	// draw the background

	splashScreen();
	//glFlush();
	glutSwapBuffers(); // flush out the buffer contents
}

void myDisplayCallback2()
{
	glClear(GL_COLOR_BUFFER_BIT);
	playGame();
	//glFlush();
	glutSwapBuffers();
	Sleep(1);
	glutPostRedisplay(); //Run program in infinite loop
}

void backgroundCallback()
{

	glClear(GL_COLOR_BUFFER_BIT);	// draw the background

	glutSwapBuffers(); // flush out the buffer contents

}

void myInit()
{
	glClearColor(0, 0, 0, 0);			// specify a background clor: white 
	gluOrtho2D(-375, 375, -375, 375);  // specify a viewing area
}
void myInit2()
{
	glClearColor(0.0, 0.0, 0.5, 1);
	//glClearColor(0.75, 0, 1, 0);			// specify a background clor: white 
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
	glutInit(&argc, argv);

	glutInitWindowSize(750, 750);				// specify a window size
	glutInitWindowPosition(0, 0);			// specify a window position
	glutInitDisplayMode(GLUT_DOUBLE);  //DOUBLE BUFFER
	splashId = glutCreateWindow("CENTIPEDE");	// create a titled window
	openImg();
	openImg2();
	openImg3();
	myInit();									// setting up

	glutDisplayFunc(myDisplayCallback);		// register a callback
	glutMouseFunc(startGame);
	glutMainLoop();							// get into an infinite loop
	//glutLeaveGameMode();
}