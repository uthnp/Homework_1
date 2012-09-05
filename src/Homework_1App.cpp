/*
*	@author Nicholas Uth
*	Program written to produce an image of some cards using basic shapes.
*	Written for CSE 274 on Sept 3, 2012.
*	
*	@Note: some misc lines of code are taken from: https://github.com/brinkmwj/HW01
*	@Note: the circle midpoint algorithm used for the drawCircle method is modified from the one found here:
*		   http://en.wikipedia.org/wiki/Midpoint_circle_algorithm
*
*	@Note: program satisfies the following project requirements:
*		A.1, A.2, A.3, A.7
*		B.1
*/

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "Resources.h"
#include <algorithm>

using namespace ci;
using namespace ci::app;
using namespace std;

class Homework_1App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void prepareSettings(Settings* settings);

  private:
	Surface* mySurface_;

	/**
	* Draws & fills a rectangle with the specified color.
	*
	* Changes the color value of the pixels representing the rectangle with it's top left corner at
	* (topLeftX, topLeftY) as well as a width and height.
	*
	* Satisfies goal A.1
	*/
	void drawRectangle (uint8_t* pixels, int topLeftX, int topLeftY, int width, int height, Color8u color);

	/**
	* Draws & fills a circle with the specified color.
	*
	* Creates a circle with a specified radius and color at position (centerX, centerY).
	* Utilizes a version of the midpoint circle algorithm.
	*
	* Satisfies goal A.2
	*/
	void drawCircle (uint8_t* pixels, int centerX, int centerY, int radius, Color8u color);

	/**
	* Draws a line of the specified color.
	*
	* Changes the color of the pixels representing the line from (point1X, point1Y) and (point2X, point2Y) to the
	* specified color.
	*
	* @Note: Based on the Bresenham's Line Algorithm. I didn't use a reference or source code though.
	*		 I wrote what is in here based on my analysis of the theory. It may, however, be unintentionally similar
	*        to preexisting code. 
	*
	* Satisfies goal A.3
	*/
	void drawLine (uint8_t* pixels, int point1X, int point1Y, int point2X, int point2Y, Color8u color);

	/**
	* Draws & fills a triangle of a particular color whose vertices are specified.
	*
	* Incrementally draws lines from one edge of the triangle to the other (creating the third as a byproduct) until the
	* entire triangle has been filled out.
	*
	* Satisfies goal A.7
	*/
	void drawTriangle (uint8_t* pixels, int point1X, int point1Y, int point2X, int point2Y, int point3X, int point3Y, Color8u color);

	/**
	* Applys a blur effect on the pixels within the rectangle specified.
	*
	* Sets the value of a pixel within the specified bounds equal to the average of it and the 8 pixels
	* immediately surrounding it.
	*
	* Satisfies goal B.1
	*/
	void applyBlur (uint8_t* pixels, int topLeftX, int topLeftY, int width, int height);

	//Width and height of the screen
	static const int kAppWidth=800;
	static const int kAppHeight=600;
	static const int kTextureSize=1024; // must be power of 2

	// important constants & variables for the actual drawing
	Color8u backColor;
	Color8u white;
	Color8u black;
	Color8u red;
	Color8u yellow;
	static const int headerHeight = 100;
	static const int cardHeight = 300;
	static const int bufferHeight = 33; // vertical spacing
	static const int footerHeight = 100;
	static const int cardWidth = 170;
	static const int bufferWidth = 15; // space between cards

};

void Homework_1App::prepareSettings(Settings* settings){
	(*settings).setWindowSize(kAppWidth,kAppHeight);
	(*settings).setResizable(false);
}

void Homework_1App::setup()
{
	mySurface_ = new Surface(kTextureSize,kTextureSize,false);

}

void Homework_1App::mouseDown( MouseEvent event )
{
}

void Homework_1App::drawRectangle (uint8_t* pixels, int topLeftX, int topLeftY, int width, int height, Color8u color)
{
	int x;
	int y;

	// run through the right coordinates for the rectangle, then use them to change the color value of the appropriate pixels
	for (y = topLeftY; y <= (topLeftY + height); y++)
	{
		for (x = topLeftX; x <= (topLeftX + width); x++)
		{
			pixels[3*(x + y*kTextureSize)] = color.r;
			pixels[3*(x + y*kTextureSize)+1] = color.g;
			pixels[3*(x + y*kTextureSize)+2] = color.b;
		}
	}
}

void Homework_1App::drawCircle (uint8_t* pixels, int centerX, int centerY, int radius, Color8u color)
{
	// using modified version of the midpoint formula method from here: http://en.wikipedia.org/wiki/Midpoint_circle_algorithm
	// also... yes, I am using wikipedia as a source. In this case, if it works then what does it matter?

	int f = 1-radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x = 0;
	int y = radius;
	//handle the points along the horiz and vert that intersect the midpoint
	drawLine(pixels, centerX, (centerY-radius), centerX, (centerY+radius), color);
	drawLine(pixels, (centerX-radius), centerY, (centerX+radius), centerY, color);
	while (x < y)
	{
		if (f >= 0)
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		drawLine (pixels, (centerX + x), (centerY + y), (centerX - x), (centerY + y),color);
		drawLine (pixels, (centerX + x), (centerY - y), (centerX - x), (centerY - y),color);
		drawLine (pixels, (centerX + y), (centerY + x), (centerX - y), (centerY + x),color);
		drawLine (pixels, (centerX + y), (centerY - x), (centerX - y), (centerY - x),color);
	}
}

