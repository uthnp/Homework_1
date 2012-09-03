/*
*	@author Nicholas Uth
*	Program written to produce an image of some cards using basic shapes.
*	Written for CSE 274 on Sept 3, 2012.
*	
*	@Note: some lines of code are taken from: https://github.com/brinkmwj/HW01
*
*	@Note: program satisfies the following project requirements:
*		A.1, A.2, A.3, A.7
*		B.1
*/

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Resources.h"

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

	void drawRectangle (uint8_t* pixels, int topLeftX, int topLeftY, int width, int height, Color8u color);
	void drawCircle (uint8_t* pixels, int topLeftX, int topLeftY, int radius, Color8u color);
	void drawLine (uint8_t* pixels, int point1X, int point1Y, int point2X, int point2Y);
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
}

void Homework_1App::drawCircle (uint8_t* pixels, int topLeftX, int topLeftY, int radius, Color8u color)
{
}

void Homework_1App::drawLine (uint8_t* pixels, int point1X, int point1Y, int point2X, int point2Y)
{
}

void Homework_1App::drawTriangle (uint8_t* pixels, int point1X, int point1Y, int point2X, int point2Y, int point3X, int point3Y, Color8u color)
{
}

void Homework_1App::update()
{

}

void Homework_1App::draw()
{ 
}

CINDER_APP_BASIC( Homework_1App, RendererGl )
