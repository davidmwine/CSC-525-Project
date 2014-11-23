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

#include "GL/glut.h"
using namespace std;

void openImg();
void openImg2();
void openImg3();
int GetX(int rx, int r, double d, double pi);
int GetY(int ry, int r, double d, double pi);
void displayShip(GLubyte shipStip[], int startX = -10, int startY = -190);
void displayBullets();
void displayImg(GLfloat picture[159][318][3]);
void displayMushroom(GLubyte mushroompattern[]);
void displayCentipede(double d, double pi, size_t counter);
void displayText(GLfloat xcor1, GLfloat ycor1);