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
#include "splash.h"
#include "variables.h"
#include <vector>
//Segments Class
class Segments
{
private:
	//Radius
	double r = 12;
	double pi = 3.1415;
	//Center
	double minxlocation, minylocation;
	bool DrawDisplay;
	bool MoveLeft;
public:
	Segments(double x, double y) {
		minxlocation = x;
		minylocation = y;
		DrawDisplay = false;
		MoveLeft = false;
	}
	//Just Draws Segments
	void draw()
	{
		if (DrawDisplay)
		{
			
			//glLineWidth(6);
			glColor3f(0, 0.8, 0);
			DrawCircle(minxlocation, minylocation, r, 300);
			//glBegin(GL_LINES); // use the default point size: 1
			//for (double t = 0; t <= 2 * pi; t += 0.005) //Incrementing slowly around Radius
			//{
			//	glVertex2f(GetX(minxlocation, 0, t, pi), GetY(minylocation, 0, t, pi));//Calls Circle function
			//	glVertex2f(GetX(minxlocation, r, t, pi), GetY(minylocation, r, t, pi));//Calls Circle function
			//}
			//glEnd();
		

		}
	}
	void DrawCircle(float cx, float cy, float r, int num_segments)
	{
		float theta = 2 * 3.1415926 / float(num_segments);
		float c = cosf(theta);//precalculate the sine and cosine
		float s = sinf(theta);
		float t;

		float x = r;//we start at angle = 0 
		float y = 0;

		glBegin(GL_LINE_LOOP);
		for (int ii = 0; ii < num_segments; ii++)
		{
			glVertex2f(cx, cy);
			glVertex2f(x + cx, y + cy);//output vertex 

			//apply the rotation matrix
			t = x;
			x = c * x - s * y;
			y = s * t + c * y;
		}
		glEnd();
	}
	//For Drawing Eyes/Antenna (Segment Drawing)
	int GetX(double rx, double r, double d, double pi) //Gets an x point from the center of a circle
	{
		double x;
		x = rx + (sin(d))*r;
		return x;
	}
	int GetY(double ry, double r, double d, double pi) //Gets a y point from the center of a circle
	{
		double y;
		y = ry + (sin(d + (pi / 2)))*r;
		return y;
	}
	//Return Methods for Center Point
	int centerX()
	{
		return minxlocation;
	}
	int centerY()
	{
		return minylocation;
	}
	//Basic Move Method for Segments
	void move(double x, double y)
	{	
		//Move based on Boolean left to right, right to left
		if (MoveLeft)
		{
			minxlocation = minxlocation - x;
			
		}
		else
		{
			minxlocation = minxlocation + x;
		}
		minylocation = minylocation - y;
		draw();
	}
	void DrawSegmentTrue()
	{
		DrawDisplay = true;
	}
	void DrawSegmentFalse()
	{
		DrawDisplay = false;
	}
	void SetMLeft()
	{
		if (MoveLeft)
		{
			MoveLeft = false;
		}
		else
		{
			MoveLeft = true;
		}
	}

};
class Centipede {
private:
	vector<Segments*> body;
	int NumOfSegments;
	bool ToDraw;
	/*Need to Implement a body counter for bomb destruction*/
public:
	Centipede(double startX = -85, double startY = 277){
		NumOfSegments = 8;
		bool ToDraw = false;
		for (int i = 0; i < NumOfSegments; i++)
		{
			Segments *Y = new Segments(startX, startY);
			body.push_back(Y);
			startX = startX - 23;


		}
	
	};
	void DrawTrue()
	{
		if (ToDraw == false)
		{
			ToDraw = true;
			for (int i = 0; i < NumOfSegments; i++)
			{
				body[i]->DrawSegmentTrue();

			}
		}
	}
	void DrawFalse()
	{
		if (ToDraw)
		{
			ToDraw = false;
			for (int i = 0; i < NumOfSegments; i++)
			{
				body[i]->DrawSegmentFalse();

			}
		}
	}
	//Basic Creation Method (Eventually to Be Deleted, Reference)
	//void initdraw(int startx = -109, int startyc = 277)
	//{
	//	int decreaseX = startx;
	//	int decreaseY = startyc;
	//	//Create Segments
	//	for (int i = 0; i < 8; i++)
	//	{
	//		Segments *Y = new Segments(decreaseX, decreaseY);
	//		body.push_back(Y);
	//		decreaseX = decreaseX - 24;