void Homework_1App::drawLine (uint8_t* pixels, int point1X, int point1Y, int point2X, int point2Y, Color8u color)
{
	// The following is based on the theory behind Bresenham's Line algorithm
	int x;
	int y;
	double dx = (point1X - point2X);
	double dy = (point1Y - point2Y);
	double percent;

	if (abs(dx) > abs(dy))
	{
		for (int i = min(point1X,point2X); i <= max(point1X, point2X); i++)
		{
			percent = (i - min(point1X,point2X))/dx;
			if (min(point1X, point2X) == point1X) // to make sure the X and Y coords stay synched
			{
				y = point1Y + (percent * dy);
			}
			else
			{
				y = point2Y + (percent * dy);
			}
			// in this case... i = x
			pixels[3*(i + y*kTextureSize)] = color.r;
			pixels[3*(i + y*kTextureSize)+1] = color.g;
			pixels[3*(i + y*kTextureSize)+2] = color.b;
		}
	}
	else // more y axis movement
	{
		for (int i = min(point1Y,point2Y); i <= max(point1Y, point2Y); i++)
		{
			percent = (i - min(point1Y,point2Y))/dy;
			if (min(point1Y, point2Y) == point1Y) // to make sure the X and Y coords stay synched
			{
				x = point1X + (percent * dx);
			}
			else
			{
				x = point2X + (percent * dx);
			}
			// in this case... i = y
			pixels[3*(x + i*kTextureSize)] = color.r;
			pixels[3*(x + i*kTextureSize)+1] = color.g;
			pixels[3*(x + i*kTextureSize)+2] = color.b;
		}
	}
}

void Homework_1App::drawTriangle (uint8_t* pixels, int point1X, int point1Y, int point2X, int point2Y, int point3X, int point3Y, Color8u color)
{
	int numIncrements = 200;
	double increment1To2X = (point2X - point1X)/numIncrements;
	double increment1To2Y = (point2Y - point1Y)/numIncrements;
	double increment1To3X = (point3X - point1X)/numIncrements;
	double increment1To3Y = (point3Y - point1Y)/numIncrements;

	int x2 = point1X;
	int y2 = point1Y;
	int x3 = point1X;
	int y3 = point1Y;

	for (int i = 0; i < numIncrements; i++)
	{
		x2 += increment1To2X;
		y2 += increment1To2Y;
		x3 += increment1To3X;
		y3 += increment1To3Y;

		drawLine (pixels, x2, y2, x3, y3, color);
	}
}

void Homework_1App::applyBlur(uint8_t* pixels, int topLeftX, int topLeftY, int width, int height)
{
	int x;
	int y;
	int newValue_r;
	int newValue_g;
	int newValue_b;

	// create a copy-to (dummy) array with the same length as pixels
	int pixelArrayLength = 3*(kAppHeight + kAppWidth*kTextureSize);
	uint8_t* dummyArray = new uint8_t[pixelArrayLength];

	// loop through original surface to get average values
	// edges of the rectangle are skipped for safety of the program
	for (y = (topLeftY + 1); y < (topLeftY + height); y++)
	{
		for (x = (topLeftX + 1); x < (topLeftX + width); x++)
		{
			newValue_r = 0;
			newValue_g = 0;
			newValue_b = 0;

			for (int i = (x-1); i <= (x+1); i++) // i refers to x coord of specific pixel
			{
				for (int j = (y-1); j <= (y+1); j++) // j refers to y coord of specific pixel
				{
					newValue_r += pixels[3*(i + j*kTextureSize)];
					newValue_g += pixels[3*(i + j*kTextureSize)+1];
					newValue_b += pixels[3*(i + j*kTextureSize)+2];
				}
			}

			// put the new pixel values into the dummy array
			dummyArray[3*(x + y*kTextureSize)] = newValue_r/9;
			dummyArray[3*(x + y*kTextureSize)+1] = newValue_g/9;
			dummyArray[3*(x + y*kTextureSize)+2] = newValue_b/9;
		}
	}

	// loop through the two arrays and apply the changed values to the real array
	for (y = (topLeftY + 1); y < (topLeftY + height); y++)
	{
		for (x = (topLeftX + 1); x < (topLeftX + width); x++)
		{
			pixels[3*(x + y*kTextureSize)] = dummyArray[3*(x + y*kTextureSize)];
		}
	}
}

void Homework_1App::update()
{
	uint8_t* pixels = (*mySurface_).getData();
	
	int numPixels = max(kAppWidth, kAppHeight);
	numPixels *= numPixels;

	// set up important color objects
	backColor = Color8u (10, 200, 10);
	white = Color8u (255, 255, 255);
	black = Color8u (0, 0, 0);
	red = Color8u (255, 0, 0);
	yellow = Color8u (255, 255, 0);

	for (int i = 0; i < (3*numPixels); i += 3)
	{
		pixels[i] = backColor.r;
		pixels[i+1] = backColor.g;
		pixels[i+2] = backColor.b;
	}

	// draw the cards
	for (int i = 0; i < 4; i++)
	{
		drawRectangle(pixels, (((2 * i + 1) * bufferWidth) + (i * cardWidth)), (headerHeight + bufferHeight), cardWidth, cardHeight, white);
	}


	applyBlur (pixels, 0, 0, kAppHeight, kAppWidth);
}

void Homework_1App::draw()
{ 
	gl::draw(*mySurface_);
}

CINDER_APP_BASIC( Homework_1App, RendererGl )
