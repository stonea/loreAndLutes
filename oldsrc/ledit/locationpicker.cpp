/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			locationpicker.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "locationpicker.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//											LEDIT_LocationPicker
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_LocationPicker::LEDIT_LocationPicker()
{	//Create a fake lighting matrix that'll display all
		lNoLight.Resize(100, 100);
		for(int iY = 0; iY < 100; iY++)
			for(int iX = 0; iX < 100; iX++)
				lNoLight[iX][iY] = true;
}
//--------------------------------------------------------------------------------------------- [Picking] -
void LEDIT_LocationPicker::PickPoint(int* piX, int* piY)
{	myfExit = false;
 	//Draw
 		DrawQuickKeys();
		Draw();
	//Update till exit
		while(!myfExit)
		{	Update();
		}
	//Set returns
		*piX = CursorX();
		*piY = CursorY();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LEDIT_LocationPicker::SetStartLocation(int iX, int iY)
{	MoveViewportsTo(iX - PLAYFIELD_TILEWIDTH/2, iY - PLAYFIELD_TILEHEIGHT/2);
}
//P------------------------------------------------------------------------------------------- [Picking] -P
void LEDIT_LocationPicker::Update()
{	//Vars
		SDLKey iKey;
		SDLKey iMod;		
	//Get a key, Handle it
		iKey = GetKey(&iMod);
		HandleKey(iKey, iMod);
   	//Draw
 		DrawQuickKeys();
		Draw();
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
SDLKey LEDIT_LocationPicker::GetKey(SDLKey* piMod)
{	//Vars
		SDLKey tiKey = SDLKey(int(-1));
		SDLKey tiKey2 = SDLKey(int(-1));
		SDLKey iMod;

	//Grab a key
		while (tiKey == -1)
		{	myoInput.Update();
			tiKey = SDLKey(myoInput.GetKey(false, 250, 0));
			//HandleMouse();
		}
		
	//Check to see if we have a key modifier
		*piMod = MOD_NONE;
		myoInput.Update();
		if(myoInput.KeyDown(SDLK_LCTRL) || myoInput.KeyDown(SDLK_RCTRL))
		{	*piMod = MOD_CTRL;
			myoInput.Update();
			return SDLKey(int(-1));
		}

	//If we have a non repeatable key wait for it to be un pressed
	if(!(tiKey == KEY_MOVECUR_NORTH || tiKey ==	KEY_MOVECUR_NORTH2 || tiKey == KEY_MOVECUR_SOUTH ||
		 tiKey == KEY_MOVECUR_SOUTH2|| tiKey ==	KEY_MOVECUR_WEST   || tiKey == KEY_MOVECUR_WEST2 ||
		 tiKey == KEY_MOVECUR_EAST  || tiKey ==	KEY_MOVECUR_EAST2  || tiKey == KEY_MOVECUR_NRTHWST ||
		 tiKey == KEY_MOVECUR_NRTHEST||tiKey ==	KEY_MOVECUR_STHWST || tiKey == KEY_MOVECUR_STHEST ||
		 tiKey == SDLK_LCTRL  || tiKey == SDLK_RCTRL))
	{
		tiKey2 = tiKey;

		while(tiKey2 == tiKey || myoInput.KeyDown(tiKey))
		{	tiKey2 = SDLKey(myoInput.GetKey(false, 250, 0));
			myoInput.Update();
		}
	}
	
	//If the key is a repeat key (e.g. 8numpad and the up arrow key) map it to the original
		 	 if(tiKey == KEY_MOVECUR_NORTH2) tiKey = KEY_MOVECUR_NORTH;
		else if(tiKey == KEY_MOVECUR_SOUTH2) tiKey = KEY_MOVECUR_SOUTH;
		else if(tiKey == KEY_MOVECUR_WEST2)  tiKey = KEY_MOVECUR_WEST;
		else if(tiKey == KEY_MOVECUR_EAST2)  tiKey = KEY_MOVECUR_EAST;
		else if(tiKey == KEY_PICK2)			 tiKey = KEY_PICK;

	//Return this key
		return(tiKey);
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LEDIT_LocationPicker::HandleKey(SDLKey iKey, SDLKey iMod)
{	//Cntrl + 
		if(iMod == MOD_CTRL)
		{	//- [Move Screen ...] -
					 if(myoInput.KeyDown(KEY_MOVESCRN_NORTH)) 	MoveScreen(DIR_NORTH);
				else if(myoInput.KeyDown(KEY_MOVESCRN_NORTH2))	MoveScreen(DIR_NORTH);
				else if(myoInput.KeyDown(KEY_MOVESCRN_SOUTH)) 	MoveScreen(DIR_SOUTH);
				else if(myoInput.KeyDown(KEY_MOVESCRN_SOUTH2))	MoveScreen(DIR_SOUTH);
				else if(myoInput.KeyDown(KEY_MOVESCRN_WEST))  	MoveScreen(DIR_WEST);
				else if(myoInput.KeyDown(KEY_MOVESCRN_WEST2))	MoveScreen(DIR_WEST);
				else if(myoInput.KeyDown(KEY_MOVESCRN_EAST))  	MoveScreen(DIR_EAST);
				else if(myoInput.KeyDown(KEY_MOVESCRN_EAST2))	MoveScreen(DIR_EAST);
				else if(myoInput.KeyDown(KEY_MOVESCRN_NRTHWST))	MoveScreen(DIR_NORTH_WEST);
				else if(myoInput.KeyDown(KEY_MOVESCRN_NRTHEST))	MoveScreen(DIR_NORTH_EAST);
				else if(myoInput.KeyDown(KEY_MOVESCRN_STHWST))	MoveScreen(DIR_SOUTH_WEST);
				else if(myoInput.KeyDown(KEY_MOVESCRN_STHEST))	MoveScreen(DIR_SOUTH_EAST);		
		}
	//Nada +
		else
		{	//- [Move Cursor ...] -
					 if(iKey == KEY_MOVECUR_NORTH)		MoveViewports(DIR_NORTH);
				else if(iKey == KEY_MOVECUR_SOUTH)		MoveViewports(DIR_SOUTH);
				else if(iKey == KEY_MOVECUR_WEST)		MoveViewports(DIR_WEST);
				else if(iKey == KEY_MOVECUR_EAST)		MoveViewports(DIR_EAST);
				else if(iKey == KEY_MOVECUR_NRTHWST)	MoveViewports(DIR_NORTH_WEST);
				else if(iKey == KEY_MOVECUR_NRTHEST)	MoveViewports(DIR_NORTH_EAST);
				else if(iKey == KEY_MOVECUR_STHWST)		MoveViewports(DIR_SOUTH_WEST);
				else if(iKey == KEY_MOVECUR_STHEST)		MoveViewports(DIR_SOUTH_EAST);
			//- [Pick] -
				else if(iKey == KEY_PICK) myfExit = true;
		}
}
//P... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
void LEDIT_LocationPicker::Draw()
{	//Clear the screen
		mypoScreen->DrawFillRectangle(0, 50, 639, 479, COLOR_BLACK, 255);
	//Draw stats
		DrawStats();
	//Draw terrain, unit, and path finding maps
		mypoGame->TerrainMap().Draw(*mypoScreen, lNoLight);
		mypoPainter->DrawUnitMap(&lNoLight);
		mypoGame->PathNodes().Draw(*mypoScreen, CursorX() - PLAYFIELD_TILEWIDTH/2,
								 CursorY() - PLAYFIELD_TILEHEIGHT/2, PLAYFIELD_X, PLAYFIELD_Y);
 		RouteEditor()->DrawRoute(CursorX(), CursorY());
	 	
	//Draw consoles
		mypoPainter->Draw();
	//Draw cursor
		mypoPainter->Cursor().BlitTo(*mypoScreen,
  									(PLAYFIELD_X2 - PLAYFIELD_X)/2 - TILE_WIDTH/2  + PLAYFIELD_X,
									(PLAYFIELD_Y2 - PLAYFIELD_Y)/2 - TILE_HEIGHT/2 + PLAYFIELD_Y);
	//Update
		mypoScreen->Update();
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...  P
void LEDIT_LocationPicker::MoveViewports(ASFC_DIRECTION iDir)
{	//Vars
		int iX = mypoGame->TerrainMap().ViewX();
		int iY = mypoGame->TerrainMap().ViewY();

	//Offset the coods based on direction
		if(iDir == DIR_NORTH || iDir == DIR_NORTH_WEST || iDir == DIR_NORTH_EAST)	iY--;
		if(iDir == DIR_SOUTH || iDir == DIR_SOUTH_WEST || iDir == DIR_SOUTH_EAST)	iY++;
		if(iDir == DIR_WEST  || iDir == DIR_NORTH_WEST || iDir == DIR_SOUTH_WEST)	iX--;
		if(iDir == DIR_EAST  || iDir == DIR_NORTH_EAST || iDir == DIR_SOUTH_EAST)	iX++;

	//Now move there
		MoveViewportsTo(iX, iY);
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...  P
void LEDIT_LocationPicker::MoveViewportsTo(int iX, int iY)
{	//Only move to iX, iY if legal!
		if(iX >= -PLAYFIELD_TILEWIDTH/2 && iY >= -PLAYFIELD_TILEHEIGHT/2 &&
  		   iX < mypoGame->TerrainMap().Width()  - PLAYFIELD_TILEWIDTH/2 &&
       	   iY < mypoGame->TerrainMap().Height() - PLAYFIELD_TILEHEIGHT/2)
		{
		   	mypoGame->TerrainMap().SetViewX(iX);
		   	mypoGame->TerrainMap().SetViewY(iY);
 		}
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...  P
void LEDIT_LocationPicker::MoveScreen(ASFC_DIRECTION iDir)
{	//If we're dealing with a horizontal direction
		if(iDir == DIR_WEST || iDir == DIR_EAST)
		{	for(int i = 0; i < PLAYFIELD_TILEWIDTH/2; i++)
			{	MoveViewports(iDir);
			}
		}
	//If we're dealing with a vertical direction
		else if(iDir == DIR_NORTH || iDir == DIR_SOUTH)
		{	for(int i = 0; i < PLAYFIELD_TILEHEIGHT/2; i++)
			{	MoveViewports(iDir);
			}
		}
	//If we're dealing with a slanty direction
		else
		{	for(int i = 0; i < ((PLAYFIELD_TILEWIDTH/2) + (PLAYFIELD_TILEHEIGHT/2))/2; i++)
			{	MoveViewports(iDir);
			}
		}
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...  P
void LEDIT_LocationPicker::DrawStats()
{	//Clear the stats console and put our stats in
		mypoPainter->StatsConsole().Clear();
		mypoPainter->StatsConsole().CurrentFont(FONT_NORMAL);
		mypoPainter->StatsConsole() << "X: " << CursorX() << "\n";
		mypoPainter->StatsConsole() << "Y: " << CursorY() << "\n";
		mypoPainter->StatsConsole() << "\n";
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...  P
void LEDIT_LocationPicker::DrawQuickKeys()
{	//Be a good editor and always offer help
		mypoPainter->TalkConsole().Clear();
		mypoPainter->TalkConsole().CurrentFont(FONT_HIGHLIGHT);
		mypoPainter->TalkConsole() << "Pick a location:\n";
		mypoPainter->TalkConsole().CurrentFont(FONT_NORMAL);
		mypoPainter->TalkConsole() << "Space:  Pick\n";
		mypoPainter->TalkConsole() << "Arrows: Move\n";
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...  P
int LEDIT_LocationPicker::CursorX()
{	return(Game()->TerrainMap().ViewX() + PLAYFIELD_TILEWIDTH/2);
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...  P
int LEDIT_LocationPicker::CursorY()
{	return(Game()->TerrainMap().ViewY() + PLAYFIELD_TILEHEIGHT/2);
}
