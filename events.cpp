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

#include <iostream>
#include "csc525Project.h";
#include <time.h>
using namespace std;

int mouseButton;
int MainWidth;
int MainHeight;
int splashId;
int gameWidth;
int gameHeight;
int mainwindow;
int gamewindow;
int shipX = -10;
int shipY = -264;
float bombX;
float bombY;
bool bombShot = false;
bool hit = false;
bool blown = false;
int explode = 0;
int segmentNum = 50;
int winNum = 0;
bool lost = false;
bool won = false;
bool reset = false;
clock_t timer = 0;

void shipMove(int x, int y)
{
	int currX = (x - ((gameWidth / 2))); //Convert to world coordinate system
	int currY = ((gameHeight / 2)) - y;
	if (currX - 15 >= -288 && currX + 15 <= 288) //Check if current mouse pos within boundaries
	{ //Mouse position based on center of ship
		shipX = currX - 10;
	}
	if (currY - 20 >= -288 && currY + 20 <= -192)
	{
		shipY = currY - 20;
	}
	glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && !bombShot && explode == 0 && !lost && !won)
	{ //If player shot bomb and bomb not already on field
		bombX = shipX + 3; //Set bombs starting location
		bombY = shipY + 13;
		bombShot = true; //Set boolean to know tht a bomb was shot
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && bombShot && !lost && !won)
	{
		hit = false;
		blown = true;
		bombShot = false;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && lost)
	{
		lost = false;
		won = false;
		reset = true;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && won && winNum <= 3)
	{
		won = false;
		lost = false;
		reset = true;
		segmentNum -= 20;
	}
	glFlush();
}

/*void idle()
{
	if (clock() > timer + 3)
	{
		glutPostRedisplay();
	}
}*/

void startGame(int button, int state, int x, int y)
{
	mouseButton = button;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glutDestroyWindow(splashId);
		//MAIN WINDOW SIZE
		MainWidth = 800;
		//glutGet(GLUT_SCREEN_WIDTH);
		MainHeight = 600;
		//glutGet(GLUT_SCREEN_HEIGHT);




		//GAME WINDOW SIZE 75% 
		gameWidth = (int)(MainWidth * 0.75);
		gameHeight = (int)(MainHeight);


		//CREATE WINDOW
		glutInitWindowSize(MainWidth, MainHeight);				// specify a window size
		glutInitWindowPosition(0, 0);			// specify a window position


		mainwindow = glutCreateWindow("MainScreen");	// create a titled window

		//INIT and CALLBACK for MainScreen
		backgroundmyInit();
		glutDisplayFunc(backgroundCallback);		// register a callback


		//Creating SubWindow where gameWidth/gameHeight is 75% of Viewable Screen Area.   
		//Setting margin with MainWidth * 0.25 * 0.5, basically half of nonused size
		gamewindow = glutCreateSubWindow(mainwindow, (int)(MainWidth * 0.25 *0.5), 0, gameWidth, gameHeight); //Create

		//INIT AND CALLBACK for GameScreen
		myInit2();

		glutDisplayFunc(myDisplayCallback2);		// register a callback
		glutPassiveMotionFunc(shipMove); //Mouse movement moves ship
		glutMouseFunc(mouseClick); //Left click shoots bomb
		//glutIdleFunc(idle);
		glutMainLoop();							// get into an infinite loop
	}
	glFlush();
}
