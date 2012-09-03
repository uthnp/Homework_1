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
	* TODO: could stand to be optimized in terms of code length... just kind of brute forced it to be safe
	*
	* Satisfies goal A.3
	*/
	void drawLine (uint8_t* pixels, int point1X, int point1Y, int point2X, int point2Y, Color8u color);

	/**
	* Draws & fills a triangle of a particular color whose vertices are specified.
	*
	* 
	*
	* Satisfies goal A.7
	*/
	void drawTriangle (uint8_t* pixels, int point1X, int point1Y, int point2X, int point2Y, int point3X, int point3Y, Color8u color);

	//Width and height of the screen
	static const int kAppWidth=800;
	static const int kAppHeight=600;
	static const int kTextureSize=1024; // must be power of 2
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
	//based on y = mx+b
	int slope;
	int intersect;
	int x;
	int y;

	if (point1X == point2X) //to prevent any div by 0 errors
	{
		x = point1X;
		for (y = min(point1Y, point2Y); y <= max(point1Y, point2Y); y++)
		{
			pixels[3*(x + y*kTextureSize)] = color.r;
			pixels[3*(x + y*kTextureSize)+1] = color.g;
			pixels[3*(x + y*kTextureSize)+2] = color.b;
		}
		return;
	}
	
	slope = ((point1Y - point2Y)/(point1X - point2X));
	intersect = (point1Y - (slope*point1X));
	if (slope > 0)
	{
		for (y = point1Y; y <= point2Y; y++)
		{
			for (x = point1X; x <= point2X; x++)
			{
				pixels[3*(x + y*kTextureSize)] = color.r;
				pixels[3*(x + y*kTextureSize)+1] = color.g;
				pixels[3*(x + y*kTextureSize)+2] = color.b;
			}
		}
	}
	else if (slope < 0)
	{
		for (y = point2Y; y <= point1Y; y++)
		{
			for (x = point2X; x <= point1X; x++)
			{
				pixels[3*(x + y*kTextureSize)] = color.r;
				pixels[3*(x + y*kTextureSize)+1] = color.g;
				pixels[3*(x + y*kTextureSize)+2] = color.b;
			}
		}
	}
	else // if slope == 0
	{
		for (x = min(point1X, point2X); x <= max(point1X, point2X); x++)
		{
			y = point1Y;
			pixels[3*(x + y*kTextureSize)] = color.r;
			pixels[3*(x + y*kTextureSize)+1] = color.g;
			pixels[3*(x + y*kTextureSize)+2] = color.b;
		}
	}
}

void Homework_1App::drawTriangle (uint8_t* pixels, int point1X, int point1Y, int point2X, int point2Y, int point3X, int point3Y, Color8u color)
{

}

void Homework_1App::update()
{
	//test
	uint8_t* pixels = (*mySurface_).getData();
	Color8u color = Color8u(100, 0, 20);
	drawRectangle(pixels, 50, 50, 60, 30, color);
	drawCircle (pixels, 150, 150, 70, color);
	drawLine (pixels, 200, 0, 210, 300, color);
}

void Homework_1App::draw()
{ 
	gl::draw(*mySurface_);
}

CINDER_APP_BASIC( Homework_1App, RendererGl )
