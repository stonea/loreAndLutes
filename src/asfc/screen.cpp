//Protected under the GNU General Public License read and see copying.txt for details
#include "screen.h"

//-------------------------------------------------------- [Construction] -
ASFC_Screen::ASFC_Screen()
{
	//Initilize the screen to a default 640x480x8bpp
		Init(640, 480, 8);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
ASFC_Screen::ASFC_Screen(int width, int height, int bpp, bool fullscreen)
{
	//Initilize the screen
		Init(width, height, bpp, fullscreen);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int ASFC_Screen::Init(int width, int height, int bitsPerPixel, bool fullscreen)
{
	//Vars	
		Uint32 bpp, flags;
		
	//Set the object to remember these states
		_width  	= width;
		_height 	= height;
		_bpp    	= bitsPerPixel;
		_fullscreen = fullscreen;
	//Startup SDL video
		if(SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			cerr << "Error starting SDL video.\n";
			exit(-1);
		}
	//Set SDLs flags based on the parameters passed and whether OpenGL is being used or not
		if(fullscreen)
		{	
			flags = SDL_OPENGL | SDL_FULLSCREEN;
		}
		else
		{
			flags = SDL_HWSURFACE | SDL_HWACCEL | SDL_DOUBLEBUF | SDL_OPENGL;
		}
	//Set OpenGL attributes
	    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,     5);
   		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,   5);
    	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,    5);
	    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,   16);
	    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//Insure that this is a valid video mode
		if((bpp = SDL_VideoModeOK(width, height, bitsPerPixel, flags)) == 0)
		{
			cerr << "\tVideo mode not supported: " << SDL_GetError() << "\n";
			return 0;
		}
	//Change to this video mode
		//if((mySurface = SDL_SetVideoMode(width, height, bpp, flags)) == NULL)
		if(SDL_SetVideoMode(width, height, bpp, flags) == NULL)
		{
			cerr << "\tError setting video mode: " << "\n";
			return 0;
		}	
	//Setup OpenGL	
		glViewport(0, 0, width, height);
    	glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    	glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
    	glClearDepth(1.0);
    	glDepthFunc(GL_LESS);
    	glEnable(GL_DEPTH_TEST);
    	glDisable(GL_DEPTH_TEST);
    	glShadeModel(GL_SMOOTH);
    	glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();
    	glMatrixMode(GL_MODELVIEW);
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glOrtho(0, width, height, 0, 0, 1);
		glPointSize(1);
	return 1;
}
//---------------------------------------------------------- [Primitives] -
void ASFC_Screen::DrawPixel(int x, int y, int r, int g, int b, int a)
{
	//Draw a pixel using GL
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_POINTS);
			glColor4f(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
			glVertex2f(x + 0.5, y + 0.5);
		glEnd();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Screen::DrawLine(int x1, int y1, int x2, int y2,
	int r, int g, int b, int a)
{
	//Draw a line using OpenGL
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_LINES);
			glColor4f(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
			glVertex2f(x1, y1);
			glVertex2f(x2 + 0.5, y2 + 0.5);
		glEnd();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Screen::DrawRectangle(int x, int y, int width, int height,
	int r, int g, int b, int a)
{
	//Just draw the rectangle's lines (top, bottom, left, right)
	//Insure that lines don't overlap by having the left and right line -
	//- segments offset by 1px.
		glDisable(GL_TEXTURE_2D);
		DrawLine(x, y, x + width, y, r, g, b, a);
		DrawLine(x, y + height, x + width, y + height, r, g, b, a);
		DrawLine(x, y + 1, x, y + height - 1, r, g, b, a);
		DrawLine(x + width, y + 1, x + width, y + height - 1, r, g, b, a);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Screen::DrawFillRectangle(int x, int y, int width, int height,
	int r, int g, int b, int a)
{
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
		glColor4f(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
		glVertex2f(x, y);
		glVertex2f(x + width, y);
		glVertex2f(x + width, y + height);
		glVertex2f(x, y + height);
	glEnd();
}
//----------------------------------------------------------- [Buffering] -
void ASFC_Screen::Update()
{
	glFlush();
   	glClearDepth(1.0);
	SDL_GL_SwapBuffers();
}
