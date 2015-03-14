/*	Protected under the GNU General Public License read and see copying.txt for details
ASFC Effects*/



#include <time.h>
#include <stdlib.h>
#include "screen.h"
#include "multiimage.h"

#include "linkedlist.h"
#include "font.h"
#include "fontpalette.h"
#include "console.h"
#include "mousepointer.h"

#include "effects.h"
#include "sound.h"

#include "SDL_gfxPrimitives.h"
#include "linkedlist.h"


void New2();
void New();
void CheckBoard();
void Zoom();
void Shade();
void Swipe();
void Fade();

#include <vector>
using namespace std;

class cOther
{	public:
};

class cTemp
{	public:
	ASFC_LinkedList<cOther> liTemps;
};

int main(int argc, char *argv[])
{	//Init
		ASFC_Screen oScreen(800, 600, 16);
		oScreen.Update();
		
ASFC_LinkedList<cTemp> liInts;
liInts.Resize(liInts.Length() + 1);

	ASFC_Input oInput;
	double dRand;
	int iX, iY, iW, iH, iR, iB, iG;

	int iLoops = 0;
	
	while(!oInput.KeyDown(SDLK_ESCAPE))
	{	dRand = ((double)rand() / (double)(RAND_MAX+1));	iX    = int(dRand * 800);
		dRand = ((double)rand() / (double)(RAND_MAX+1));	iY    = int(dRand * 600);
		dRand = ((double)rand() / (double)(RAND_MAX+1));	iW    = int(dRand * 800);
		dRand = ((double)rand() / (double)(RAND_MAX+1));	iH    = int(dRand * 600);
		dRand = ((double)rand() / (double)(RAND_MAX+1));	iR    = int(dRand * 0xFF);
		dRand = ((double)rand() / (double)(RAND_MAX+1));	iG    = int(dRand * 0xFF);
		dRand = ((double)rand() / (double)(RAND_MAX+1));	iB    = int(dRand * 0xFF);
 
 		iX = 0;
 		iY = 0;
 		iW = iLoops;
 		iH = iLoops;
 
		//oScreen.DrawFillRectangle(iX, iY, iW, iH, iR, iG, iB, 0xFF);
 		SDL_Rect dst;
		dst.x = iX;
		dst.y = iY;
		dst.w = iW;
		dst.h = iH;
 		
   		SDL_FillRect(oScreen.GetSurface(), &dst, ((Uint32)iR << 24) | ((Uint32)iG << 16) | ((Uint32)iB << 8) | (Uint32)0xFF);
		oScreen.Update();
	
		oInput.Update();
		iLoops++;
	}


/*
	ASFC_Sound oSound;
	oSound.Init();
	//oSound.LoadMusic("VLLIFE.MID");
	oSound.LoadMusic("VLLIFE.MID");
	oSound.PlayMusic();

	oSound.StopMusic();
*/
}
/*
void CheckBoard()
{	SDL_Event event;
	bool done = false;
	srand(time(NULL));
	
	ASFC_Screen screen(640, 480, 32);	
	
	ASFC_Surface oCircle(SDL_LoadBMP("./test.bmp"));

	int iRow = 0;
	int iBlockSize = 3;

	while (!done) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYDOWN:     
					switch (event.key.keysym.sym) {
						case SDLK_q:
							done = true;
							break;
					}
			}
		}
		
		if(iRow < (480 / iBlockSize))
		{	for(int i = 0; i < 640 / iBlockSize; i++)
			{	if((i + iRow) % 2 == 0)
				{	screen.Blit(oCircle, i * iBlockSize, iRow * iBlockSize, i * iBlockSize, iRow * iBlockSize,
   								iBlockSize, iBlockSize);
				}
			}
		}
		else
		{	for(int i = 0; i < 640 / iBlockSize; i++)
			{	if((i + iRow - (480 / iBlockSize)) % 2 != 0)
				{	screen.Blit(oCircle, i * iBlockSize, (iRow- (480 / iBlockSize)) * iBlockSize,
    				i * iBlockSize, (iRow-(480 / iBlockSize)) * iBlockSize,
   								iBlockSize, iBlockSize);
				}
			}
		}
		
  		screen.Update();
  		iRow++;
	}
}

void Zoom()
{
	SDL_Event event;
	bool done = false;
	
	srand(time(NULL));
	
	ASFC_Screen screen(640, 480, 32);	
	
ASFC_Surface oCircle(SDL_LoadBMP("./test.bmp"));

int iRad = 0;

	while (!done) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_q:
							done = true;
							break;
					}
			}
		}
		
		int iCX = 640/2;
		int iCY = 480/2;
		
		screen.Blit(oCircle, iCX - iRad, iCY- iRad, iCX - iRad, iCY - iRad, iRad*2, iRad*2);
  		screen.Update();
  		iRad+= 2;
	}
}


void Shade()
{
	SDL_Event event;
	bool done = false;
	
	srand(time(NULL));
	
	ASFC_Screen screen(640, 480, 32);	
	
ASFC_Surface oCircle(SDL_LoadBMP("./test.bmp"));

int iY = 0;

	while (!done) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_q:
							done = true;
							break;
					}
			}
		}


		iY = rand() % 480;
		
		screen.Blit(oCircle, 0, iY, 0, iY, 640, 2);
  		screen.Update();
	}
}

void Swipe()
{
	SDL_Event event;
	bool done = false;
	
	srand(time(NULL));
	
	ASFC_Screen screen(640, 480, 32);	
	
ASFC_Surface oCircle(SDL_LoadBMP("./test.bmp"));

int iX = 0;
int iY = 0;

	while (!done) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_q:
							done = true;
							break;
					}
			}
		}

		screen.DrawFillRectangle(0, 0, 640, 480, 0, 0, 0, 255);
		screen.Blit(oCircle, iX, iY, 0, 0, 640, 480);
  		screen.Update();
  		
  		iY+= 5;
	}
}
void Fade()
{
	SDL_Event event;
	bool done = false;
	
	srand(time(NULL));
	
	ASFC_Screen screen(640, 480, 32);	
	
ASFC_Surface oCircle(SDL_LoadBMP("./test.bmp"));

	while (!done) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_q:
							done = true;
							break;
					}
			}
		}
	int iX;
	int iY;
	for(int i = 0; i < 500; i++)
	{	iX = rand() % 640;
		iY = rand() % 480;
		screen.Blit(oCircle, iX, iY, iX, iY, 4, 4);
	}

  		screen.Update();
	}
}


void New()
{
	SDL_Event event;
	bool done = false;
	
	srand(time(NULL));
	
	ASFC_Screen screen(640, 480, 32);	
	
ASFC_Surface oCircle(SDL_LoadBMP("./test.bmp"));

	int iX = 0;
	int iY = 0;

	while (!done) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_q:
							done = true;
							break;
					}
			}
		}


for(int i2 = 5; i2 > 0; i2--)
{	iX = 0;
	iY = 0;
	
	while(iX < 640*3)
	{
		if(iX < 640)
		{	screen.Blit(oCircle, iX, iY, iX, iY, 640-iX - iX, 1);
		}
		else if (iX >= 640 & iX < 640*2)
		{	int iNX = iX - 640;
			int iNY = iY - 640;
			
			screen.Blit(oCircle, iNX, iNY, iNX, iNY, iX, 1);
		}
		else
		{	int iNX = iX - 640*2;
			int iNY = iY - 640*2;
			
			screen.Blit(oCircle, iNX, iNY, iNX, iNY, 1, 480);
		}
		
		if(iX % 50 == 0)	
			screen.Update();
			
		iX += i2;
		iY += i2;
	}
}
}

}


void New2()
{	SDL_Event event;
	bool done = false;
	
	srand(time(NULL));
	
	ASFC_Screen screen(640, 480, 32);	
	
ASFC_Surface oCircle(SDL_LoadBMP("./test.bmp"));

int iX = 0;
int iY = 1;

		for(int i = 0; i < 50; i++)
		{  	iY = 0;
			for(int iOff = 0; iOff < 480; iOff++)
			{	iX = rand() % 640;
  
  				screen.Blit(oCircle, iX, iY + iOff, iX, iY + iOff, 640, 1);
		
				iY = int(iY *= 1.9);
				if(iOff % 25 == 0)
					screen.Update();
			}
		}
		
		screen.Blit(oCircle, 0, 0);
		screen.Update();

	while (!done)
 	{	while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_q:
							done = true;
							break;
					}
			}
		}
		
		screen.Update();
	}
}
*/
