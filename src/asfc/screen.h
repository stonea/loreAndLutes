//Protected under the GNU General Public License read and see copying.txt for details
#ifndef ASFC_SCREEN_H_
#define ASFC_SCREEN_H_

//Dependencies
	#include "utils.h"
	#include <SDL.h>
	#include <GL/gl.h>
	#include <GL/glu.h>

class ASFC_Screen
{
	public:
	//- [Construction] -
		ASFC_Screen();
		ASFC_Screen(int width, int height, int bpp, bool fullscreen = false);
		int Init(int width, int height, int bpp, bool fullscreen = false);
	//- [Primitives] -
		void DrawPixel(int x, int y, int r, int g, int b, int a = 0xFF);
		void DrawLine(int x1, int y1, int x2, int y2,
			int r, int g, int b, int a = 0xFF);
		void DrawRectangle(int x, int y, int width, int height,
			int r, int g, int b, int a = 0xFF);
		void DrawFillRectangle(int x, int y, int width, int height,
			int r, int g, int b, int a = 0xFF);
	//- [Buffering] -
		void Update();
	//- [Statistics] -
		MEMVAR_GET(Width,  int, _width);
		MEMVAR_GET(Height, int, _height);
		MEMVAR_GET(BPP,    int, _bpp);
		MEMVAR_GET(IsFullscreen, bool, _fullscreen);
		
	//Vars
		int  _width, _height, _bpp;
		bool _fullscreen;
};

#endif	
		
