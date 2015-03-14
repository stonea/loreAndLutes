/*
	ASFC_Screen screen(640, 480, 32, false);
	ASFC_Input input;
	ASFC_Font font(8, 13, COLOR_BLUE);
	font.Load("fonts/normal_console_font.png");
	ASFC_Console con;
	con.SetFont(&font);
	for(int i = 0; i < 100; i++)
	{
		con.Writeln(s, 0);
	}
	con.Draw(screen);*/
/*	screen.DrawFillRectangle(50, 50, 100, 100, COLOR_RED, 0xFF);
	screen.Update();
	input.Update();
	input.Pause();
*/


/*	Protected under the GNU General Public License read and see copying.txt for details
ASFC Effects*/


#include <time.h>
#include <stdlib.h>
#include "screen.h"
#include "image.h"
#include "input.h"
#include "animation.h"
#include "mousepointer.h"
#include "font.h"
#include "matrix.h"
#include "console.h"
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

int main(int argc, char *argv[])
{
	ASFC_LinkedList<int> list;
	list.Resize(13, 0);

	for (int i = 0; i < list.Length(); i++)
		cout << list[i] << ". ";
	cout << endl;
/*
	ASFC_Screen screen(640, 480, 32, false);
	ASFC_Animation animation(32, 32);
	ASFC_Input input;
	animation.Load("test.png");
	animation.Draw(screen, 50, 50, 0);
	screen.Update();
*/
/*
	ASFC_Font font(8, 13, COLOR_BLUE);
	font.Load("fonts/normal_console_font.png");
	ASFC_Console con(&screen, &font, 50, 30);
	
	string s;
	char c;
	double d;
	int i;
	
	for (int i = 0; i < 10000; i++)
	{
		con << i << "\n";
		con.Draw();
		screen.Update();
	}
	con << "Enter a string: ";
	con >> s;
	con << "\nEnter a char: ";
	con >> c;
	con << "\nEnter a double: ";
	con >> d;
	con << "\nEnter an int: ";
	con >> i;
	con << "\n";
	con << "S = " << s << "\n";
	con << "C = " << c << "\n";
	con << "D = " << d << "\n";
	con << "I = " << i << "\n";
	
	con.Draw();
	screen.Update();
*/
	//input.Update();
	//input.Pause();
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
