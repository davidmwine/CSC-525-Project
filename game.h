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
#include "splash.h"
#include "variables.h"
#include <vector>
//Display Functions
void displayLoss(GLfloat pixMap[][300][4], double angleStart);
void displayWin(GLfloat pixMap[][450][4], double angleStart);
void displayFinish(GLfloat pixMap[][300][4], double angleStart);
void displayInstr();
void displayPause();

//Individual Mushrooms
struct flocations
{
	double mX;//X Location
	double mY;//Y location
	bool visible;//Bool to Display
	bool inContact;//Is centipede in contact
	double r;//color values
	double g;
	double b;
	int change = 301;//color change timer
};
//Field of Mushrooms Class, contains all mushroom related functions
class mushrooms
{
private:
	vector<flocations*> field;//Vector holds mushrooms
	int maxMush; //maximum number of mushrooms allowed per row

public:
	//Values prevent drawing of mushrooms on edges or in ship position
	mushrooms(int maximum = 2, double minX = -264, double minY = -192, double maxX = 264, double maxY = 240)
	{
		bool t = false;
		bool gVal = false;
		unsigned int Fsize;
		maxMush = maximum;

		//Create First mushroom at safe location
		flocations *first = new flocations();
		first->mX = 216;
		first->mY = 96;
		field.push_back(first);

		//Go through each grid row
		for (int y = minY; y <= maxY; y += 24)
		{

			Fsize = field.size();//current size of field

			//Create mushrooms randomly per row till max is reached
			for (int x = 0; x < maxMush; x++)
			{

				double rFactor = (rand() % 11) * 24;//Random X location
				flocations *ty = new flocations();//New Mushroom
				ty->visible = true;//Show Mushroom
				ty->inContact = false;// Not in contact yet

				//function to create even distribution between pos and neg x values
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


				//Extra rule check
				//Mushrooms are not allowed to be draw catercorner from mushroom
				for (unsigned int u = 0; u < Fsize; ++u)
				{
					if (ty->mX - 24 == (field[u]->mX) && ty->mY - 24 == (field[u]->mY)\
						|| ty->mX + 24 == (field[u]->mX) && ty->mY - 24 == (field[u]->mY)\
						|| ty->mX - 24 == (field[u]->mX) && ty->mY + 24 == (field[u]->mY)\
						|| ty->mX + 24 == (field[u]->mX) && ty->mY + 24 == (field[u]->mY))
					{

						gVal = true;//Draw boolean is true


					}



				}

				//If mushroom breaks the rules, don't add it
				if (!gVal)
					field.push_back(ty);//Add Mushroom to field

				gVal = false;


			}
		}


	}
	//Gets index and returns mushroom pointer in field
	flocations* mushpointer(int lock)
	{

		return field[lock];
	}
	//create random mushroom field
	void create()
	{

		for (unsigned int i = 0; i < field.size(); ++i)//For each placed mushroom
		{
			if (field[i]->visible)//if the mushroom is visible (not destroyed)
			{
				double r = 0;
				double g = 0;
				double b = 0;
				if (field[i]->change > 300)//timer function to change color
				{
					
					while (r < 0.9 && g < 0.9 && b < 0.9)//Only allow bright colors
					{
						//Random Color generator
						r = (double)rand() / RAND_MAX;
						g = (double)rand() / RAND_MAX;
						b = (double)rand() / RAND_MAX;
						//cout << r << " " << g << " " << b << endl;
					}
					//Set color values for individual mushrooms
					field[i]->r = r;
					field[i]->g = g;
					field[i]->b = b;
					field[i]->change = 0;//reset timer
				}
				else
				{
					//maintain mushroom color if timer not reached
					r = field[i]->r;
					g = field[i]->g;
					b = field[i]->b;
					field[i]->change++;//increment timer
				}
				draw(field[i]->mX, field[i]->mY, r, g, b);//call draw function
			}
		}
	}
	//Simply draws mushroom with location and color
	void draw(double x, double y, double r, double g, double b)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glColor3f(r, g, b);
		glRasterPos2i(x, y);
		glBitmap(24, 24, 0.0, 0.0, 0.0, 0.0, mushroompattern2);
	}
	//Returns vector of mushrooms(field)
	vector<flocations*> getField()
	{
		return field;
	}
	//Checking if the mushroom needs to be blown up
	bool blowUp(int x, int y)//COLLISION DETECTION
	{
		bool result = false;
		for (int i = 0; i < field.size(); i++)
		{
			int mX = field[i]->mX;
			int mY = field[i]->mY;
			if ((mX <= x + 48 && mX >= x - 24)\
				|| mX + 24 <= x + 48 && mX + 24 >= x - 24)
			{
				if ((mY <= y + 48 && mY >= y - 24)\
					|| (mY + 24 <= y + 48 && mY + 24 >= y - 24))
				{
					result = true;
				}
			}
		}
		return result;
	}
	//Set mushroom visible property to false if blownUp
	void destroyMush(int x, int y)//COLLISION DETECTION
	{
		for (int i = 0; i < field.size(); i++)
		{
			int mX = field[i]->mX;
			int mY = field[i]->mY;
			if ((mX <= x + 48 && mX >= x - 24)\
				|| mX + 24 <= x + 48 && mX + 24 >= x - 24)
			{
				if ((mY <= y + 48 && mY >= y - 24)\
					|| (mY + 24 <= y + 48 && mY + 24 >= y - 24))
				{
					field[i]->visible = false;
				}
			}
		}
	}

	int getX(int i)//get mushroom X value by index
	{
		return field[i]->mX;
	}

	int getY(int i)//get mushroom Y value by index
	{
		return field[i]->mY;
	}
	bool isVisible(flocations* mm)//pass mushrooms and get visible property
	{
		return mm->visible;
	}
	bool isInContact(flocations* mm)//pass mushrooms and get if its in contact with centipede
	{
		return mm->inContact;
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
	bool DrawDisplay;//Draw
	bool MoveLeft;//Boolean determine whether Centipede moves left or gith
	int segNum;//Segment Density
	bool head;//Is Segment Head
	bool tail;//Is Segment Tail
public:
	Segments(double x, double y, int segs) {//Constructor 
		minxlocation = x;//X location
		minylocation = y;//Y location
		segNum = segs;//Segment Line Density 
		DrawDisplay = false;
		MoveLeft = false;
		head = false;
		tail = false;
	}
	//get whether Segment is head
	bool IsHead()
	{
		return head;
	}
	//set Segment as Head
	void SetH()
	{
		head = true;
	}
	//get whether Segment is tail
	bool IsTail()
	{
		return tail;
	}
	//set Segment as Tail
	void SetT()
	{
		tail = true;
	}
	//Just Draws Segments
	void draw()
	{
		if (DrawDisplay)
		{
			glColor3f(0, 0.8, 0); //Color
			DrawCircle(minxlocation, minylocation, r, segNum);	//Draw Segments
		}
	}
	//Draw function for centipede, efficient circle generator
	void DrawCircle(float cx, float cy, float r, int num_segments)
	{
		float theta = 2 * 3.1415926 / float(num_segments);  //Calculate Theta
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
	//For Drawing Eyes/Antenna, good for drawing circles within circles or lines
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
	//Set Draw to True
	void DrawSegmentTrue()
	{
		DrawDisplay = true;
	}
	//Set Draw to False
	void DrawSegmentFalse()
	{
		DrawDisplay = false;
	}
	//Set alternate movement when called from left to right or vice versa
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

	//Return Boolean of left/right switch
	bool retMLeft()
	{
		return MoveLeft;

	}


};
class Centipede {
private:
	vector<Segments*> body;//Holds Body Segments
	int NumOfSegments;//Number of Body Segments
	bool ToDraw;//Draw Bool
	bool done;//Centipede finishes
	int segNum;//Line Density of Segments
	/*Need to Implement a body counter for bomb destruction*/
public:
	Centipede(int segs = 50, double startX = -85, double startY = 277){
		NumOfSegments = 8; //Default Number of segments
		ToDraw = false;
		done = false;
		segNum = segs; //Segment Line Density set
		for (int i = 0; i < NumOfSegments; i++)
		{
			Segments *Y = new Segments(startX, startY, segNum);//Create Segement
			if (i == 0)//If first, set to Head
			{
				Y->SetH();
			}
			if (i == NumOfSegments - 1)//If last, set to tail
			{
				Y->SetT();
			}
			body.push_back(Y);//Add Segment to body
			startX = startX - 23;//place 23 pixels behind


		}

	};
	//Set centipede to Visible
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
	//Make Centipede segments to invisible
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
	//Return number of segments
	int getSize()
	{
		return NumOfSegments;
	}
	//return segment x location
	int getSegX(int i)
	{
		return body[i]->centerX();
	}
	//return segment y location
	int getSegY(int i)
	{
		return body[i]->centerY();
	}

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
	void move(vector<flocations*> mush)//Movement function, calls other movement function
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
	//Set passed mushroom to in contact with centipede
	void EnterMushroom(flocations* hitMush)
	{

		hitMush->inContact = true;

	}
	//Set passed mushroom to NOT in contact with centipede
	void LeaveMushroom(flocations* hitMush)
	{

		hitMush->inContact = false;
	}

	//Move Down Method
	void movedown(Segments* ut)
	{
		double u = 0.0;
		while (u < 24)
		{
			ut->moveSegment(0, 1);
			u = u + 1;
		}
		ut->SetMLeft();
	}
	bool CollisionDetector(vector<flocations*> mushloc, Segments* ut)
	{
		bool set = false; //Boolean if centipede needs to move down and turn
		if (ut->retMLeft()) //If moving left check left collision
		{

			if ((ut->centerX() - 12) < -285) //If hit left wall move down and turn
			{
				set = true;
			}
			else //Else check if mushroom hit
			{
				for (auto mush : mushloc) //Loop through each mushroom
				{
					if (mush->mX + 24 >= ut->centerX() - 12 && mush->mX <= ut->centerX() - 12)
					{
						if (mush->mY + 24 >= ut->centerY() && mush->mY <= ut->centerY())
						{ //If centipede in x and y bounds of a mushroom
							if (ut->IsHead() && mush->visible)
							{ //If it is the head segment and mushroom is visible move down and turn
								EnterMushroom(mush); //Make sure rest of body finishes even if mushroom destroyed
								set = true;
							}
							else if (ut->IsTail() && mush->inContact)
							{ //If centipede finished turning change in contact value and let tail finish turning
								LeaveMushroom(mush);
								set = true;
							}
							else if (mush->inContact)
							{ //If in middle of turning finish turning
								set = true;
							}
							else
							{ //Otherwise no collision
								set = false;
							}
						}
					}
				}
			}

		}
		else
		{
			if ((ut->centerX() + 12) > 287) //If hit right wall move down and turn
			{
				set = true;
			}
			else
			{
				for (auto mush : mushloc) //Loop through the mushrooms
				{
					//11.8 12.2
					if (mush->mX <= ut->centerX() + 12 && mush->mX + 24 >= ut->centerX() + 12)
					{
						if (mush->mY +24 >= ut->centerY() && mush->mY <= ut->centerY())
						{ //If centipede in bounding x and y of a mushroom
							if (ut->IsHead() && mush->visible) //If started turning
							{
								EnterMushroom(mush); //Make sure turn completes
								set = true;
							}
							else if (ut->IsTail() && mush->inContact) //If done turning
							{
								LeaveMushroom(mush); //Mushroom no longer being turned on
								set = true; //Let tail finish
							}
							else if (mush->inContact)
							{ //If in mid turning there is a collision
								set = true;
							}
							else
							{ //Otherwise there was no collision
								set = false;
							}
						}
					}

				}

			}
		}
		return set; //Return whether or not there was a collision

	}

	//Determine if centipede was hit
	bool blowUp(int bX, int bY)
	{
		bool result = false;
		for (int i = 0; i < NumOfSegments; i++) //Check collision with each segment
		{
			if ((body[i]->centerX() - 12 >= bX - 24 && body[i]->centerX() - 12 <= bX + 48)\
				|| (body[i]->centerX() + 12 >= bX - 24 && body[i]->centerX() + 12 <= bX + 48))
			{
				if ((body[i]->centerY() - 12 >= bY - 24 && body[i]->centerY() - 12 <= bY + 48)\
					|| (body[i]->centerY() + 12 >= bY - 24 && body[i]->centerY() + 12 <= bY + 48))
				{ //Check if explosion in bounding box of a segment
					result = true;
				}
			}
		}
		return result; //Return whether or not centipede was hit
	}

	//Destroy a centipede segment if needing popped
	void popSeg()
	{
		if (NumOfSegments > 1) //If there are segments left pop one
		{
			body.pop_back();
			NumOfSegments--;
			body[body.size() - 1]->SetT();
		}
		else //Otherwise clear vector, reduce NumOfSegments and level done
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
	{ //Draw the grid for the game area
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
public:
	Ship(GLubyte shipStip[], int x, int y)
	{
		//Ship should stay between -288 and 288 for x
		//And -288 and -216 for y
		int xLoc = x; //X and Y locations pass in as parameters
		int yLoc = y;
	}
	void drawShip(GLubyte ship[], int startX, int startY)
	{ //Draw the ship
		xLoc = startX; //Start location of bottom left corner
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
	{ //Check if ship collided with centipede
		bool result = false;
		for (int i = 0; i < c->getSize(); i++) //Check each segment
		{
			int cX = c->getSegX(i);
			int cY = c->getSegY(i);
			if ((cX - 12 <= xLoc + 25 && cX - 12 >= xLoc - 5)\
				|| cX + 12 <= xLoc + 25 && cX + 12 >= xLoc - 5)
			{
				if ((cY - 12 <= yLoc + 40 && cY - 12 >= yLoc)\
					|| (cY + 12 <= yLoc + 40 && cY + 12 >= yLoc))
				{ //Check if ship inside a segments bounding box
					result = true;
				}
			}
		}
		return result; //Return whether or not ship hit centipede
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
	{//Empty constructer
	}
	void drawBomb(float x, float y)
	{ //Only draw the bomb if one has been shot
		xLoc = x; //Bombs current location
		yLoc = y;
		glEnable(GL_BLEND); //Use GL_BLEND to enable transparency of bomb
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		glRasterPos2i(xLoc, yLoc); //Starting point of bomb image
		glDrawPixels(24, 24, GL_RGBA, GL_FLOAT, bombPic); //Draw bomb image
		glDisable(GL_BLEND);
		if (yLoc > 288) //Bomb no longer considered shot if it goes off screen
		{
			bombShot = false;
		}
	}
	bool checkHit(Centipede *c)
	{ //Check if bomb hit the centipede
		bool result = false;
		for (int i = 0; i < c->getSize(); i++) //Check each segment
		{
			int cX = c->getSegX(i);
			int cY = c->getSegY(i);
			if ((cX - 12 <= bombX + 24 && cX - 12 >= bombX)\
				|| cX + 12 <= bombX + 24 && cX + 12 >= bombX)
			{
				if ((cY - 12 <= bombY + 24 && cY - 12 >= bombY)\
					|| (cY + 12 <= bombY + 24 && cY + 12 >= bombY))
				{ //Check if bomb within bounding box of a segment
					result = true;
				}
			}
		}
		return result; //Return whether or not a collision
	}

	bool checkHit2(mushrooms *m)
	{ //Check for collision with bomb and mushrooms
		bool result = false;
		for (int i = 0; i < m->getField().size(); i++) //Check each mushroom
		{
			int mX = m->getX(i);
			int mY = m->getY(i);
			if ((mX <= xLoc + 24 && mX >= xLoc)\
				|| mX + 24 <= xLoc + 24 && mX + 24 >= xLoc)
			{
				if ((mY <= yLoc + 24 && mY >= yLoc)\
					|| (mY + 24 <= yLoc + 24 && mY + 24 >= yLoc))
				{ //Check if bomb within bounding box of a mushroom
					if (m->isVisible(m->mushpointer(i))) //Check if mushroom is visible
					{
						result = true;
					}
				}
			}
		}
		return result; //Return whether or not a collision
	}

	bool killed(int sX, int sY)
	{ //Check if bomb destroyed the ship
		bool result = false;
		if ((sX - 5 >= xLoc - 24 && sX + 25 <= xLoc + 48)\
			|| (sX - 5 >= xLoc - 24 && sX + 25 + 12 <= xLoc + 48))
		{
			if ((sY + 40 >= yLoc - 24 && sY + 40 <= yLoc + 48)\
				|| (sY >= yLoc - 24 && sY + 12 <= yLoc + 48))
			{ //Check if explosion within bounding box of the ship
				result = true;
			}
		}
		return result;
	}

	void explosion()
	{ //Display the explosion
		glEnable(GL_BLEND); //Use GL_BLEND to enable transparency of explosion
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		glRasterPos2i(bombX - 24, bombY - 24); //Starting point of explosion image
		glDrawPixels(72, 72, GL_RGBA, GL_FLOAT, explosionPic); //Draw explosion image
		glDisable(GL_BLEND);
	}
};