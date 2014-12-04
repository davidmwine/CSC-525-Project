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

void displayLoss(GLfloat pixMap[][300][4]);
void displayWin();
void displayFinish();

struct flocations
{
	double mX;
	double mY;
	bool used;
};
class mushrooms
{
private:
	vector<flocations*> field;

public:
	mushrooms(double minX = -240, double minY = -192, double maxX = 240, double maxY = 240)
	{

		srand(time(NULL));
		bool t = false;
		bool gVal = false;
		unsigned int Fsize;

		flocations *first = new flocations();
		first->mX = 216;
		first->mY = 96;

		field.push_back(first);


		for (int y = minY; y <= maxY; y += 24)
		{

			Fsize = field.size();


			for (int x = 0; x < 2; x++)
			{

				double rFactor = (rand() % 10) * 24;
				flocations *ty = new flocations();
				if (t)
				{
					ty->mX = rFactor;
					t = false;
				}
				else
				{
					ty->mX = -rFactor;
					t = true;
				}
				ty->mY = y;



				for (unsigned int u = 0; u < Fsize; ++u)
				{
					if (ty->mX - 24 == (field[u]->mX) && ty->mY - 24 == (field[u]->mY)\
						|| ty->mX + 24 == (field[u]->mX) && ty->mY - 24 == (field[u]->mY)\
						|| ty->mX - 24 == (field[u]->mX) && ty->mY + 24 == (field[u]->mY)\
						|| ty->mX + 24 == (field[u]->mX) && ty->mY + 24 == (field[u]->mY))
					{

						gVal = true;


					}



				}

				if (!gVal)
					field.push_back(ty);

				gVal = false;


			}
		}


	}
	void create()
	{
		for (unsigned int i = 0; i < field.size(); ++i)
		{
			draw(field[i]->mX, field[i]->mY);
		}
	}

	void draw(double x, double y)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glColor3f(1, 0.5, 1);
		glRasterPos2i(x, y);
		glBitmap(24, 24, 0.0, 0.0, 0.0, 0.0, mushroompattern2);
	}
	vector<flocations*> getField()
	{
		return field;
	}

	bool blowUp(int x, int y)
	{
		bool result = false;
		for (int i = 0; i < field.size(); i++)
		{
			int mX = field[i]->mX;
			int mY = field[i]->mY;
			if ((mX < x + 48 && mX > x - 24)\
				|| mX + 24 < x + 48 && mX + 24 > x - 24)
			{
				if ((mY < y + 48 && mY > y - 24)\
					|| (mY + 24 < y + 48 && mY + 24 > y - 24))
				{
					result = true;
				}
			}
		}
		return result;
	}

	void destroyMush(int x, int y)
	{
		for (int i = 0; i < field.size(); i++)
		{
			int mX = field[i]->mX;
			int mY = field[i]->mY;
			if ((mX < x + 48 && mX > x - 24)\
				|| mX + 24 < x + 48 && mX + 24 > x - 24)
			{
				if ((mY < y + 48 && mY > y - 24)\
					|| (mY + 24 < y + 48 && mY + 24 > y - 24))
				{
					field.erase(field.begin() + i);
				}
			}
		}
	}

	int getX(int i)
	{
		return field[i]->mX;
	}

	int getY(int i)
	{
		return field[i]->mY;
	}



};

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
	int linelocation;
	int segNum;
