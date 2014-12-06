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
Centipede *Cent = new Centipede(segmentNum);
mushrooms *mushmush = new mushrooms(winNum + 2);
double angle = 5*pi / 6;
int textTimer = 0;

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
	//won = true;
	//winNum = 4;
	if (reset)
	{
		glClearColor(0.15, 0.15, 0.15, 1);
		g = new Grid(-288, -288, 288, 288); //Display grid
		Cent = new Centipede(segmentNum);
		mushmush = new mushrooms(winNum + 2);
		b = new Bomb();
		bombShot = false;
		hit = false;
		blown = false;
		explode = 0;
		reset = false;
	}
	//lost = true;
	if (!lost && !won && started && !paused)
	{
		g->drawGrid(); //Display grid
		mushmush->create();
		if (bombShot) //If there is a bomb on field, display it
		{
			if (explode == 0)
			{
				b->drawBomb(bombX, bombY);
			}
			if (b->checkHit(Cent) || b->checkHit2(mushmush)) hit = true;
			if (!hit) bombY+=2; //Change bombs location every time to simulate movement
		}
		s->drawShip(shipStip, shipX, shipY); //Display ships current location
		bool popped = false;
		bool mushDest = false;
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
		if (blown && mushmush->blowUp(bombX, bombY))
		{
			mushDest = true;
		}

		if (explode < 100 && blown)
		{
			b->explosion();
			explode++;
		}
		else if (blown)
		{
			blown = false;
			explode = 0;
			if (popped)
			{
				Cent->popSeg();
			}
			if (mushDest)
			{
				mushmush->destroyMush(bombX, bombY);
			}
			if (b->killed(shipX, shipY))
			{
				lost = true;
			}
		}
		if (s->centColl(Cent)) lost = true;
		if (Cent->getSize() == 0)
		{
			won = true;
			winNum++;
		}
	}
	else if (!started)
	{
		displayInstr();
	}
	else if (lost)
	{
		winNum = 0;
		segmentNum = 50;
		displayLoss(skullPic, angle);
	}
	else if (won == true)
	{
		if (winNum <= 3)
		{
			displayWin(levelPic);
		}
		else
		{
			//winNum = 0;
			//segmentNum = 50;
			displayFinish(winPic);
		}
	}
	else if (paused == true)
	{
		displayPause();
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
	//timer = clock();
	glClear(GL_COLOR_BUFFER_BIT);
	playGame();
	//glFlush();
	glutSwapBuffers();
	Sleep(2);
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
	glClearColor(0.15, 0.15, 0.15, 1);
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
	openImg4();
	openImg5();
	openImg6();
	myInit();								// setting up
	srand(time(NULL));
	glutDisplayFunc(myDisplayCallback);		// register a callback
	glutMouseFunc(startGame);
	glutMainLoop();							// get into an infinite loop
	//glutLeaveGameMode();
}