	//	}
	//	draweyesant();
	//}
	//Draws Eyes and Antenna on the first Segment
	void draweyesant()
	{
		if (ToDraw)
		{
			//Draw Eyes(Converted from Degress to Radeons for convenience)
			glColor3f(1, 0, 0.5);
			glPointSize(5);
			glBegin(GL_POINTS);
			glVertex2f(body[0]->GetX(body[0]->centerX(), 5, 45 * pi / 180, pi), body[0]->GetY(body[0]->centerY(), 5, 45 * pi / 180, pi));
			glVertex2f(body[0]->GetX(body[0]->centerX(), 5, 315 * pi / 180, pi), body[0]->GetY(body[0]->centerY(), 5, 315 * pi / 180, pi));
			glEnd();
			//Draw Antenna (Converted from Degress to Radeons for convenience)
			glColor3f(1, 1, 0.5);
			glBegin(GL_LINES);
			glVertex2f(body[0]->GetX(body[0]->centerX(), 10, 45 * pi / 180, pi), body[0]->GetY(body[0]->centerY(), 10, 45 * pi / 180, pi));
			glVertex2f(body[0]->GetX(body[0]->centerX() + 5, 10, 45 * pi / 180, pi), body[0]->GetY(body[0]->centerY() + 5, 10, 45 * pi / 180, pi));
			glVertex2f(body[0]->GetX(body[0]->centerX(), 10, 320 * pi / 180, pi), body[0]->GetY(body[0]->centerY(), 10, 320 * pi / 180, pi));
			glVertex2f(body[0]->GetX(body[0]->centerX() - 5, 10, 320 * pi / 180, pi), body[0]->GetY(body[0]->centerY() + 5, 10, 320 * pi / 180, pi));
			glEnd();
		}

	}
	//General Purpose Move Method, calls other methods, to contain logic for moving
	void move()
	{
		for (int j = 0; j < NumOfSegments; j++)
			if ((body[j]->centerX() - 12) < -285  || (body[j]->centerX() + 12) > 287 )  //if collision
			{
			movedown(body[j]);
			}
			else
			{
			body[j]->move(0.5, 0);
			}


			
				
			
		//draw eyes
		draweyesant();


	}

	//Move Down Method
	void movedown(Segments* ut)
	{
		double u = 0.0;
		while (u < 23.6)
		{
			ut->move(0, 0.8);
			u = u + 0.8;
		}
		ut->SetMLeft();
		ut->move(0.5, 0);
	}
};


class Grid
{
private:
	int leftX;
	int botY;
	int rightX;
	int topY;
public:
	Grid(int minX = -288, int minY = -288, int maxX = 288, int maxY = 288)
	{ //Fill 600x600 area with grid
		leftX = minX; //Variables for area grid covers
		botY = minY;
		rightX = maxX;
		topY = maxY;
	}
	void drawGrid()
	{
		glColor3f(0, 0, 0);
		for (int x = leftX; x <= rightX; x += 24) //Grid squares are 24x24
		{
			glBegin(GL_LINES); //Draw vertical lines for grid
			glVertex2i(x, botY);
			glVertex2i(x, topY);
			glEnd();
		}
		for (int y = botY; y <= topY; y += 24)
		{
			glBegin(GL_LINES); //Draw horizontal lines for grid
			glVertex2i(leftX, y);
			glVertex2i(rightX, y);
			glEnd();
		}
	}

};

class Ship
{
private:
	int xLoc;
	int yLoc;
	int width;
	int height;
	//Ship() { }
public:
	Ship(GLubyte shipStip[], int x, int y)
	{
		//Ship should stay between -288 and 288 for x
		//And -288 and -192 for y
		int xLoc = x; //X and Y locations pass in as parameters
		int yLoc = y;
		displayShip(shipStip, xLoc, yLoc); //Display the ship starting at it's current location
		/*glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glColor3f(1, 0.5, 1);
		glRasterPos2i(-288, -288);
		glBitmap(32, 32, 0.0, 0.0, 0.0, 0.0, mushroompattern);*/
	}
	void redrawShip(GLubyte shipStip[], int x, int y)
	{
		int xLoc = x; //X and Y locations pass in as parameters
		int yLoc = y;
		displayShip(shipStip, xLoc, yLoc); //Display the ship starting at it's current location
	}
};

class Bomb
{
private:
	int xLoc;
	int yLoc;
	int width;
	int height;
public:
	Bomb()
	{
		/*xLoc = x; //Bombs current location
		yLoc = y;
		glEnable(GL_BLEND); //Use GL_BLEND to enable transparency of bomb
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		glRasterPos2i(xLoc, yLoc); //Starting point of bomb image
		glDrawPixels(24, 24, GL_RGBA, GL_FLOAT, bombPic); //Draw bomb image
		glDisable(GL_BLEND);*/
	}
	void drawBomb(float x, float y)
	{
		xLoc = x; //Bombs current location
		yLoc = y;
		glEnable(GL_BLEND); //Use GL_BLEND to enable transparency of bomb
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		glRasterPos2i(xLoc, yLoc); //Starting point of bomb image
		glDrawPixels(24, 24, GL_RGBA, GL_FLOAT, bombPic); //Draw bomb image
		glDisable(GL_BLEND);
	}
};