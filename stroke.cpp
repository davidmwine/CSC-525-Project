/*==================================================================================================
PROGRAMMER:			    David Wine
COURSE:				    CSC 525/625
MODIFIED BY:			N/A
LAST MODIFIED DATE:	    Nov. 23, 2014
DESCRIPTION:			Draw a rectangular pipe and display in both orthographic and perspective
							views, allowing user to change view as well, with instructions in a
							pop up window
NOTE:					N/A
FILES:					hw6.cpp
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
#include <math.h>
using namespace std;
//Variables
const double pi = 3.14159265;
float eyeX = 100;
float eyeY = 100;
float eyeZ = 100;
float centerX = 0;
float centerY = 0;
int centerZ = 0;
float tmpX;
float tmpY;
float tmpZ;
float upX = 0;
float upY = 1;
float upZ = 0;
int helpWindow;
int expand = 0;
double Dist;
bool helpMenu = true;
int mainWindow;

int windowWidth = 800;
int windowHeight = 400;
int xPad = 0;
int yPad = 0;


//***********************************************************************************

void instructions()
{
	string help = "How to use program"; //Create each string needing displayed for instructions
	string q = "Press q to increase x by 5";
	string a = "Press a to decrease x by 5";
	string w = "Press w to increase y by 5";
	string s = "Press s to decrease y by 5";
	string e = "Press e to increase z by 5";
	string d = "Press d to decrease z by 5";
	string r = "Press r to move the viewer 5 (distance) to center";
	string f = "Press f to move the viewer 5 (distance) outwards";
	string reset1 = "Right click main window and click reset to reset";
	string reset2 = "     to initial position";
	string exitMain1 = "Right click main window and click exit";
	string exitMain2 = "     to close program";
	string exitHelp1 = "Right click help window and click close help window";
	string exitHelp2 = "     to close this window";
	string openHelp1 = "Right click main window and click help";
	string openHelp2 = "     to reopen help window";
	string ops[16] = { q, a, w, s, e, d, r, f, reset1, reset2, exitMain1, 
	exitMain2, exitHelp1, exitHelp2, openHelp1, openHelp2}; //Put instructions in an array
	int currRastX = -140; //Set position for heading
	int currRastY = 100;
	glColor3f(0, 1, 0);
	for (int loc = 0; loc < help.length(); loc++) //Draw heading text
	{
		glRasterPos2i(currRastX, currRastY);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, help[loc]);
		currRastX += 15;
	}
	currRastX = -200; //Set starting position for instructions
	currRastY = 85;
	for (int n = 0; n < 16; n++) //Loop through each instruction
	{
		for (int loc = 0; loc < ops[n].length(); loc++)
		{ //Display current instruction
			glRasterPos2i(currRastX, currRastY);
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, ops[n][loc]);
			currRastX += 8;
		}
		currRastX = -200; //Update raster position for next instruction
		currRastY -= 13;
	}

}
//Launch Instructions
void myDisplayCallback2()
{
	glClear(GL_COLOR_BUFFER_BIT);
	instructions();
	glFlush();
}

void helpInit()
{
	glClearColor(0, 0, 0, 0);			// specify a background clor: white
	gluOrtho2D(-250, 250, -120, 120);  // specify a viewing area
}

void menuSelect2(int id)
{
	if (id == 1)
	{
		helpMenu = false; //Can open new help window again
		glutDestroyWindow(helpWindow); //Destroy window
		glutSetWindow(mainWindow); //Set window to mainWindow
	}
}

void menuSelect(int id)
{
	if (id == 3)
	{
		exit(0); //If told to exit close program
	}
	else if (id == 1)
	{ //If told to reset set all gluLookat parameters to original parameters and redisplay
		eyeX = 100;
		eyeY = 100;
		eyeZ = 100;
		centerX = 0;
		centerY = 0;
		centerZ = 0;
		upX = 0;
		upY = 1;
		upZ = 0;
		glutPostRedisplay();
	}
	else
	{ //Otherwise open up new window showing instructions for program
		if (!helpMenu)
		{
			helpMenu = true; //Can no longer open new help windows
			glutInitWindowSize(500, 250);
			glutInitWindowPosition(850, 100);
			helpWindow = glutCreateWindow("HELP");
			helpInit();
			glutDisplayFunc(myDisplayCallback2);
			int menuid2 = glutCreateMenu(menuSelect2); //Allow user to exit help window
			glutAddMenuEntry("Close Help Window", 1);
			glutAttachMenu(GLUT_RIGHT_BUTTON);
			glutMainLoop();
		}
	}
}

void moveCamera(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q': //Positive movement along x
		eyeX += 5;
		break;
	case 'a': //Negative movement along x
		eyeX -= 5;
		break;
	case 'w': //Positive movement along y
		eyeY += 5;
		break;
	case 's': //Negative movement along y
		eyeY -= 5;
		break;
	case 'e': //Positive movement along z
		eyeZ += 5;
		break;
	case 'd': //Negative movement along z
		eyeZ -= 5;
		break;
	case 'r': //Moving Viewer CENTER


		//Calculating New Unit Vector
		Dist = sqrt(pow(eyeX, 2) + pow(eyeY, 2) + pow(eyeZ, 2));


		tmpX = eyeX / Dist;
		tmpY = eyeY / Dist;
		tmpZ = eyeZ / Dist;
		//Increase Distance from Center
		Dist -= 5;

		//Calculate new viewpoint
		eyeX = Dist*tmpX;
		eyeY = Dist*tmpY;
		eyeZ = Dist*tmpZ;
		break;

	case 'f': //Moving Viewer OUTWARDS
		//Calculating New Unit Vector
		Dist = sqrt(pow(eyeX, 2) + pow(eyeY, 2) + pow(eyeZ, 2));
		tmpX = eyeX / Dist;
		tmpY = eyeY / Dist;
		tmpZ = eyeZ / Dist;

		//Increase Distance from Center
		Dist += 5;
		
		//Calculate new viewpoint
		eyeX = Dist*tmpX;
		eyeY = Dist*tmpY;
		eyeZ = Dist*tmpZ;
	}
	glutPostRedisplay(); //Display changes
}

void drawPoints()
{
	glViewport(xPad, yPad, windowWidth / 2, windowHeight); //Set viewport based on current window size
	glMatrixMode(GL_PROJECTION); //Reset ortho for left side
	glLoadIdentity();
	glOrtho(-200, 200, -200, 200, 1, 1500);  // specify a viewing area
	glMatrixMode(GL_MODELVIEW); //Reset glu lookat
	glLoadIdentity(); //Display current view
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
	glPointSize(1); ///Change point size to 1


	glBegin(GL_LINES);	// use points to form X-/Y-/Z-axes
	glColor3f(0, 0, 0);			 // change drawing color to black
	glVertex3i(-150, 0, 0); // draw X-axis
	glVertex3i(150, 0, 0);
	glVertex3i(0, -150, 0); // draw Y-axis
	glVertex3i(0, 150, 0);
	glVertex3i(0, 0, -150); //draw Z-axis
	glVertex3i(0, 0, 150);
	glEnd();

	glPushMatrix();
	glRasterPos3i(160, -4, -4);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 88);
	glRasterPos3i(-4, 160, -4);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 89);
	glRasterPos3i(-4, -4, 160);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 90);
	glPopMatrix();

	float x = 0;
	float y = 100;
	float z = 0;
	string s = "HELLO THERE";
	for (int i = 0; i < s.length(); i++)
	{
		glPushMatrix();
		glTranslatef(x, y, z);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, s[i]);
		y -= 40;
		glPopMatrix();
	}
	
	//Viewport based on window size and placed on right of screen
	glViewport(windowWidth / 2 + xPad, yPad, windowWidth / 2, windowHeight);
	glMatrixMode(GL_PROJECTION); //Change to gluPerspective for right side
	glLoadIdentity();
	gluPerspective(90, 1, 1, 1500);
	glMatrixMode(GL_MODELVIEW); //Reset glu lookat
	glLoadIdentity(); //Display current view
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
	glPointSize(1); ///Change point size to 1

	glBegin(GL_LINES);	// use points to form X-/Y-/Z-axes
	glColor3f(0, 0, 0);			 // change drawing color to black
	glVertex3i(-150, 0, 0); // draw X-axis
	glVertex3i(150, 0, 0);
	glVertex3i(0, -150, 0); // draw Y-axis
	glVertex3i(0, 150, 0);
	glVertex3i(0, 0, -150); //draw Z-axis
	glVertex3i(0, 0, 150);
	glEnd();

	glRasterPos3i(160, -4, -4);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 88);
	glRasterPos3i(-4, 160, -4);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 89);
	glRasterPos3i(-4, -4, 160);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 90);

	float x2 = 0;
	float y2 = 100;
	float z2 = 0;
	string s2 = "HELLO THERE";
	for (int i = 0; i < s2.length(); i++)
	{
		glPushMatrix();
		glTranslatef(x2, y2, z2);
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, s2[i]);
		y2 -= 120;
		glPopMatrix();
	}


}

void reshape(int w, int h)
{ //If window is reshaped, change proportions for viewport
	if (h == w / 2)
	{ //If height is twice the width viewport is same
		windowWidth = w;
		windowHeight = h;
		xPad = 0;
		yPad = 0;
	}
	else if (h > w / 2)
	{ //If h is greater than half the width height based on width and padding added
		windowWidth = w;
		windowHeight = w / 2;
		xPad = 0;
		yPad = (h - windowHeight) / 2;
	}
	else
	{// Otherwise width based on height and padding added
		windowWidth = h * 2;
		windowHeight = h;
		xPad = (w - windowWidth) / 2;
		yPad = 0;
	}
}

//***********************************************************************************
void myInit()
{
	glClearColor(1, 1, 1, 0);			// specify a background clor: white
	glViewport(xPad, yPad, windowWidth, windowHeight);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-200, 200, -200, 200, 1, 500);  // specify a viewing area
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
}

//***********************************************************************************
void myDisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// draw the background

	drawPoints();

	glFlush(); // flush out the buffer contents
}

//***********************************************************************************
void main(int argc, char ** argv)
{
	glutInitDisplayMode(GLUT_DEPTH);
	glutInit(&argc, argv);
	glutInitWindowSize(800, 400);				// specify a window size
	glutInitWindowPosition(0, 0);			// specify a window position
	mainWindow = glutCreateWindow("Simple Point Drawing");	// create a titled window
	glEnable(GL_DEPTH_TEST);

	myInit();									// setting up

	glutReshapeFunc(reshape);
	glutDisplayFunc(myDisplayCallback);		// register a callback
	glutKeyboardFunc(moveCamera); //Key presses used to adjust camera

	//Create menu with a reset option, help window option, and exit option
	int menuid = glutCreateMenu(menuSelect);
	glutAddMenuEntry("Reset", 1); //Allow user to reset, open help window, or exit
	glutAddMenuEntry("Help Window", 2);
	glutAddMenuEntry("Exit", 3);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutInitWindowSize(500, 250);
	glutInitWindowPosition(850, 100);
	helpWindow = glutCreateWindow("HELP");
	helpInit();
	glutDisplayFunc(myDisplayCallback2);
	int menuid2 = glutCreateMenu(menuSelect2); //Allow user to exit help window
	glutAddMenuEntry("Close Help Window", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();

	glutMainLoop();							// get into an infinite loop
}
