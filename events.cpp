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

void shipMove(int x, int y)
{
	int currX = (x - ((gameWidth/2))); //Convert to world coordinate system
	int currY = ((gameHeight/2)) - y;
	if (currX-20 >= -288 && currX+20 <= 288) //Check if current mouse pos within boundaries
	{ //Mouse position based on center of ship
		shipX = currX-10;
	}
	if (currY-25 >= -288 && currY+25 <= -192)
	{
		shipY = currY-25;
	}
	glutPostRedisplay();
}

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

		glutMainLoop();							// get into an infinite loop
	}
	glFlush();
}