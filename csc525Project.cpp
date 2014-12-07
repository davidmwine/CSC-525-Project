/*==================================================================================================
PROGRAMMER:				David Wine, Joshua Stark
COURSE:					CSC 525/625
FOLDER IDS:				Wine123, Stark1222
CONTRIBUTIONS:			David Wine (50%): A large portion of event driven programming,
							display screens, pixel maps, ship, bomb, grid, splash screen
							contributions same as homework 3 (largely unchanged), a lot of
							the code in main display callback for game.
						Joshua Stark (50%): Centipede, mushrooms, bitmaps, collision detection,
							3D stroke text, splash screen contributions same as homework 3 
							(largely unchanged)
MODIFIED BY:			N/A
LAST MODIFIED DATE:	    Dec. 6, 2014
DESCRIPTION:			Advertisement/Demo for game called Centipede Bomber. Starts with splash
							screen, click to go into main window. Main window starts with
							instructions for how to play, then click again to actually play game.
							Once playing game there is a center window with actual gameplay, and
							side panels with a message stating game is a demo. There is also a
							game lost screen, a next level screen, a win screen, and a pause screen
NOTES:					Speed will work differently on some computers (mainly those with dedicated
							graphics cards it seems), centipede movement down can seem a little
							jagged or disconnected
FILES:					csc525Project.cpp, splash.cpp, game.cpp, events.cpp,csc525Project.h,
						splash.h, game.h, events.h, variables.h
IDE/COMPILER:			MicroSoft Visual Studio 2013
INSTRUCTION FOR COMPILATION AND EXECUTION:
1.		Double click on termProject.sln	to OPEN the project
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
Bomb *b = new Bomb(); //Create bomb (but don't display yet)
Ship *s = new Ship(shipStip, shipX, shipY); //Display ship at current mouse position within bounding area
Centipede *Cent = new Centipede(segmentNum); //Display centipede at starting location
mushrooms *mushmush = new mushrooms(winNum + 2); //Display mushrooms
double angle = 5*pi / 6; //Starting angle for text screens
double textrotate = 0;//Starting Angle for Text

//***********************************************************************************

void splashScreen()
{ //Display splash screen
	displayShip(shipStip);
	displayBullets();
	displayImg(picture);
	displayMushroom(mushroompattern);
	displayCentipede(d, pi);
	displayText(xcor1, ycor1);
}

void playGame()
{
	if (reset) //If game needing reset
	{
		glClearColor(0.15, 0.15, 0.15, 1); //Set background color to grey
		g = new Grid(-288, -288, 288, 288); //Display grid
		Cent = new Centipede(segmentNum); //Display centipede (segments change based on level)
		mushmush = new mushrooms(winNum + 2); //Recreate mushrooms (change based on level)
		b = new Bomb(); //Recreate bomb
		bombShot = false; //Reset booleans
		hit = false;
		blown = false;
		explode = 0;
		reset = false;
	}
	//lost = true;
	if (!lost && !won && started && !paused)
	{ //If game is currently running
		g->drawGrid(); //Display grid
		mushmush->create(); //Create mushrooms
		if (bombShot) //If there is a bomb on field, display it
		{
			if (explode == 0) //If not exploding draw it at current location
			{
				b->drawBomb(bombX, bombY);
			}
			if (b->checkHit(Cent) || b->checkHit2(mushmush)) hit = true; //If a collision set hit
			if (!hit) bombY+=2; //Change bombs location every time to simulate movement if not hit
		}
		s->drawShip(shipStip, shipX, shipY); //Display ships current location
		bool popped = false; //Set a couple booleans
		bool mushDest = false;
		if (!blown || !Cent->blowUp(bombX, bombY)) //If centipede not being blown up let it continue
		{
			Cent->DrawTrue();
			Cent->move(mushmush->getField());
		}
		else if (blown && Cent->blowUp(bombX, bombY)) //Otherwise flash centipede while being popped
		{
			Cent->DrawFalse();
			popped = true;
		}
		if (blown && mushmush->blowUp(bombX, bombY)) //If exploding a mushroom set boolean
		{
			mushDest = true;
		}

		if (explode < 100 && blown) //If still exploding, continue explosion
		{
			b->explosion();
			explode++;
		}
		else if (blown) //Otherwise explosion finished
		{
			blown = false; // Explosion done
			explode = 0;
			if (popped) //If centipede popped remove segment from end
			{
				Cent->popSeg();
			}
			if (mushDest) //If mushroom destroyed set visibility value
			{
				mushmush->destroyMush(bombX, bombY);
			}
			if (b->killed(shipX, shipY)) //If ship blown up lost game
			{
				lost = true;
			}
		}
		if (s->centColl(Cent)) lost = true; //If ship hit centipede lost game
		if (Cent->getSize() == 0) //If centipede gone won level
		{
			won = true;
			winNum++; //Move to next level
		}
	}
	else if (!started) //If not started display instruction
	{
		displayInstr();
	}
	else if (lost) //If lost display lose screen and reset level and segments
	{
		winNum = 0;
		segmentNum = 50;
		displayLoss(skullPic, angle);
	}
	else if (won == true) //If won level display level up screen or win screen
	{
		if (winNum <= 3) //If still levels to go display level up screen
		{
			displayWin(levelPic, angle);
		}
		else //Otherwise display win screen
		{
			displayFinish(winPic, angle);
		}
	}
	else if (paused == true) //If paused display pause screen
	{
		displayPause();
	}
	
}

//***********************************************************************************

//***********************************************************************************
void myDisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT);	// draw the background
	splashScreen();
	glutSwapBuffers(); // flush out the buffer contents
}

void myDisplayCallback2()
{
	glClear(GL_COLOR_BUFFER_BIT);
	playGame();
	glutSwapBuffers();
	//sleep(2); //Uncomment and change value if speed is too fast
	glutPostRedisplay(); //Run program in infinite loop
}

void backgroundCallback()
{

	glClear(GL_COLOR_BUFFER_BIT);	// draw the background
	//SPINNING TEXT ON THE LEFT
	//X Y and Z POSITIONS
	if (started)
	{
		glColor3f(0, 1, 0); //Set color
		float x2 = -700; //Set start location
		float y2 = 575;
		float z2 = -150;
		string s2 = "ONLY A DEMO";
		glMatrixMode(GL_MODELVIEW);
		for (int i = 0; i < s2.length(); i++)//Loop Down Y Positions, rotate translate
		{
			glPushMatrix();

			glTranslatef(x2, y2, z2);
			glRotatef(textrotate, 0, 1.0, 0.2);
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, s2[i]);
			y2 -= 120;

			glPopMatrix();


		}


		//SPINNING TEXT ON THE RIGHT
		//X Y and Z POSITIONS
		float x1 = 700;//Set Start Location
		float y1 = 575;
		float z1 = -150;
		string s1 = "ONLY A DEMO";
		glMatrixMode(GL_MODELVIEW);
		for (int i = 0; i < s2.length(); i++)//Loop Down Y Positions, rotate translate
		{
			glPushMatrix();

			glTranslatef(x1, y1, z1);
			glRotatef(textrotate, 0, 1.0, 0.1);
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, s1[i]);
			y1 -= 120;

			glPopMatrix();


		}

		//INCREMENT ANGLE
		textrotate += 0.1;
	}
	glutSwapBuffers(); // flush out the buffer contents
	glutPostRedisplay(); //Infinite LOOP


}

void myInit()
{
	glClearColor(0, 0, 0, 0);			// specify a background clor: white 
	gluOrtho2D(-375, 375, -375, 375);  // specify a viewing area
}
void myInit2()
{
	glClearColor(0.15, 0.15, 0.15, 1);
	gluOrtho2D(-300, 300, -300, 300);  // specify a viewing area
}
void backgroundmyInit()
{
	glMatrixMode(GL_PROJECTION);
	glClearColor(0, 0, 0, 0);			// specify a background color: white 
	glViewport(0, 0, 750, 750);
	glLoadIdentity();

	//LARGE VIEWING AREA TO SHRINK TEXT
	glOrtho(-800, 800, -700, 700, -800, 800);  // specify a viewing are
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0, 0, 200, 0, 0, 0, 0, 1, 0);
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
}