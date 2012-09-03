/*
*	@author Nicholas Uth
*	Program written to produce an image of some cards using basic shapes.
*	
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

  private:

	//Width and height of the screen
	static const int kAppWidth=800;
	static const int kAppHeight=600;
	static const int kTextureSize=1024;
};

void Homework_1App::setup()
{
}

void Homework_1App::mouseDown( MouseEvent event )
{
}

void Homework_1App::update()
{
}

void Homework_1App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_BASIC( Homework_1App, RendererGl )
