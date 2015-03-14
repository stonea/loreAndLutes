/*	Protected under the GNU General Public License read and see copying.txt for details
 * surface.h: defines ASFC_Surface and two helper functions: graphics_start and
 * 		graphics_stop
 */
 
#ifndef ASFC_SURFACE_H_
#define ASFC_SURFACE_H_

#include <iostream> //For my debuging purposes
#include <string>
#include <SDL.h>
#include <SDL_image.h>
//Dependencies
	#include "utils.h"
	
static int gSurfacesCreated = 0;
static int gSurfacesDeleted = 0;
static int gMemoryAllocated = 0;
static int gMemoryFreed = 0;

/* GraphicsStart return -1 fail, 0 if already running, 1 on success */
int GraphicsStart();
int GraphicsStop();

class ASFC_Surface {
	protected:
		SDL_Surface *mySurface;
		int myWidth;
		int myHeight;
		int myBpp;
		bool mySurfaceMade;
		bool myfOriginalSource;
		bool myfValidImageFile;
		void SurfaceCreate(); //This takes care of when an ASFC_Surface is created
				      //but SDL_Init has not been called yet
		
	public:
		//Constructors
		ASFC_Surface();
		ASFC_Surface(int width, int height, int bpp);
		void Init(int width, int height, int bpp);
		ASFC_Surface(SDL_Surface *surf);
		ASFC_Surface(ASFC_Surface *surf);
		ASFC_Surface(ASFC_Surface &surf);
		~ASFC_Surface();
		MEMVAR_SETGET(SetOriginalSource, OriginalSource, bool, myfOriginalSource);
		
		//Info grabbers
		SDL_Surface *GetSurface() {return mySurface;}
		int GetWidth() {return myWidth;}
		int GetHeight() {return myHeight;}
		int GetBpp() {return myBpp;}
		bool SurfaceMade() {return mySurfaceMade;}
		
		//Primitives and Blit functions
		int DrawPixel(int x, int y, int r, int g, int b, int a);
		int DrawLine(int x1, int y1, int x2, int y2, int r, int g, int b, int a);
		int DrawRectangle(int x, int y, int width, int height, int r, int g, int b, int a);
		int DrawFillRectangle(int x, int y, int width, int height, 
				      int r, int g, int b, int a);
		int DrawCircle(int x, int y, int radius, int r, int g, int b, int a);
		int DrawFillCircle(int x, int y, int radius, int r, int g, int b, int a);
		
		int LoadImage(string file, int transred = -1, int transgrn = -1, int transblu = -1);
		int LoadSurface(SDL_Surface *surf);
		int LoadSurface(ASFC_Surface &surf);
		
		void Blit(ASFC_Surface &surf, int x, int y, int sx = 0, int sy = 0, int w = -1, int h = -1);
		void Blit(SDL_Surface *surf, int x, int y, int sx = 0, int sy = 0, int w = -1, int h = -1);
		void BlitTo(ASFC_Surface &surf, int x, int y);
		
		virtual void Update();
		void operator=(ASFC_Surface &rhs);
};

void ViewDebugInfo();

#endif
