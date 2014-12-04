/*==================================================================================================
PROGRAMMER:			David Wine (Adjusted from points.cpp from Yang Wang)
COURSE:				CSC 525/625
MODIFIED BY:			N/A
LAST MODIFIED DATE:	Sep. 22, 2014
DESCRIPTION:			Display image from centipede.txt and draw and label axes
NOTE:					N/A
FILES:					lab7.cpp
IDE/COMPILER:			MicroSoft Visual Studio 2013
INSTRUCTION FOR COMPILATION AND EXECUTION:
1.		Double click on labProject.sln	to OPEN the project
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
using namespace std;

//***********************************************************************************
string aStringObjectName = "CENTIPEDE";
double d;//initializing variable
const double pi = 3.14159265; //pi constant
size_t countup;
GLfloat picture[300][300][4]; //Centipede picture pixel map
const GLfloat xcor1 = -70.0;
const GLfloat ycor1 = 120.0;
bool saved = false;

//***********************************************************************************
void main(int argc, char ** argv)
{
	ifstream file; //Create an ifstream to run through file
	ofstream file2;
	file.open("C:\\TEMP\\8bitskull.txt", ios::in | ios::binary);
	file2.open("C:\\TEMP\\8bitskull.bin", ios::out | ios::binary);

	float readNum;
	int i = 0; //Counter to determine where to place values in array
	int j = 0;
	int color = 0;
	if (file.is_open())
	{//If file is open run loop
		while (file >> readNum)
		{ //Loop through all numbers in file
			if (i < 300 * 4)
			{
				file2 << readNum << " ";
			}
			else
			{
				file2 << "\n";
				i = 0;
			}
		}
		file.close(); //Close file
		//file2.close();
	}
	else
	{//If file wasn't open display error message
		cout << "File not found. Make sure the file centipede.txt is in TEMP.\n";
		exit(0);
	}
	file2.close();
}
