/*	Protected under the GNU General Public License read and see copying.txt for details
	 * * *                          \ | / Annex Solutions
	* ASFC *---------------------- -- + -- Foundation
	 * * *                          / | \    Classes

    File: effects.cpp
    By:   Andy Stone
    Desc:	
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "effects.h"

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 ASFC_Effects
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
ASFC_Effects::ASFC_Effects()
{
}/*
//--------------------------------------------------------------------------------------------- [Effects] -
void ASFC_Effects::FadeOutAndIn(ASFC_Surface oSurf1, ASFC_Surface oSurf2, ASFC_Screen &oScreen)
{	//Const
		const static int STEPS = 7;
		const static int SPEED = 25;

	//Draw surf1
		oSurf1.BlitTo(oScreen, 0, 0);
	//Fade out
		for(int i = 0; i < STEPS; i++)
		{	oTimer.Reset();
  			oScreen.DrawFillRectangle(0, 0, oScreen.GetWidth(), oScreen.GetHeight(), COLOR_BLACK,
     								  255/STEPS);
			oScreen.Update();
			oTimer.Delay(SPEED);
		}
		
		for(int i = 0; i < STEPS; i++)
		{	oSurf2.BlitTo(oScreen, 0, 0);
			oScreen.DrawFillRectangle(0, 0, oScreen.GetWidth(), oScreen.GetHeight(), COLOR_BLACK,
   									  255-i*(255/STEPS));
			oTimer.Delay(SPEED);
			oScreen.Update();
		}
	//Draw surf2
		oSurf2.BlitTo(oScreen, 0, 0);
		oScreen.Update();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Effects::Dissolve(ASFC_Surface oSurf1, ASFC_Surface oSurf2, ASFC_Screen &oScreen)
{	//Vars
		int iX, iY, iMinSteps;

	//Const
		const static int DISSOLVE_STEPS	= 100;
		const static int MINI_STEPS_MIN = 1;
		const static int MINI_STEPS_MAX = 5000;
		const static int MINI_STEPS_ACL = 150;
		const static int BLOCK_SIZE 	= 2;
		const static int SPEED			= 25;
		
	//Set the default # of mini steps
		iMinSteps = MINI_STEPS_MIN;
		
	//Blit Surface 1
		oSurf1.BlitTo(oScreen, 0, 0);

	//Do STEPS random blits
		for(int i = 0; i < DISSOLVE_STEPS; i++)
		{	oTimer.Reset();
		
			for(int j = 0; j < iMinSteps; j++)
  			{	iX = rand() % oScreen.GetWidth();
				iY = rand() % oScreen.GetHeight();
				oScreen.Blit(oSurf2, iX, iY, iX, iY, BLOCK_SIZE, BLOCK_SIZE);
			}
			
			//Increase # of ministeps
				if(iMinSteps < MINI_STEPS_MAX)
					iMinSteps += MINI_STEPS_ACL;
			
			oScreen.Update();
			oTimer.Delay(SPEED);
		}
		
	//Blit surface 2
		oSurf2.BlitTo(oScreen, 0, 0);
		oScreen.Update();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Effects::Triambulate(ASFC_Surface oSurf1, ASFC_Surface oSurf2, ASFC_Screen &oScreen)
{	//Vars
		int iX = 0;
		int iY = 0;
		
	//Draw surf1
		oSurf1.BlitTo(oScreen, 0, 0);
		
	//Preform the triambulation effect
		for(int i2 = 5; i2 > 0; i2--)
		{	iX = 0;
			iY = 0;
		
			while(iX < 640*3)
			{	if(iX < 640)
				{	oScreen.Blit(oSurf2, iX, iY, iX, iY, 640-iX - iX, 1);
				}
				else if (iX >= 640 & iX < 640*2)
				{	int iNX = iX - 640;
					int iNY = iY - 640;
					
					oScreen.Blit(oSurf2, iNX, iNY, iNX, iNY, iX, 1);
				}
				else
				{	int iNX = iX - 640*2;
					int iNY = iY - 640*2;
				
					oScreen.Blit(oSurf2, iNX, iNY, iNX, iNY, 1, 480);
				}
		
				if(iX % 50 == 0)	
					oScreen.Update();
			
				iX += i2;
				iY += i2;
			}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Effects::CheckerBoard(ASFC_Surface oSurf1, ASFC_Surface oSurf2, ASFC_Screen &oScreen)
{	//Vars
		int iRow = 0;
		int iBlockSize = 10;

	//Draw surf1
		oSurf1.BlitTo(oScreen, 0, 0);
	
	//Preform the checkerboard effect
		while(iRow < 2*(480 / iBlockSize))
		{	if(iRow < (480 / iBlockSize))
			{	for(int i = 0; i < 640 / iBlockSize; i++)
				{	if((i + iRow) % 2 == 0)
					{	oScreen.Blit(oSurf2, i * iBlockSize, iRow * iBlockSize, i * iBlockSize, iRow * iBlockSize,
   									iBlockSize, iBlockSize);
					}
				}
			}
			else
			{	for(int i = 0; i < 640 / iBlockSize; i++)
				{	if((i + iRow - (480 / iBlockSize)) % 2 != 0)
					{	oScreen.Blit(oSurf2, i * iBlockSize, (iRow- (480 / iBlockSize)) * iBlockSize,
    					i * iBlockSize, (iRow-(480 / iBlockSize)) * iBlockSize,
   									iBlockSize, iBlockSize);
					}
				}
			}
		
	  		oScreen.Update();
  			iRow++;
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Effects::Blend(ASFC_Surface oSurf1, ASFC_Surface oSurf2, ASFC_Screen &oScreen, int iSpeed, int iStep)
{	//Vars
		SDL_Rect src, dst;
  		int iFade = 0;
  		ASFC_Timer oTimer;

	//Draw surf1
		oSurf1.BlitTo(oScreen, 0, 0);
	//Loop through until we have a pure opaque oSurf2
		while(iFade < 0xFF)
		{	//Reset the timer
				oTimer.Reset();
  			//Set the transperancy of the second surface
				SDL_SetAlpha(oSurf2.GetSurface(), SDL_RLEACCEL | SDL_SRCALPHA, iFade);
			//Draw surf1
				oSurf1.BlitTo(oScreen, 0, 0);
  			//Draw surf2
				oSurf2.BlitTo(oScreen, 0, 0);
			//Update
				oScreen.Update();
				iFade += iStep;
			//Delay if necessary
				oTimer.Delay(iSpeed);
		}
	//Draw surf2
		oSurf2.BlitTo(oScreen, 0, 0);
		oScreen.Update();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Effects::SplitVert(ASFC_Surface oSurf1, ASFC_Surface oSurf2, ASFC_Screen &oScreen, int iSpeed, int iStep)
{	//Vars
		ASFC_LinkedList<ASFC_Effects_Image_Vector> oImages;
	//Resize the list to hold two images
		oImages.Resize(2);
	//Split Surf1 into two smaller images
		oImages[0].oSurf.Init(oScreen.GetWidth() / 2, oScreen.GetHeight(), 16);
		oImages[1].oSurf.Init(oScreen.GetWidth() / 2, oScreen.GetHeight(), 16);
		oImages[0].oSurf.Blit(oSurf1, 0, 0, 0, 0, oScreen.GetWidth() / 2, oScreen.GetHeight());
		oImages[1].oSurf.Blit(oSurf1, 0, 0, oScreen.GetWidth() / 2, 0, oScreen.GetWidth() / 2, oScreen.GetHeight());
	//Set up the vector information
		oImages[0].iX = (0);
		oImages[0].iY = (0);
		oImages[0].iDeltaX = (-iStep);
		oImages[0].iDeltaY = (0);
		oImages[1].iX = (oScreen.GetWidth() / 2);
		oImages[1].iY = (0);
		oImages[1].iDeltaX = (iStep);
		oImages[1].iDeltaY = (0);
	//While image 2 is still on the screen
		while(oImages[1].iX < oScreen.GetWidth())
		{	//Blit the background image
				oSurf2.BlitTo(oScreen, 0, 0);
  			//Blit and move the surfaces
				for(int i = 0; i < oImages.Length(); i++)
				{	oImages[i].oSurf.BlitTo(oScreen, oImages[i].iX, oImages[i].iY);
					oImages[i].iX += oImages[i].iDeltaX;
					oImages[i].iY += oImages[i].iDeltaY;
				}
			//Update the screen
				oScreen.Update();
				
			//Delay if necessary
				oTimer.Reset();
				oTimer.Delay(iSpeed);
		}
	//Draw surf2
		oSurf2.BlitTo(oScreen, 0, 0);
		oScreen.Update();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void ASFC_Effects::SplitHoriz(ASFC_Surface oSurf1, ASFC_Surface oSurf2, ASFC_Screen &oScreen, int iSpeed, int iStep)
{	//Vars
		ASFC_LinkedList<ASFC_Effects_Image_Vector> oImages;
	//Resize the list to hold two images
		oImages.Resize(2);
	//Split Surf1 into two smaller images
		oImages[0].oSurf.Init(oScreen.GetWidth(), oScreen.GetHeight() / 2, 16);
		oImages[1].oSurf.Init(oScreen.GetWidth(), oScreen.GetHeight() / 2, 16);
		oImages[0].oSurf.Blit(oSurf1, 0, 0, 0, 0, oScreen.GetWidth(), oScreen.GetHeight() / 2);
		oImages[1].oSurf.Blit(oSurf1, 0, 0, 0, oScreen.GetHeight() / 2, oScreen.GetWidth(), oScreen.GetHeight() / 2);
	//Set up the vector information
		oImages[0].iX = (0);
		oImages[0].iY = (0);
		oImages[0].iDeltaX = (0);
		oImages[0].iDeltaY = (-iStep);
		oImages[1].iX = (0);
		oImages[1].iY = (oScreen.GetHeight() / 2);
		oImages[1].iDeltaX = (0);
		oImages[1].iDeltaY = (iStep);
	//While image 2 is still on the screen
		while(oImages[1].iY < oScreen.GetHeight())
		{	//Blit the background image
				oSurf2.BlitTo(oScreen, 0, 0);
  			//Blit and move the surfaces
				for(int i = 0; i < oImages.Length(); i++)
				{	oImages[i].oSurf.BlitTo(oScreen, oImages[i].iX, oImages[i].iY);
					oImages[i].iX += oImages[i].iDeltaX;
					oImages[i].iY += oImages[i].iDeltaY;
				}
			//Update the screen
				oScreen.Update();

			//Delay if necessary
				oTimer.Reset();
				oTimer.Delay(iSpeed);
		}
	//Draw surf2
		oSurf2.BlitTo(oScreen, 0, 0);
		oScreen.Update();
}
*/
