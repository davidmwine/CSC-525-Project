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

#include <iostream>
#include "csc525Project.h";
#include <time.h>
using namespace std;

//Create new variables for file, as well as initialize some extern variables
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
bool started = false;
bool paused = false;

void shipMove(int x, int y) //Ship movement
{ //Find new location for ship
	int currX = (x - ((gameWidth / 2))); //Convert to world coordinate system
	int currY = ((gameHeight / 2)) - y;
	if (currX - 15 >= -288 && currX + 15 <= 288) //Check if current mouse pos within boundaries
	{ //Mouse position based on center of ship
		shipX = currX - 10;
	}
	if (currY - 20 >= -288 && currY + 20 <= -216)
	{
		shipY = currY - 20;
	}
	glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y) //Various mouse events
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && !started)
	{ //Click to leave instructions screen and play game
		started = true;
		glClearColor(0.15, 0.15, 0.15, 1);
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && !bombShot && explode == 0 && !lost && !won)
	{ //If player shot bomb and bomb not already on field
		bombX = shipX + 3; //Set bombs starting location
		bombY = shipY + 13;
		bombShot = true; //Set boolean to know tht a bomb was shot
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && bombShot && !lost && !won)
	{ //If bomb shot and explosion happened set booleans
		hit = false;
		blown = true;
		bombShot = false;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && lost)
	{//If lost and on loss screen, click to restart game
		started = false;
		lost = false;
		won = false;
		reset = true;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && won && winNum <= 3)
	{ //If beat level then click to proceed to next level
		won = false;
		lost = false;
		reset = true;
		segmentNum -= 20;
	}
	glFlush();
}

void keyEvent(unsigned char key, int x, int y)
{
	switch (key)
	{
		case ' ': //If spacebar pressed toggle pause screen
			if (paused == false && started && !won && !lost)
			{
				glClearColor(0, 0, 0, 1);
				paused = true;
			}
			else if (!won && !lost && started)
			{
				glClearColor(0.15, 0.15, 0.15, 1);
				paused = false;
			}
			break;
		case 'r': //If r pressed reset to instructions menu
			started = false;
			reset = true;
			winNum = 0;
			won = false;
			lost = false;
			segmentNum = 50;
			break;
		case 27: //If ESC pressed exit program
			exit(0);
			break;
	}
}

void startGame(int button, int state, int x, int y)
{
	mouseButton = button;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{ //If on splash screen and button clicked create new window for game
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
		glutKeyboardFunc(keyEvent);
		//glutIdleFunc(idle);
		glutMainLoop();							// get into an infinite loop
	}
	glFlush();
}