public:
	Segments(double x, double y, int segs) {
		minxlocation = x;
		minylocation = y;
		segNum = segs;
		DrawDisplay = false;
		MoveLeft = false;
		linelocation = 0;
	}
	//Just Draws Segments
	void draw()
	{
		if (DrawDisplay)
		{
			
			//glLineWidth(6);
			glColor3f(0, 0.8, 0);
			DrawCircle(minxlocation, minylocation, r, segNum);
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
		for (int i = 0; i < num_segments; i++)
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
	void moveSegment(double x, double y)
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

	void IncLineLocation()
	{
		linelocation++;
	}
	bool retMLeft()
	{
		return MoveLeft;

	}


};
class Centipede {
private:
	vector<Segments*> body;
	int NumOfSegments;
	bool ToDraw;
	bool done;
	int segNum;
	/*Need to Implement a body counter for bomb destruction*/
public:
	Centipede(int segs = 50, double startX = -85, double startY = 277){
		NumOfSegments = 8;
		ToDraw = false;
		done = false;
		segNum = segs;
		for (int i = 0; i < NumOfSegments; i++)
		{
			Segments *Y = new Segments(startX, startY, segNum);
			body.push_back(Y);
			startX = startX - 23;


		}

	};
	void DrawTrue()
	{
		if (!ToDraw && !done)
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
		if (ToDraw || done)
		{
			ToDraw = false;
			for (int i = 0; i < NumOfSegments; i++)
			{
				body[i]->DrawSegmentFalse();

			}
		}
	}
	int getSize()
	{
		return NumOfSegments;
	}
	int getSegX(int i)
	{
		return body[i]->centerX();
	}
	int getSegY(int i)
	{
		return body[i]->centerY();
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
	void move(vector<flocations*> mush)
	{
		for (int j = 0; j < NumOfSegments; j++)
		{
			if (CollisionDetector(mush, body[j]))  //if collision
			{
				movedown(body[j]);
			}
			else
			{
				body[j]->moveSegment(0.5, 0);
			}
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
			ut->moveSegment(0, 0.8);
			u = u + 0.8;
		}
		ut->IncLineLocation();
		ut->SetMLeft();
		ut->moveSegment(2, 0);
	}
	bool CollisionDetector(vector<flocations*> mushloc, Segments* ut)
	{
		bool set = false;
		if (ut->retMLeft())
		{

			if ((ut->centerX() - 12) < -285)
			{
				set = true;
			}
			else
			{
				for (auto mush : mushloc)
				{
					if (mush->mX + 12 > ut->centerX() - 12 && mush->mX - 12 < ut->centerX() - 12)
					{
						if (mush->mY + 12 > ut->centerY() - 12 && mush->mY - 12 < ut->centerY() - 12)
						{
							set = true;
						}
					}
				}
			}

		}
		else
		{
			if ((ut->centerX() + 12) > 287)
			{
				set = true;
			}
			else
			{
				for (auto mush : mushloc)
				{
					//11.8 12.2
					if (mush->mX - 12 < ut->centerX() + 12 && mush->mX + 12 > ut->centerX() + 12)
					{
						if (mush->mY - 12 < ut->centerY() - 12 && mush->mY + 12 > ut->centerY() - 12)
						{
							set = true;
						}
					}

				}

			}
		}
		return set;

	}
	bool blowUp(int bX, int bY)
	{
		bool result = false;
		for (int i = 0; i < NumOfSegments; i++)
		{
			if ((body[i]->centerX() - 12 > bX - 24 && body[i]->centerX() - 12 < bX + 48)\
				|| (body[i]->centerX() + 12 > bX - 24 && body[i]->centerX() + 12 < bX + 48))
			{
				if ((body[i]->centerY() - 12 > bY - 24 && body[i]->centerY() - 12 < bY + 48)\
					|| (body[i]->centerY() + 12 > bY - 24 && body[i]->centerY() + 12 < bY + 48))
				{
					result = true;
				}
			}
		}
		return result;
	}
	void popSeg()
	{
		if (NumOfSegments > 1)
		{
			body.pop_back();
			NumOfSegments--;
		}
		else
		{
			body.clear();
			NumOfSegments--;
			done = true;
		}
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
		glColor3f(0.3, 0.3, 0.3);
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
		/*glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glColor3f(1, 0.5, 1);
		glRasterPos2i(-288, -288);
		glBitmap(32, 32, 0.0, 0.0, 0.0, 0.0, mushroompattern);*/
	}
	void drawShip(GLubyte ship[], int startX, int startY)
	{
		xLoc = startX;
		yLoc = startY;
		glEnable(GL_POLYGON_STIPPLE);
		glPolygonStipple(ship); //Draw polygon with pattern
		glBegin(GL_POLYGON);
		glColor3f(1, 0, 1); //Draw ship
		glVertex2i(startX+5, startY);
		glVertex2i(startX + 15, startY);
		glVertex2i(startX + 25, startY + 20);
		glVertex2i(startX + 10, startY + 40);
		glVertex2i(startX - 5, startY + 20);
		glEnd();
		glDisable(GL_POLYGON_STIPPLE);//Draw ship cockpit
		glBegin(GL_POLYGON);
		glColor3f(0, 0, 0);
		glVertex2i(startX + 3, startY + 25);
		glVertex2i(startX + 10, startY + 35);
		glVertex2i(startX + 17, startY + 25);
		glEnd();
	}
	bool centColl(Centipede *c)
	{
		bool result = false;
		for (int i = 0; i < c->getSize(); i++)
		{
			int cX = c->getSegX(i);
			int cY = c->getSegY(i);
			if ((cX - 12 < xLoc + 25 && cX - 12 > xLoc - 5)\
				|| cX + 12 < xLoc + 25 && cX + 12 > xLoc - 5)
			{
				if ((cY - 12 < yLoc + 40 && cY - 12 > yLoc)\
					|| (cY + 12 < yLoc + 40 && cY + 12 > yLoc))
				{
					result = true;
				}
			}
		}
		return result;
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
		if (yLoc > 288)
		{
			bombShot = false;
		}
	}
	bool checkHit(Centipede *c)
	{
		bool result = false;
		for (int i = 0; i < c->getSize(); i++)
		{
			int cX = c->getSegX(i);
			int cY = c->getSegY(i);
			if ((cX - 12 < bombX + 24 && cX - 12 > bombX)\
				|| cX + 12 < bombX + 24 && cX + 12 > bombX)
			{
				if ((cY - 12 < bombY + 24 && cY - 12 > bombY)\
					|| (cY + 12 < bombY + 24 && cY + 12 > bombY))
				{
					result = true;
				}
			}
		}
		return result;
	}

	bool checkHit2(mushrooms *m)
	{
		bool result = false;
		for (int i = 0; i < m->getField().size(); i++)
		{
			int mX = m->getX(i);
			int mY = m->getY(i);
			if ((mX < xLoc + 24 && mX > xLoc)\
				|| mX + 24 < xLoc + 24 && mX + 24 > xLoc)
			{
				if ((mY < yLoc + 24 && mY > yLoc)\
					|| (mY + 24 < yLoc + 24 && mY + 24 > yLoc))
				{
					result = true;
				}
			}
		}
		return result;
	}

	bool killed(int sX, int sY)
	{
		bool result = false;
		if ((sX - 5 > xLoc - 24 && sX + 25 < xLoc + 48)\
			|| (sX - 5 > xLoc - 24 && sX + 25 + 12 < xLoc + 48))
		{
			if ((sY + 40 > yLoc - 24 && sY + 40 < yLoc + 48)\
				|| (sY > yLoc - 24 && sY + 12 < yLoc + 48))
			{
				result = true;
			}
		}
		return result;
	}

	void explosion()
	{
		glEnable(GL_BLEND); //Use GL_BLEND to enable transparency of bomb
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		glRasterPos2i(bombX - 24, bombY - 24); //Starting point of centipede image
		glDrawPixels(72, 72, GL_RGBA, GL_FLOAT, explosionPic); //Draw centipede image
		glDisable(GL_BLEND);
	}
};