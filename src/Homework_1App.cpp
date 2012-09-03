/*
*	@author Nicholas Uth
*	Program written to produce an image of some cards using basic shapes.
*	
*	@Note: some lines of code are taken from: https://github.com/brinkmwj/HW01
*/

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

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

	void drawRectangle (int topLeftX, int topLeftY, int width, int height);
	void drawCircle (int topLeftX, int topLeftY, int radius);
	void drawLine (int point1X, int point1Y, int point2X, int point2Y);
	void drawTriangle (int point1X, int point1Y, int point2X, int point2Y, int point3X, int point3Y);

	struct colorUInt8
	{
		uint8_t* red;
		uint8_t* green;
		uint8_t* blue;
	};

	//Width and height of the screen
	static const int kAppWidth=800;
	static const int kAppHeight=600;
	static const int kTextureSize=1024;
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

void Homework_1App::update()
{
}

void Homework_1App::drawRectangle (int topLeftX, int topLeftY, int width, int height)
{
}

void Homework_1App::drawCircle (int topLeftX, int topLeftY, int radius)
{
}

void Homework_1App::drawLine (int point1X, int point1Y, int point2X, int point2Y)
{
}

void Homework_1App::drawTriangle (int point1X, int point1Y, int point2X, int point2Y, int point3X, int point3Y)
{
}

void Homework_1App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_BASIC( Homework_1App, RendererGl )
