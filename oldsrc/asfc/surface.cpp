//Protected under the GNU General Public License read and see copying.txt for details
#include "surface.h"
#include "SDL_gfxPrimitives.h"

static int started = 0;
static int users = 0;

//Functions
int GraphicsStart()
{
	int ret;
	
	DBG("In GraphicsStart()\n");
	if (started) {
		users++;
		ret = 0; //already started
		DBG("\tSDL already started. users is now: " << users << "\n");
	}
	else if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		ret = -1; //we had an error
		DBG("\tError starting SDL\n");
	} else {
		started = 1;
		ret = 1; //success!
		DBG("\tSDL started\n");
	}
	DBG("Leaving GraphicsStart()\n");
	return ret;
}

int GraphicsStop()
{
	int ret;
	
	DBG("In GraphicsStop()\n");
	if (started) {
		if (users > 0) {
			users--;
			ret = 0;
			DBG("\tSurfaces still alive. users is now: " << users << "\n");
		} else if (users == 0) {
			SDL_Quit();
			ViewDebugInfo();
			started = 0;
			ret = 1;
			DBG("\tSDL stopped\n");
		}
	} else {
		ret = -1;
		DBG("\tSDL is not started\n");
	}
	DBG("Leaving GraphicsStop()\n");
	return ret;
}

//Private/Protected methods
void ASFC_Surface::SurfaceCreate()
{
///!!! Might want to change to SDL_HWSurface???

	DBG("In ASFC_Surface::SurfaceCreate()\n");
	if (started) {
		mySurface = SDL_CreateRGBSurface(SDL_HWSURFACE, myWidth, myHeight, myBpp,
					 0, 0, 0, 0);
  		gMemoryAllocated += myWidth * myHeight * 2;
  		gSurfacesCreated++;
  		myfOriginalSource = true;
		mySurfaceMade = true;
	}
	DBG("Leaving ASFC_Surface::SurfaceCreate()\n");
}

//Constructors/Deconstructors
ASFC_Surface::ASFC_Surface()
	: myfOriginalSource(false)
{	myfValidImageFile = true;
	DBG("In ASFC_Surface::ASFC_Surface()\n");
	if (GraphicsStart() == -1) {
		DBG("Error starting graphics\n");
		return;
	}	
	mySurface = NULL;
	myWidth = myHeight = myBpp = 0;
	mySurfaceMade = false;
	DBG("Leaving ASFC_Surface::ASFC_Surface()\n");
}

ASFC_Surface::ASFC_Surface(int width, int height, int bpp)
	: myfOriginalSource(false)
{
	DBG("In ASFC_Surface::ASFC_Surface(int, int, int)\n");
	if (GraphicsStart() == -1) {
		DBG("Error starting graphics\n");
		return;
	}
	mySurface = NULL;
	myWidth = width;
	myHeight = height;
	myBpp = bpp;
	mySurfaceMade = false;
	DBG("Leaving ASFC_Surface::ASFC_Surface(int, int, int)\n");
}

void ASFC_Surface::Init(int width, int height, int bpp)
{	myfOriginalSource = false;
	if (GraphicsStart() == -1) {
		DBG("Error starting graphics\n");
		return;
	}
	mySurface = NULL;
	myWidth = width;
	myHeight = height;
	myBpp = bpp;
	mySurfaceMade = false;
}

ASFC_Surface::ASFC_Surface(SDL_Surface *surf)
	: myfOriginalSource(false)
{
	DBG("In ASFC_Surface::ASFC_Surface(SDL_Surface*)\n");
	if (GraphicsStart() == -1) {
		DBG("Error starting graphics\n");
		return;
	}
	this->LoadSurface(surf);
	DBG("Leaving ASFC_Surface::ASFC_Surface(SDL_Surface*)\n");
}

ASFC_Surface::ASFC_Surface(ASFC_Surface *surf)
	: myfOriginalSource(false)
{
	DBG("In ASFC_Surface::ASFC_Surface(ASFC_Surface*)\n");
	if (GraphicsStart() == -1) {
		DBG("Error starting graphics\n");
		return;
	}
	this->LoadSurface(surf->GetSurface());
	DBG("Leaving ASFC_Surface::ASFC_Surface(ASFC_Surface*)\n");
}

