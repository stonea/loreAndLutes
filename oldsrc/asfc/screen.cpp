//Protected under the GNU General Public License read and see copying.txt for details
#include "screen.h"

ASFC_Screen::ASFC_Screen()
{
	DBG("In ASFC_Screen::ASFC_Screen()\n");
	DBG("Leaving ASFC_Screen::ASFC_Screen()\n");
}

ASFC_Screen::ASFC_Screen(int width, int height, int bpp, bool fullscreen)
{
	DBG("In ASFC_Screen::ASFC_Screen(int, int, int)\n");
	this->Init(width, height, bpp, fullscreen);
	DBG("Leaving ASFC_Screen::ASFC_Screen(int, int, int)\n");
	
	myWidth  = width;
	myHeight = height;
}

ASFC_Screen::~ASFC_Screen()
{
	DBG("In ASFC_Screen::~ASFC_Screen()\n");
	DBG("Leaving ASFC_Screen::~ASFC_Screen()\n");
}

int ASFC_Screen::Init(int width, int height, int BitsPerPixel, bool fullscreen)
{
	DBG("In ASFC_Screen::Init(int, int, int)\n");
	
	Uint32 bpp, flags;
	
	if(fullscreen)
		flags = SDL_SWSURFACE | SDL_FULLSCREEN;
	else
		flags = SDL_SWSURFACE | SDL_DOUBLEBUF;
	
	if ((bpp = SDL_VideoModeOK(width, height, BitsPerPixel, flags)) == 0)  {
		DBG("\tVideo mode not supported: " << SDL_GetError() << "\n");
		return 0;
	} else {
		DBG("\tUsing "  "bpp\n");
	}
	
	if ((mySurface = SDL_SetVideoMode(width, height, bpp, flags)) == NULL) {
		DBG("\tError setting video mode: " << "\n");
		return 0;
	}
	
	mySurfaceMade = true;
	myBpp = bpp;
	
	myWidth  = width;
	myHeight = height;
	
	DBG("Leaving ASFC_Screen::Init(int, int, int)\n");
	return 1;
}

void ASFC_Screen::Update()
{
	DBG("In ASFC_Screen::Update()\n");
	SDL_Flip(mySurface);
	DBG("Leaving ASFC_Screen::Update()\n");
}
