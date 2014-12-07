/*==================================================================================================
PROGRAMMER:				David Wine, Joshua Stark
COURSE:					CSC 525/625
FOLDER IDS:				Wine123, Stark1222
CONTRIBUTIONS:			David Wine (50%): A large portion of event driven programming,
							display screens, pixel maps, ship, bomb, grid, splash screen
							contributions same as homework 3 (largely unchanged), a lot of
							the code in main display callback for game.
						Joshua Stark (50%):	Centipede, mushrooms, bitmaps, collision detection,
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
#include <iostream>
#include <math.h>
#include <string>
#include <fstream>
#include <stdio.h>
const double pi = 3.14159265; //Pi used for rounded text
using namespace std;

void displaySkull(GLfloat pixMap[][300][4])
{
	glEnable(GL_BLEND); //Use GL_BLEND to enable transparency of skull
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glRasterPos2i(-145, -145); //Starting point of skull image
	glDrawPixels(300, 300, GL_RGBA, GL_FLOAT, pixMap); //Draw skull image
	glDisable(GL_BLEND);
}

void displaylevel(GLfloat pixMap[][450][4])
{
	glEnable(GL_BLEND); //Use GL_BLEND to enable transparency of level up
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glRasterPos2i(-210, -100); //Starting point of level up image
	glDrawPixels(450, 238, GL_RGBA, GL_FLOAT, pixMap); //Draw level up image
	glDisable(GL_BLEND);
}

void displayYouWon(GLfloat pixMap[][300][4])
{
	glEnable(GL_BLEND); //Use GL_BLEND to enable transparency of you won
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glRasterPos2i(-140, -100); //Starting point of you won image
	glDrawPixels(300, 230, GL_RGBA, GL_FLOAT, pixMap); //Draw you won image
	glDisable(GL_BLEND);
}

void displayLoss(GLfloat pixMap[][300][4], double angleStart)
{ //Display loss screen
	glClearColor(0.0, 0.0, 0.2, 1); //Dark blue background
	string gameOver = "YOU LOSE"; //Strings to display
	string tryAgain = "CLICK TO TRY AGAIN";
	glColor3f(1, 0, 0); //Red text
	double currDeg = angleStart; //Starting angle of first string
	double x1 = cos(currDeg) * 200; //Use angle to calculate location of first character
	double y1 = sin(currDeg) * 200;
	for (int i = 0; i < gameOver.length(); i++)
	{ //Display you lose text
		glRasterPos2i(x1, y1);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, gameOver[i]);
		currDeg = currDeg - (((2 * pi / 3) / (gameOver.length() - 1))); //Increment angle
		x1 = cos(currDeg) * 200; //Calculate new location
		y1 = sin(currDeg) * 200;
	}

	currDeg = angleStart + pi/3; //Starting angle of next string
	x1 = cos(currDeg) * 200; //Find next starting location
	y1 = sin(currDeg) * 200;

	for (int i = 0; i < tryAgain.length(); i++)
	{ //Display click to try again text
		glRasterPos2i(x1, y1);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, tryAgain[i]);
		currDeg = currDeg + (((2 * pi / 3) / (tryAgain.length() - 1))); //Calculate new angle and location
		x1 = cos(currDeg) * 200;
		y1 = sin(currDeg) * 200;
	}
	displaySkull(pixMap); //Display skull
}

void displayWin(GLfloat pixMap[][450][4], double angleStart)
{ //Display level up screen
	glClearColor(0.0, 0.0, 0.2, 1); //Blue background
	string levelWon1 = "CLICK TO PLAY"; //Strings to display
	string levelWon2 = "NEXT LEVEL";
	glColor3f(1, 0, 0); //Red text
	double currDeg = angleStart; //Starting location for first string
	double x1 = cos(currDeg) * 200;
	double y1 = sin(currDeg) * 200;
	for (int i = 0; i < levelWon1.length(); i++)
	{ //Display click to play text
		glRasterPos2i(x1, y1);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, levelWon1[i]);
		currDeg = currDeg - (((2 * pi / 3) / (levelWon1.length() - 1))); //Find new location
		x1 = cos(currDeg) * 200;
		y1 = sin(currDeg) * 200;
	}

	currDeg = angleStart + pi/3; //Starting location for second string
	x1 = cos(currDeg) * 200;
	y1 = sin(currDeg) * 200;

	for (int i = 0; i < levelWon2.length(); i++)
	{ //Display next level text
		glRasterPos2i(x1, y1);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, levelWon2[i]);
		currDeg = currDeg + (((2 * pi / 3) / (levelWon2.length() - 1))); //New location
		x1 = cos(currDeg) * 200;
		y1 = sin(currDeg) * 200;
	}
	displaylevel(pixMap); //Display level up image
}

void displayFinish(GLfloat pixMap[][300][4], double angleStart)
{ //Finished game screen
	glClearColor(0.0, 0.0, 0.2, 1); //Blue background
	string buyGame1 = "DON'T FORGET TO"; //Strings to display
	string buyGame2 = "BUY OUR GAME";
	glColor3f(1, 0, 0); //red text
	double currDeg = angleStart; //Starting location for first string
	double x1 = cos(currDeg) * 200;
	double y1 = sin(currDeg) * 200;
	for (int i = 0; i < buyGame1.length(); i++)
	{ //Display don't forget to buy text
		glRasterPos2i(x1, y1);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buyGame1[i]);
		currDeg = currDeg - (((2 * pi / 3) / (buyGame1.length() - 1))); //Next location
		x1 = cos(currDeg) * 200;
		y1 = sin(currDeg) * 200;
	}

	currDeg = angleStart + pi/3; //Starting location for second string
	x1 = cos(currDeg) * 200;
	y1 = sin(currDeg) * 200;

	for (int i = 0; i < buyGame2.length(); i++)
	{ //Display buy our game text
		glRasterPos2i(x1, y1);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buyGame2[i]);
		currDeg = currDeg + (((2 * pi / 3) / (buyGame2.length() - 1))); //Next location
		x1 = cos(currDeg) * 200;
		y1 = sin(currDeg) * 200;
	}
	displayYouWon(pixMap); //Display you won image
}

void displayInstr()
{ //Instructions screen
	glClearColor(0, 0, 0, 1); //Black background
	string keyShort = "Keyboard Shortcuts"; //Strings to display
	string pause = "Press spacebar to pause game";
	string quit = "Press ESC to exit game";
	string reset = "Press r to reset";
	string instrHead = "Instructions";
	string shipM = "Ship moves with mouse (constrained to bottom)";
	string bombS = "Click left mouse button to shoot bomb";
	string bombS2 = "Click left mouse button again to blow up bomb";
	string bombK = "Bombs can destroy mushrooms and a centipede segment";
	string bombK2 = "Be careful as bombs can also kill you";
	string centK = "When all segments are destroyed, proceed to next level";
	string winC = "There are 4 levels of increasing difficulty, good luck";
	string click = "CLICK";
	string to = "TO";
	string start = "PLAY GAME";
	string shrtCut[3] = { pause, quit, reset }; //Shortcuts array
	string instrArr[7] = { shipM, bombS, bombS2, bombK, bombK2, centK, winC }; //Instructions array
	int currRastX = -275; //Starting location
	int currRastY = 260;
	glColor3f(0, 1, 0); //Green text
	for (int loc = 0; loc < keyShort.length(); loc++) //Draw heading text
	{
		glRasterPos2i(currRastX, currRastY);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, keyShort[loc]);
		currRastX += 15;
	}
	currRastX = -250;
	currRastY = 230;
	for (int n = 0; n < 3; n++) //Loop through each instruction
	{
		for (int loc = 0; loc < shrtCut[n].length(); loc++)
		{ //Display current instruction
			glRasterPos2i(currRastX, currRastY);
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, shrtCut[n][loc]);
			currRastX += 10;
		}
		currRastX = -250; //Update raster position for next instruction
		currRastY -= 30;
	}
	currRastX = -275;
	currRastY = 110;
	glColor3f(0, 1, 0);
	for (int loc = 0; loc < instrHead.length(); loc++) //Draw heading text
	{
		glRasterPos2i(currRastX, currRastY);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, instrHead[loc]);
		currRastX += 15;
	}
	currRastX = -250; //Set new raster position
	currRastY = 80;
	for (int n = 0; n < 7; n++) //Loop through each instruction
	{
		for (int loc = 0; loc < instrArr[n].length(); loc++)
		{ //Display current instruction
			glRasterPos2i(currRastX, currRastY);
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, instrArr[n][loc]);
			currRastX += 10;
		}
		currRastX = -250; //Update raster position for next instruction
		currRastY -= 30;
	}
	currRastX = -50; //Set new raster position
	currRastY = -150;
	glColor3f(0, 1, 0);
	for (int loc = 0; loc < click.length(); loc++) //Draw heading text
	{
		glRasterPos2i(currRastX, currRastY);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, click[loc]);
		currRastX += 15;
	}
	currRastX = -30; //New raster position
	currRastY = -200;
	glColor3f(0, 1, 0);
	for (int loc = 0; loc < to.length(); loc++) //Draw heading text
	{
		glRasterPos2i(currRastX, currRastY);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, to[loc]);
		currRastX += 15;
	}
	currRastX = -80; //New raster position
	currRastY = -250;
	glColor3f(0, 1, 0);
	for (int loc = 0; loc < start.length(); loc++) //Draw heading text
	{
		glRasterPos2i(currRastX, currRastY);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, start[loc]);
		currRastX += 15;
	}
}

void displayPause()
{ //Pause screen
	glColor3f(0, 1, 0); //Green text
	string game = "GAME"; //Strings to display
	string pause = "PAUSED";
	string pSpace = "PRESS SPACEBAR TO CONTINUE";
	int currRastX = -25; //Game paused displayed around center of screen
	int currRastY = 15;
	for (int loc = 0; loc < game.length(); loc++)
	{
		glRasterPos2i(currRastX, currRastY);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, game[loc]);
		currRastX += 15;
	}
	currRastX = -40;
	currRastY -= 30;
	for (int loc = 0; loc < pause.length(); loc++)
	{
		glRasterPos2i(currRastX, currRastY);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, pause[loc]);
		currRastX += 15;
	}
	currRastX = -190; //Message to continue displayed near bottom
	currRastY = -200;
	for (int loc = 0; loc < pSpace.length(); loc++)
	{
		glRasterPos2i(currRastX, currRastY);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, pSpace[loc]);
		currRastX += 15;
	}
}