ASFC_Surface::ASFC_Surface(ASFC_Surface &surf)
	: myfOriginalSource(false)
{
	DBG("In ASFC_Surface::ASFC_Surface(ASFC_Surface&)\n");
	if (GraphicsStart() == -1) {
		DBG("Error starting graphics\n");
		return;
	}
	this->LoadSurface(surf);
	DBG("Leaving ASFC_Surface::ASFC_Surface(ASFC_Surface&)\n");
}

ASFC_Surface::~ASFC_Surface()
{
	DBG("In ASFC_Surface::~ASFC_Surface()\n");
	if (mySurfaceMade && myfOriginalSource)
	{
 		if (mySurface->refcount == 1)
		{	gMemoryFreed += mySurface->w * mySurface->h  * 2;
  			SDL_FreeSurface(mySurface);
			gSurfacesDeleted++;
		}
	}
	GraphicsStop();
	DBG("Leaving ASFC_Surface::~ASFC_Surface()\n");
}

//Public methods
//Primitives
int ASFC_Surface::DrawPixel(int x, int y, int r, int g, int b, int a)
{
	DBG("In ASFC_Surface::DrawPixel(int, int, int, int, int, int)\n");
	if (!mySurfaceMade)
		this->SurfaceCreate();
	fastPixelRGBA(mySurface, x, y, r, g, b, a);
	DBG("Leaving ASFC_Surface::DrawPixel(int, int, int, int, int, int)\n");
}

int ASFC_Surface::DrawLine(int x1, int y1, int x2, int y2, int r, int g, int b, int a)
{
	DBG("In ASFC_Surface::DrawLine(int, int, int, int, int, int, int, int)\n");
	if (!mySurfaceMade)
		this->SurfaceCreate();
	lineRGBA(mySurface, x1, y1, x2, y2, r, g, b, a);
	DBG("Leaving ASFC_Surface::DrawLine(int, int, int, int, int, int, int, int)\n");
}

int ASFC_Surface::DrawRectangle(int x, int y, int width, int height, int r, int g, int b, int a)
{
	DBG("In ASFC_Surface::DrawRectangle(int, int, int, int, int, int, int, int)\n");
	if (!mySurfaceMade)
		this->SurfaceCreate();
	rectangleRGBA(mySurface, x, y, x + width, y + height, r, g, b, a);
	DBG("Leaving ASFC_Surface::DrawRectangle(int, int, int, int, int, int, int, int)\n");
}

int ASFC_Surface::DrawFillRectangle(int x, int y, int width, int height, int r, int g, int b, int a)
{
	DBG("In ASFC_Surface::DrawFillRectangle(int, int, int, int, int, int, int, int)\n");
	if (!mySurfaceMade)
		this->SurfaceCreate();
	boxRGBA(mySurface, x, y, x + width, y + height, r, g, b, a);
	DBG("Leaving ASFC_Surface::DrawFillRectangle(int, int, int, int, int, int, int, int)\n");
}

int ASFC_Surface::DrawCircle(int x, int y, int radius, int r, int g, int b, int a)
{
	DBG("In ASFC_Surface::DrawCircle(int, int, int, int, int, int, int)\n");
	if (!mySurfaceMade)
		this->SurfaceCreate();
	circleRGBA(mySurface, x, y, radius, r, g, b, a);
	DBG("Leaving ASFC_Surface::DrawCircle(int, int, int, int, int, int, int)\n");
}

int ASFC_Surface::DrawFillCircle(int x, int y, int radius, int r, int g, int b, int a)
{
	DBG("In ASFC_Surface::DrawFillCircle(int, int, int, int, int, int, int)\n");
	if (!mySurfaceMade)
		this->SurfaceCreate();
	filledCircleRGBA(mySurface, x, y, radius, r, g, b, a);
	DBG("Leaving ASFC_Surface::DrawFillCircle(int, int, int, int, int, int, int)\n");
}

