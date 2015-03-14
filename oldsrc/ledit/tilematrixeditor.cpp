/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			tilematrixeditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	09/21/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//											Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "tilematrixeditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//										 LEDIT_TileMatrixEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_TileMatrixEditor::LEDIT_TileMatrixEditor()
{
}
//-------------------------------------------------------------------------------------------- [Editting] -
int LEDIT_TileMatrixEditor::ChooseTile()
{	//Set our selected tile
		myiSelected 	= 0;
		myiNumTiles		= 253;
	
	//Set grab option to include just the good ol default space and return
		int iKey = 0;
		ASFC_LinkedList<int> lChoosers;
		lChoosers.Push(KEY_CHOOSE);
		lChoosers.Push(KEY_CHOOSE2);
		
	//Now grab an option and return it
		return(GrabOption(&iKey, lChoosers));
}
//--------------------------------------------------------------------------------------------- [Drawing] -
void LEDIT_TileMatrixEditor::Draw()
{	//Vars (set iLoops to equal the first tile of the row where the cursor is at - 1/2 # of rows.)
		int iLoops = (myiSelected / PLAYFIELD_TILEWIDTH) * PLAYFIELD_TILEWIDTH 
					 - ((PLAYFIELD_TILEHEIGHT / 2) * PLAYFIELD_TILEWIDTH);
	 	myiTopLeftTile = iLoops;

	//Loop through the playfield
		for(int iY = 0; iY < PLAYFIELD_TILEHEIGHT; iY++)
		{	for(int iX = 0; iX < PLAYFIELD_TILEWIDTH; iX++)
			{	//If there's a tile here draw it
					if(iLoops >= 0 && iLoops < myiNumTiles)
        				DrawTile(iX * TILE_WIDTH + PLAYFIELD_X, iY * TILE_HEIGHT + PLAYFIELD_Y, iLoops);
  				//If no tile's here
  					else
  					{	//Draw an error image
							mypoPainter->Error1().BlitTo(*mypoScreen, iX * TILE_WIDTH + PLAYFIELD_X,
														 iY * TILE_HEIGHT + PLAYFIELD_Y);
  					}
				//If this tile is our selected one
					if(iLoops == myiSelected)
					{	//Draw the cursor
							mypoPainter->Cursor().BlitTo(*mypoScreen, iX * TILE_WIDTH + PLAYFIELD_X,
									 				   	 iY * TILE_HEIGHT + PLAYFIELD_Y);
					}
				
				//Increment loop counter
					iLoops++;
			}
		}
			
	//Draw the talk console
		mypoPainter->TalkConsole().Draw(0xFF);
		
	//Flip on the back buffer
		mypoScreen->Update();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LEDIT_TileMatrixEditor::DrawTile(int iX, int iY, int iTile)
{	//This should be overloaded
		mypoPainter->Error2().BlitTo(*mypoScreen, iX, iY);
}
//P------------------------------------------------------------------------------------------- [Editting] -
int LEDIT_TileMatrixEditor::GrabOption(int* piKey, ASFC_LinkedList<int> lChoosers)
{	//Draw all of our options
		Draw();
		
	//Reset the timer
		myoTimer.Reset();

	//Loop until a return is forced (e.g. forever)
		while(1 == 1)
		{	//Update our input info
				myoInput.Update();
				
    		//Decide what to do based on what key is down (if enough time has passed since the last press
    			if(myoTimer.Ellapsed(DELAY))
    			{	//Check for any clicks
    					if(myoInput.GetMouseButton(MOUSE_RIGHT))
    					{	while(myoInput.GetMouseButton(MOUSE_RIGHT))
    							myoInput.Update();
         					return(myiSelected);
    					}
    			
						if(myoInput.GetMouseButton(MOUSE_LEFT))
						{	//Translate this mouse position to a tile #
								int iMouseX = myoInput.GetMouseX();
								int iMouseY = myoInput.GetMouseY();
								int iTile = ((iMouseY - PLAYFIELD_Y) / TILE_HEIGHT) * PLAYFIELD_TILEWIDTH +
							 				((iMouseX - PLAYFIELD_X) / TILE_WIDTH) + myiTopLeftTile;
									 				
	 						//If legal switch to that tile
	 							if(iTile >= 0 && iTile < myiNumTiles)
	 								myiSelected = iTile;
			 						
							//Redraw
								Draw();
							//Reset the timer
								myoTimer.Reset();
						}
       
       				//- [Choose] -
    					for(int i = 0; i < 	lChoosers.Length(); i++)
    					{	if(myoInput.KeyDown(SDLKey(lChoosers[i])))
							{	//Wait until that key is released
									while(myoInput.KeyDown(SDLKey(lChoosers[i])))
       								{myoInput.Update();}
       								
								//Set the choosing key
									*piKey = lChoosers[i];
									
								//Return with the chosen option
									return(myiSelected);
							}
						}
					//- [Cancel] -
						if(myoInput.KeyDown(KEY_CANCEL))
						{	//Wait until that key is released
								while(myoInput.KeyDown(KEY_CANCEL)) {myoInput.Update();}

       						//Return our cancel option
								return(CANCEL);
						}
					//- [Previous] -
						else if(myoInput.KeyDown(KEY_PREVIOUS))
						{	//If we can choose a previous option, choose it
								if(myiSelected > 0)
									myiSelected--;
							//Redraw
								Draw();
							//Reset the timer
								myoTimer.Reset();
						}
					//- [Next] -
						else if(myoInput.KeyDown(KEY_NEXT))
						{	//If we can choose the next option, choose it
								if(myiSelected+1 < myiNumTiles)
									myiSelected++;
							//Redraw
								Draw();
							//Reset the timer
								myoTimer.Reset();
						}
					//- [Previous Row] -
						else if(myoInput.KeyDown(KEY_PREVIOUSROW))
						{	//If we can choose a previous option, choose it
								if(myiSelected - PLAYFIELD_TILEWIDTH >= 0)
									myiSelected -= PLAYFIELD_TILEWIDTH;
								else
									myiSelected = 0;
							//Redraw
								Draw();
							//Reset the timer
								myoTimer.Reset();
						}
					//- [Next Row] -
						else if(myoInput.KeyDown(KEY_NEXTROW))
						{	//If we can choose the next option, choose it
								if(myiSelected + PLAYFIELD_TILEWIDTH < myiNumTiles)
									myiSelected += PLAYFIELD_TILEWIDTH;
								else
									myiSelected = myiNumTiles - 1;
							//Redraw
								Draw();
							//Reset the timer
								myoTimer.Reset();
						}
				}
		}
}
