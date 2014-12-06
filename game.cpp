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

void displaylevel(GLfloat pixMap[][450][4])
{
	glEnable(GL_BLEND); //Use GL_BLEND to enable transparency of bomb
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glRasterPos2i(-210, -100); //Starting point of centipede image
	glDrawPixels(450, 238, GL_RGBA, GL_FLOAT, pixMap); //Draw centipede image
	glDisable(GL_BLEND);
}

void displayYouWon(GLfloat pixMap[][300][4])
{
	glEnable(GL_BLEND); //Use GL_BLEND to enable transparency of bomb
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glRasterPos2i(-140, -100); //Starting point of centipede image
	glDrawPixels(300, 230, GL_RGBA, GL_FLOAT, pixMap); //Draw centipede image
	glDisable(GL_BLEND);
}

void displayLoss(GLfloat pixMap[][300][4], double angleStart)
{
	glClearColor(0.0, 0.0, 0.2, 1);
	string gameOver = "YOU LOSE";
	string tryAgain = "CLICK TO TRY AGAIN";
	glColor3f(1, 0, 0);
	double currDeg = angleStart;
	double x1 = cos(currDeg) * 200;
	double y1 = sin(currDeg) * 200;
	for (int i = 0; i < gameOver.length(); i++)
	{ //Display click to start text
		glRasterPos2i(x1, y1);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, gameOver[i]);
		currDeg = currDeg - (((2 * pi / 3) / (gameOver.length() - 1)));
		x1 = cos(currDeg) * 200;
		y1 = sin(currDeg) * 200;
	}

	currDeg = angleStart + pi/3;
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

void displayWin(GLfloat pixMap[][450][4])
{
	glClearColor(0.0, 0.0, 0.2, 1);
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
	displaylevel(pixMap);
}

void displayFinish(GLfloat pixMap[][300][4])
{
	glClearColor(0.0, 0.0, 0.2, 1);
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
	displayYouWon(pixMap);
}

void displayInstr()
{
	glClearColor(0, 0, 0, 1);
	string keyShort = "Keyboard Shortcuts";
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
	string shrtCut[3] = { pause, quit, reset };
	string instrArr[7] = { shipM, bombS, bombS2, bombK, bombK2, centK, winC };
	int currRastX = -275;
	int currRastY = 260;
	glColor3f(0, 1, 0);
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
	currRastX = -250;
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
	currRastX = -50;
	currRastY = -150;
	glColor3f(0, 1, 0);
	for (int loc = 0; loc < click.length(); loc++) //Draw heading text
	{
		glRasterPos2i(currRastX, currRastY);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, click[loc]);
		currRastX += 15;
	}
	currRastX = -30;
	currRastY = -200;
	glColor3f(0, 1, 0);
	for (int loc = 0; loc < to.length(); loc++) //Draw heading text
	{
		glRasterPos2i(currRastX, currRastY);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, to[loc]);
		currRastX += 15;
	}
	currRastX = -80;
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
{
	glColor3f(0, 1, 0);
	string game = "GAME";
	string pause = "PAUSED";
	string pSpace = "PRESS SPACEBAR TO CONTINUE";
	int currRastX = -25;
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
	currRastX = -190;
	currRastY = -200;
	for (int loc = 0; loc < pSpace.length(); loc++)
	{
		glRasterPos2i(currRastX, currRastY);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, pSpace[loc]);
		currRastX += 15;
	}
}