int ASFC_Surface::LoadImage(string file, int transred, int transgrn, int transblu)
{	int iReturn;

	DBG("In ASFC_Surface::LoadImage()\n");
	if (!mySurfaceMade)
		this->SurfaceCreate();
	SDL_Surface *tmp;
	tmp = IMG_Load(file.c_str());

	//If no image was created make one;  Why do we do this?!
 		if(tmp == NULL)
   		{	tmp = SDL_CreateRGBSurface(SDL_HWSURFACE, 0,0, myBpp, 0, 0, 0, 0);
   			gSurfacesCreated++;
	    }	
	if (transred != -1 || transgrn != -1 || transblu != -1) {
		DBG("\tCalling SDL_SetColorKey\n");
			SDL_SetColorKey(tmp, SDL_SRCCOLORKEY, SDL_MapRGB(tmp->format, transred, transgrn, transblu));
		DBG("\tFinished SDL_SetColorKey\n");
	}

	iReturn = LoadSurface(SDL_DisplayFormat(tmp));
	
	//*AIS You forgot to free the temp surface!
		SDL_FreeSurface(tmp);
	
	DBG("Leaving ASFC_Surface::LoadImage()\n");
	return(iReturn);
}

int ASFC_Surface::LoadSurface(ASFC_Surface &surf)
{
	return this->LoadSurface(surf.GetSurface());
}

int ASFC_Surface::LoadSurface(SDL_Surface *surf)
{	if (surf == NULL)
		return 0;
	mySurface = surf;
	myWidth = surf->w;
	myHeight = surf->h;
	myBpp = surf->format->BitsPerPixel;
	mySurfaceMade = true;
	gMemoryAllocated += surf->w * surf->h * 2;
	
	return 1;
}

//Blit and Update
void ASFC_Surface::Blit(ASFC_Surface &surf, int x, int y, int sx, int sy, int w, int h)
{	if (!mySurfaceMade)
		this->SurfaceCreate();
		
	this->Blit(surf.GetSurface(), x, y, sx, sy, w, h);
}

void ASFC_Surface::Blit(SDL_Surface *surf, int x, int y, int sx, int sy, int w, int h)
{
	DBG("In ASFC_Surface::Blit(ASFC_Surface*, int, int, int, int)\n");
	if (!mySurfaceMade)
		this->SurfaceCreate();
	
	SDL_Rect src, dst;
	
	src.x = sx;
	src.y = sy;
	if (w != -1)
		src.w = w;
	else
		src.w = surf->w;
	if (h != -1)
		src.h = h;
	else
		src.h = surf->h;
	
	dst.x = x;
	dst.y = y;
	dst.w = mySurface->w;
	dst.h = mySurface->h;
	
	SDL_BlitSurface(surf, &src, mySurface, &dst);
	
	DBG("Leaving ASFC_Surface::Blit(ASFC_Surface*, int, int, int, int)\n");
}

//*AIS
void ASFC_Surface::BlitTo(ASFC_Surface &surf, int x, int y)
{	surf.Blit(*this, x, y);
}

void ASFC_Surface::Update()
{
	DBG("In ASFC_Surface::Update()\n");
	if (mySurfaceMade)
		SDL_UpdateRect(mySurface, 0, 0, 0, 0);
	DBG("Leaving ASFC_Surface::Update()\n");
}

//operator =
void ASFC_Surface::operator=(ASFC_Surface &rhs)
{
	DBG("In ASFC_Surface::Equals(ASFC_Surface &)\n");
	this->LoadSurface(rhs);
	DBG("Leaving ASFC_Surface::Equals(ASFC_Surface &)\n");

}

void ViewDebugInfo()
{	cerr << "Surfaces made:    " << gSurfacesCreated << endl;
	cerr << "Surfaces deleted: " << gSurfacesDeleted << endl;
	cerr << "Memory allocated: " << gMemoryAllocated << endl;
	cerr << "Memory freed:     " << gMemoryFreed << endl;
}
