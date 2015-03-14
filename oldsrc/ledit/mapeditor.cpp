/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			mapeditor.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	01/01/03 20:52
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "mapeditor.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//			 									 LEDIT_MapEditor
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_MapEditor::LEDIT_MapEditor()
	: myiCursorLayer(3)
{	//Create a fake lighting matrix that'll display all
		lNoLight.Resize(100, 100);
		for(int iY = 0; iY < 100; iY++)
			for(int iX = 0; iX < 100; iX++)
				lNoLight[iX][iY] = true;
	//Load the logo
		myoLogo.LoadImage(LEDIT_MapEditor__Logo_Image);
	//Set defaults
		myfBattleEdit = false;
	    myiBattleEdgeX1 = 45;
		myiBattleEdgeY1 = 5;
		myiBattleEdgeX2 = 55;
		myiBattleEdgeY2 = 15;
		myfHighlightUnits = false;
		myfUpdateButtons  = true;
}
//-------------------------------------------------------------------------------------------- [Editting] -
LEDIT_MapEditor::LEDIT_TestInformation LEDIT_MapEditor::Edit(int iX, int iY)
{	//Vars
		LEDIT_TestInformation oInfo;

	//Reset the state
		myiCurrentState 	= MAPEDIT_STATE_GOOD;
		myiSelectedTerrain	= 0;
		myfPenDown			= false;
		myfRouteEditting	= false;
		myfLayingArea		= false;
		iCopyX = 0;
  		iCopyY = 0;
		mypoGame->SetInBattleMode(false);
		myoTimer.Reset();
	//Move the cursor if necessary
		if(iX != -1)
		{	Game()->TerrainMap().SetViewX(iX - PLAYFIELD_TILEWIDTH/2);
			Game()->TerrainMap().SetViewY(iY - PLAYFIELD_TILEWIDTH/2);
		}
	//Redraw
		Draw();
	//While we're good keep on chuggin the editor
		while(myiCurrentState == MAPEDIT_STATE_GOOD)
		{	Update();
		}
		
		if(myiCurrentState == MAPEDIT_STATE_TEST)
		{	oInfo.fTest = true;
			oInfo.iMap	= mypoGame->CurrentMap();
			oInfo.iX	= CursorX();
			oInfo.iY	= CursorY();
		}
		
		return(oInfo);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LEDIT_MapEditor::SwitchMap(int iNewMap)
{	//Clear out old classes and load in the battle information
		mypoGame->SetInBattleMode(true);
		mypoGame->LoadMap(-1);
		mypoGame->LoadClasses("", mypoScreen);
		mypoGame->SetInBattleMode(false);
	//Always turn off battle edit mode unless we're switching to a battle map < 0
		if(iNewMap >= 0)
		{	myfBattleEdit = false;
			mypoGame->SetInBattleMode(false);
		}
		else
		{	myfBattleEdit = true;
			mypoGame->SetInBattleMode(true);
			myfRouteEditting = false;
		}
	//Load the map and classes
		mypoGame->LoadMap(iNewMap);
		mypoGame->LoadClasses("", mypoScreen);
}
//----------------------------------------------------------------------------------------- [Map Settings] -
void LEDIT_MapEditor::SetGame(LL_Game* poGame)
{	mypoGame = poGame;
	mypoPathNodes = &Game()->PathNodes();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_SETGET(SetGame, Game, LL_Game*, mypoGame);
//P------------------------------------------------------------------------------------------- [Editting] -P
void LEDIT_MapEditor::Update()
{	//Vars
		SDLKey iKey;
		SDLKey iMod;
	//Get a key, Handle it
		iKey = GetEdittingKey(&iMod);
		HandleEdittingKey(iKey, iMod);
	//If the pen is down plot
 		if(myfPenDown)
 			Game()->TerrainMap().Set(CursorX(), CursorY(), myiSelectedTerrain);
   	//Draw
   		DrawQuickKeys();
		Draw();
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...  p
bool LEDIT_MapEditor::HandleMouse()
{	//If the user is clicking
		if(myoInput.GetMouseButton(MOUSE_LEFT) || myoInput.GetMouseButton(MOUSE_RIGHT))
		{	//Draw quick keys
				DrawQuickKeys();
				
			//Pause
				ASFC_Timer oTime;
				oTime.Reset();
				oTime.Delay(10);
				myoInput.Update();
				
			//Get the position
				int iMouseX = myoInput.GetMouseX();
				int iMouseY = myoInput.GetMouseY();

			//If we're below the button area
				if(iMouseY >= PLAYFIELD_Y)
				{	//Translate this mouse position to a tile #
						int iTileX = ((iMouseX - PLAYFIELD_X) / TILE_WIDTH)  + Game()->TerrainMap().ViewX();
						int iTileY = ((iMouseY - PLAYFIELD_Y) / TILE_HEIGHT) + Game()->TerrainMap().ViewY();
						iTileX -= PLAYFIELD_TILEWIDTH/2;
						iTileY -= PLAYFIELD_TILEHEIGHT/2;
									 				
						//Move the viewports center to there.
							MoveViewportsTo(iTileX, iTileY);
			 						
					//Redraw
						Draw();
				}
			//Else see if we're clicking a button
				else
				{	int iButtonPressed = mypoButtonsStrip->ButtonAt(iMouseX, iMouseY);
					while(myoInput.GetMouseButton(MOUSE_LEFT) || myoInput.GetMouseButton(MOUSE_RIGHT))
					{	myoInput.Update();
						mypoButtonsStrip->Highlight(iButtonPressed);
						mypoScreen->Update();
						iMouseX = myoInput.GetMouseX();
						iMouseY = myoInput.GetMouseY();
						iButtonPressed = mypoButtonsStrip->ButtonAt(iMouseX, iMouseY);
					}
					if(iButtonPressed >= 0)
					{	PressButton(iButtonPressed);
						Draw();
					}
					else if(iMouseY < PLAYFIELD_Y)
					{	mypoButtonsStrip->SetCurrentSet(BUTTONS_MENU_MAIN);
						myfUpdateButtons = true;
						Draw();
					}
				}
				
			//If the user is cntrl + right clicking pick
				myoInput.Update();
				if(myoInput.KeyDown(SDLK_LCTRL) || myoInput.KeyDown(SDLK_RCTRL))
				{	if(myoInput.GetMouseButton(MOUSE_RIGHT))
					{	myiSelectedTerrain = int(Game()->TerrainMap().Get(CursorX(), CursorY()));
						Draw();
						while(myoInput.GetMouseButton(MOUSE_RIGHT))
							myoInput.Update();
						return false;
					}
				}
				
			//If both buttons are down
				if(myoInput.GetMouseButton(MOUSE_RIGHT) && myoInput.GetMouseButton(MOUSE_LEFT))
				{	Plot();
					Draw();
					return(false);
				}
				
			//Wait for the right mouse button to be released
				while(myoInput.GetMouseButton(MOUSE_RIGHT))
				{	myoInput.Update();
				
					//If both buttons are depressed then plot
						if(myoInput.GetMouseButton(MOUSE_LEFT))
						{	Plot();
							Draw();
							
							while(myoInput.GetMouseButton(MOUSE_RIGHT) || myoInput.GetMouseButton(MOUSE_LEFT))
							{	myoInput.Update();
							}
						}
				}
		}

	//Return false for "no clicks"
		return(false);
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...  p
SDLKey LEDIT_MapEditor::GetEdittingKey(SDLKey* piMod)
{	//Vars
		SDLKey tiKey = SDLKey(int(-1));
		SDLKey tiKey2 = SDLKey(int(-1));
		SDLKey iMod;

	//Grab a key
		while (tiKey == -1)
		{	myoInput.Update();
			tiKey = SDLKey(myoInput.GetKey(false, 250, 5));
			HandleMouse();
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
		 tiKey == KEY_MOVECUR_NRTHEST || tiKey ==	KEY_MOVECUR_STHWST || tiKey == KEY_MOVECUR_STHEST ||
		 tiKey == KEY_PLOT          || tiKey == SDLK_LCTRL         || tiKey == SDLK_RCTRL ||
		 tiKey == KEY_BUTTON_0		|| tiKey == KEY_BUTTON_1	   || tiKey == KEY_BUTTON_2 ||
		 tiKey == KEY_BUTTON_3		|| tiKey == KEY_BUTTON_4	   || tiKey == KEY_BUTTON_5 ||
		 tiKey == KEY_BUTTON_6		|| tiKey == KEY_BUTTON_7	   || tiKey == KEY_BUTTON_8 ||
		 tiKey == KEY_BUTTON_9		|| tiKey == KEY_BUTTON_10	   || tiKey == KEY_BUTTON_11))
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
		else if(tiKey == KEY_SWITCH_MAPS2)	 tiKey = KEY_SWITCH_MAPS;
		else if(tiKey == KEY_HELP2) 		 tiKey = KEY_HELP;
		else if(tiKey == KEY_CHANGETERRAIN2) tiKey = KEY_CHANGETERRAIN;
		else if(tiKey == KEY_ABOUT2) 		 tiKey = KEY_ABOUT;
		else if(tiKey == KEY_EXIT2) 		 tiKey = KEY_EXIT;

	//Return this key
		return(tiKey);
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...  P
void LEDIT_MapEditor::HandleEdittingKey(SDLKey iKey, SDLKey iMod)
{	//Cntrl + 
		myoInput.Update();
		if(iMod == MOD_CTRL && myoInput.KeyDown(SDLK_LCTRL) || myoInput.KeyDown(SDLK_RCTRL))
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
			//- [Plot ...] -
				else if(myoInput.KeyDown(KEY_PLOT))		    Plot();
				else if(myoInput.KeyDown(KEY_PLOT_SQUARE1)) PlotSquare(1, CursorX(), CursorY(), myiSelectedTerrain);
				else if(myoInput.KeyDown(KEY_PLOT_SQUARE2)) PlotSquare(2, CursorX(), CursorY(), myiSelectedTerrain);
				else if(myoInput.KeyDown(KEY_PLOT_SQUARE3)) PlotSquare(3, CursorX(), CursorY(), myiSelectedTerrain);
				else if(myoInput.KeyDown(KEY_PLOT_SQUARE4)) PlotSquare(4, CursorX(), CursorY(), myiSelectedTerrain);
				else if(myoInput.KeyDown(KEY_PLOT_SQUARE5)) PlotSquare(5, CursorX(), CursorY(), myiSelectedTerrain);
				else if(myoInput.KeyDown(KEY_PLOT_SQUARE6)) PlotSquare(6, CursorX(), CursorY(), myiSelectedTerrain);
				else if(myoInput.KeyDown(KEY_PLOT_SQUARE7)) PlotSquare(7, CursorX(), CursorY(), myiSelectedTerrain);
				else if(myoInput.KeyDown(KEY_PLOT_SQUARE8)) PlotSquare(8, CursorX(), CursorY(), myiSelectedTerrain);
				else if(myoInput.KeyDown(KEY_PLOT_SQUARE9)) PlotSquare(9, CursorX(), CursorY(), myiSelectedTerrain);
			//- [Edit Player Set] - //51
				else if(myoInput.KeyDown(KEY_EDIT_PLAYER_SET))
				{	mypoPlayerSetEditor->EditPlayerSet(&Game()->PlayerSet(), Game());
				}
			//- [Highlight] -
  				else if(myoInput.KeyDown(KEY_HIGHLIGHT))
  				{	myfHighlightUnits = !myfHighlightUnits;
  				}
			//- [Move to] -
				else if(myoInput.KeyDown(KEY_MOVETO))
				{	//If we're not battle map editting prompt for a location
						if(!myfBattleEdit)
						{	//Vars
								int iX, iY;
							//Ask for X, Y
								mypoPainter->TalkConsole().Clear();
								mypoPainter->TalkConsole().CurrentFont(FONT_HIGHLIGHT);
								mypoPainter->TalkConsole() << "Where would you like to place the cursor?\n";
								mypoPainter->TalkConsole().CurrentFont(FONT_NORMAL);
								mypoPainter->TalkConsole() << "X: ";

								mypoPainter->TalkConsole() >> iX;
								mypoPainter->TalkConsole() << "\nY: ";
								mypoPainter->TalkConsole() >> iY;

							//Move to X, Y if possible
								if(iX >= 0 && iX < Game()->TerrainMap().Width())
								{	Game()->TerrainMap().SetViewX(iX - PLAYFIELD_TILEWIDTH/2);
								}
								if(iY >= 0 && iY < Game()->TerrainMap().Height())
								{	Game()->TerrainMap().SetViewY(iY - PLAYFIELD_TILEWIDTH/2);
								}
    					}
     				//We're battle map editting so ask for a map #
     					else
     					{	//Vars
								int iNum, iX, iY;
							//Ask for X, Y
								mypoPainter->TalkConsole().Clear();
								mypoPainter->TalkConsole().CurrentFont(FONT_HIGHLIGHT);
								mypoPainter->TalkConsole() << "What battle map # would you like to edit?\n";
								mypoPainter->TalkConsole().CurrentFont(FONT_NORMAL);
								mypoPainter->TalkConsole() << "#: ";
								mypoPainter->TalkConsole() >> iNum;
    						//Calculate the X, Y of dis' map
								iX = Game()->BattleMap().MapEdgeX(iNum);
								iY = Game()->BattleMap().MapEdgeY(iNum);
    						//Set the restrictions
    							myiBattleEdgeX1 = iX;
                 				myiBattleEdgeY1 = iY;
                 				myiBattleEdgeX2 = iX + PLAYFIELD_TILEWIDTH;
                     			myiBattleEdgeY2 = iY + PLAYFIELD_TILEHEIGHT;
							//Move to X, Y if possible
								Game()->TerrainMap().SetViewX(iX);
								Game()->TerrainMap().SetViewY(iY);
     					}
				}
			//- [Pick terrain] -
				else if(myoInput.KeyDown(KEY_PICK_TERRAIN))
				{	myiSelectedTerrain = int(Game()->TerrainMap().Get(CursorX(), CursorY()));
				}
		}
	//Nada +
		else
		{	//- [Exit] -
				if(iKey == KEY_EXIT)
				{	//If we're route editting stop
	    				if(myfRouteEditting)
    					{	//Switch route editting mode
								myfRouteEditting = !myfRouteEditting;
								myfLayingArea = false;
						}
					//Else ask if the user REALLY wants to quit
						else
						{	if(mypoPainter->PromptYN("Accck! You want to exit Lore And Lutes",
													 "Are you sure? (Y/N)", "", 1))
					    	{
	              				myiCurrentState = MAPEDIT_STATE_EXIT;
							}
						}
				}
			//- [Test] -
				else if(iKey == KEY_TEST)
				{	myiCurrentState = MAPEDIT_STATE_TEST;
				}
			//- [Move Cursor ...] -
				else if(iKey == KEY_MOVECUR_NORTH)		MoveViewports(DIR_NORTH);
				else if(iKey == KEY_MOVECUR_SOUTH)		MoveViewports(DIR_SOUTH);
				else if(iKey == KEY_MOVECUR_WEST)		MoveViewports(DIR_WEST);
				else if(iKey == KEY_MOVECUR_EAST)		MoveViewports(DIR_EAST);
				else if(iKey == KEY_MOVECUR_NRTHWST)	MoveViewports(DIR_NORTH_WEST);
				else if(iKey == KEY_MOVECUR_NRTHEST)	MoveViewports(DIR_NORTH_EAST);
				else if(iKey == KEY_MOVECUR_STHWST)		MoveViewports(DIR_SOUTH_WEST);
				else if(iKey == KEY_MOVECUR_STHEST)		MoveViewports(DIR_SOUTH_EAST);
			//- [Gem View] -
				else if(iKey == KEY_GEM_VIEW)
				{	GemView();
				}
			//- [Plot...] -
				else if(iKey == KEY_PLOT) 		  Plot();
			//- [Switch Pen Mode] -
				else if(iKey == KEY_PENMODE_SWITCH) myfPenDown = !myfPenDown;
			//- [Fill] -
				else if(iKey == KEY_FILL)
					Fill(CursorX(), CursorY(), myiSelectedTerrain,
     					 Game()->TerrainMap().Get(CursorX(), CursorY()));
			//- [Change current tile] -
				else if(iKey == KEY_CHANGETERRAIN)
				{	int ti = mypoTerrainSetEditor->ChooseTile();
					if(ti != mypoTerrainSetEditor->CANCEL)
	    				myiSelectedTerrain = ti;
				}
			//- [Edit Map Informatin] -
				else if(iKey == KEY_EDIT_INFO)
				{	//Only when not in battle edit mode
						if(!myfBattleEdit)
		    				mypoMapInfoEditor->EditMap(&mypoGame->TerrainMap());
				}
			//- [Edit global (universal) information] -
				else if(iKey == KEY_EDIT_GLOBAL_INFO)
				{	//Only when not in battle edit mode
		    			mypoGlobalInfoEditor->EditInfo();
				}
			//- [Switch maps / edit map set] -
				else if(iKey == KEY_SWITCH_MAPS)
				{ 	int iMap = mypoMapSetEditor->EditMapSet(&mypoGame->MapSet());
      				//If we canceled do nothing
          				if(iMap == mypoMapSetEditor->CONSOLEEDIT_NONE)
      					{}
					//If we just created a new map
						else if(iMap == mypoMapSetEditor->NEW_MAP)
						{	mypoGame->NewMap(mypoGame->MapSet().NumMaps()-1);
							SwitchMap(mypoGame->MapSet().NumMaps()-1);
						}
					//If its a real map
						else
			   			{	SwitchMap(iMap);
			   			}
				}
			//- [Previous map] -
				else if(iKey == KEY_SWITCH_PREV_MAP)
				{	if(mypoGame->CurrentMap() - 1 >= 0)
						SwitchMap(mypoGame->CurrentMap() - 1);
				}
			//- [Next map] -
				else if(iKey == KEY_SWITCH_NEXT_MAP)
				{	if(mypoGame->CurrentMap() + 1 < mypoGame->MapSet().NumMaps())
						SwitchMap(mypoGame->CurrentMap() + 1);
				}
			//- [Edit battle map] -
				else if(iKey == KEY_EDIT_BATTLE_MAP)
				{	//Vars
						int iNum, iX, iY;
    				//Switch to the battle map
						SwitchMap(-1);
  					//Prompt for sub map number
						mypoPainter->TalkConsole().Clear();
						mypoPainter->TalkConsole().CurrentFont(FONT_HIGHLIGHT);
						mypoPainter->TalkConsole() << "What battle map # would you like to edit?\n";
						mypoPainter->TalkConsole().CurrentFont(FONT_NORMAL);
						mypoPainter->TalkConsole() << "#: ";
						mypoPainter->TalkConsole() >> iNum;
    				//Calculate sub map location
						iX = Game()->BattleMap().MapEdgeX(iNum);
						iY = Game()->BattleMap().MapEdgeY(iNum);
					//Set the restrictions
 						myiBattleEdgeX1 = iX;
                 		myiBattleEdgeY1 = iY;
                 		myiBattleEdgeX2 = iX + PLAYFIELD_TILEWIDTH;
                     	myiBattleEdgeY2 = iY + PLAYFIELD_TILEHEIGHT;
					//Move to X, Y if possible
						Game()->TerrainMap().SetViewX(iX);
						Game()->TerrainMap().SetViewY(iY);
				}
			//- [About/Place area] -
				else if(iKey == KEY_ABOUT)
				{	//If we're not in routing mode then display the about message
						if(!myfRouteEditting)
						{	ASFC_Surface oImage;
		    				oImage.LoadImage("./data/gui/editor/about.png", COLOR_BLUE);
	 						oImage.BlitTo(*mypoScreen, PLAYFIELD_X, PLAYFIELD_Y);
 							mypoScreen->Update();
		 					WaitForAKey();
						}
					//If we're routing ask for area positions
						else
						{	//If we're laying area then this is the last corner, lay area
								if(myfLayingArea)
								{	//Save the cursor position
										int iAreaEndX = CursorX();
										int iAreaEndY = CursorY();
									//If the end area is actually the topleft corner reverse the vars
										if(iAreaEndX < myiAreaStartX || iAreaEndY < myiAreaStartY)
										{	int ti;
          									//Reverse Xs
												ti = myiAreaStartX;
												myiAreaStartX = iAreaEndX;
												iAreaEndX	  = ti;
											//Reverse Ys
          										ti = myiAreaStartY;
												myiAreaStartY = iAreaEndY;
												iAreaEndY	  = ti;
										}
										
									//Now lay it
										LL_Area oArea;
										oArea.iX = myiAreaStartX;
										oArea.iY = myiAreaStartY;
										oArea.iWidth  = iAreaEndX - myiAreaStartX + 1;
										oArea.iHeight = iAreaEndY - myiAreaStartY + 1;
          								Game()->PathNodes().AddArea(oArea);
      								//We're done laying area
      									myfLayingArea = !myfLayingArea;
								}
							//Else we're laying new area
								else
								{	//Save the cursor position							
										myiAreaStartX = CursorX();
										myiAreaStartY = CursorY();
									//Turn on laying area mode
										myfLayingArea = true;
								}
						}
				}
			//- [Save] -
				else if(iKey == KEY_SAVE)
				{	//Don't do anything until this key is released
						while(myoInput.KeyDown(KEY_SAVE)) {myoInput.Update();}
					//Now save the map
						mypoGame->SaveTerrainMap(mypoGame->TerrainMapFile());
					//And the map set
						mypoGame->SaveMapSet(mypoGame->MapSetFile());
					//And the vehicle set
						mypoGame->SaveVehicleSet(mypoGame->VehicleSetFile());
					//And the terrain set
						mypoGame->SaveTerrainSet(mypoGame->TerrainSetFile());
					//And the item set
						mypoGame->SaveItemSet(mypoGame->ItemSetFile());
					//And dat' monster set
						mypoGame->SaveMonsterSet(mypoGame->MonsterSetFile());
					//And the player set
						mypoGame->SavePlayerSet(mypoGame->PlayerSetFile());
					//And the vehicle objects set
						mypoGame->SaveVehicleObjectsSet(mypoGame->VehicleObjectsSetFile());
  					//And the battle information
  						mypoGame->SaveBattleMap();
					//And the classets
						mypoGame->SaveClassSet(mypoGame->ClassSetFileName(), &mypoGame->ClassSet());
						mypoGame->SaveGlobalClassSet();
					//And the map units set
						mypoGame->SaveUnitSet(mypoGame->UnitSetFileName());
					//And the global information
						mypoGame->SaveGlobalInfo();
				}
			//- [Edit Vehicle Set] -
				else if(iKey == KEY_EDIT_VEHICLE_SET)
				{	mypoVehicleSetEditor->EditVehicleSet();
				}
			//- [Clear Map] -
				else if(iKey == KEY_CLEAR_MAP)
				{	//Ask the user if he really is crazy. If so clear
						if(mypoPainter->PromptYN("Clear the map! It'll delete everything off it!",
														 "Are you sure? (Y/N)", "", 1))
				    	{
        					mypoGame->TerrainMap().Clear();
							mypoGame->UnitMap().Clear();
							mypoGame->UnitSet().Clear();
							mypoGame->LOOP().ClearClasses();
							mypoGame->ClassSet().Clear();
						}
				}
			//- [Help] -
				else if(iKey == KEY_HELP)
				{	//Help!
						mypoHelp->MapEditorHelp();
				}
			//- [Jot Notes] -
				else if(iKey == KEY_JOT_NOTES)
				{	//Jot notes
						mypoHelp->JotNotes(mypoGame->GameDir() + "/notes.txt");
				}
			//- [Edit Class Set] -
				else if(iKey == KEY_EDIT_CLASS_SET)
				{	//Only when not in battleedit mode
						if(!myfBattleEdit)
						{	//Edit, save
								mypoClassSetEditor->EditClassSet(mypoGame, &mypoGame->ClassSet(),
      															 mypoGame->ClassFileName(),
                		    									 mypoGame->ClassSetFileName());
								mypoGame->SaveClassSet(mypoGame->ClassSetFileName(), &mypoGame->ClassSet());
    					}
				}
			//- [Edit Global Class Set] -
				else if(iKey == KEY_EDIT_GLOBAL_CLASS_SET)
				{	//Edit, save
						mypoClassSetEditor->EditClassSet(mypoGame, &mypoGame->GlobalClassSet(),
      													 mypoGame->GlobalClassFileName(),
                    									 mypoGame->GlobalClassSetFileName());
						mypoGame->SaveGlobalClassSet();
				}
			//- [Edit Global Script] -
				else if(iKey == KEY_EDIT_GLOBAL_SCRIPT)
				{	mypoGlobalScriptEditor->EditGlobalScript(mypoGame, mypoGame->GlobalScriptFileName());
				}
			//- [Plot Instance] -
				else if(iKey == KEY_PLOT_INSTANCE)
				{	//Wait for o to be unreleased
    				//Only when not in battle mode
						//if(!myfBattleEdit)
						//{
      						mypoMapObjectEditor->PlotNewInstance(mypoGame, mypoClassSetEditor,
    															 CursorX(), CursorY(), CursorLayer());
                    	//}
				}
			//- [Kill Instance] -
				else if(iKey == KEY_KILL_INSTANCE)
				{	//If routing mode is on destroy any routes here
						if(myfRouteEditting)
						{	//Nodes
			      				mypoGame->PathNodes().RemoveNode(CursorX(), CursorY());
		   					//Areas
		   						mypoGame->PathNodes().RemoveArea(CursorX(), CursorY());
							//Routes
								mypoGame->PathNodes().RemoveRoute(CursorX(), CursorY());
						}
					//If there's a spawner here delete it
						else if(Game()->UnitSet().SpawnerAt(CursorX(), CursorY()) !=
								LL_UnitSet::NOTHING_FOUND)
						{
							Game()->UnitSet().RemoveSpawner
								(Game()->UnitSet().SpawnerAt(CursorX(), CursorY()));
						}
					//Else destroy instances
						else
							mypoMapObjectRemover->RemoveInstance(CursorX(), CursorY());
				//If we're editting da' battle maps
  					if(myfBattleEdit)
 					{	Game()->BattleMap().SetNoneOn(CursorX(), CursorY());
   					}
  				}
			//- [Edit Instance] -
				else if(iKey == KEY_EDIT_INSTANCE)
				{	//If there's a spawner on here
						if(Game()->UnitSet().SpawnerAt(CursorX(), CursorY()) >= 0)
						{	//Edit this spawner
								int iNum =
									Game()->UnitSet().SpawnerAt(CursorX(), CursorY());
								mypoSpawnerEditor->EditSpawner
								(&Game()->UnitSet().Spawner(iNum));
						}
					//If there's a unit on here
						if(Game()->UnitMap().IsUnitOn(CursorX(), CursorY()))
						{	//Vars
								int iSeg, iOff;
							//Get the seg and off here
								iSeg = Game()->UnitMap().TopSegOn(CursorX(), CursorY());
								iOff = Game()->UnitMap().TopOffOn(CursorX(), CursorY());
      
	       					//If there's a scripted unite here edit that
								if(iSeg == LL_UnitMap::SEG_SCRIPTED_UNITS)
								{	mypoScriptedUnitEditor->EditScriptedUnit(
        								&Game()->UnitSet().ScriptedUnit(iOff), Game());
								}
							//If there's chest edit that
								if(iSeg == LL_UnitMap::SEG_CHESTS)
								{	mypoChestEditor->EditChest(&Game()->UnitSet().Chest(iOff));
								}
							//If there's a transport edit that
								if(iSeg == LL_UnitMap::SEG_TRANSPORTS)
								{	mypoTransportEditor->EditTransport(&Game()->UnitSet().Transport(iOff));
								}
						}
				}
			//- [Edit Daily Path] -
				else if(iKey == KEY_EDIT_DAILY_PATH)
				{	//If there's a unit on here
						if(Game()->UnitMap().IsUnitOn(CursorX(), CursorY()))
						{	//Vars
								int iSeg, iOff;
							//Get the seg and off here
								iSeg = Game()->UnitMap().TopSegOn(CursorX(), CursorY());
								iOff = Game()->UnitMap().TopOffOn(CursorX(), CursorY());
	       					//If the seg is that of a scripted unit edit the path
								if(iSeg == LL_UnitMap::SEG_SCRIPTED_UNITS)
								{	mypoScriptedUnitEditor->DailyRoutineEditor()->EditDailyRoutine(
         								&Game()->UnitSet().ScriptedUnit(iOff).DailyRoutine());
								}
						}
				}
			//- [Copy] -
				else if(iKey == KEY_COPY)
				{	//Record this position
						iCopyX = CursorX();
      					iCopyY = CursorY();
						iCopySpawner = Game()->UnitSet().SpawnerAt(iCopyX, iCopyY);
				}
			//- [Paste] -
				else if(iKey == KEY_PASTE)
				{	mypoMapObjectEditor->PlotCopyInstance(	mypoGame, mypoClassSetEditor, iCopyX, iCopyY,
															CursorX(), CursorY(), CursorLayer());
					if(iCopySpawner != LL_UnitSet::NOTHING_FOUND)
					{	Game()->UnitSet().CopySpawner(CursorX(), CursorY(), iCopySpawner);
					}
				}
			//- [Edit Monster Set] -
				else if(iKey == KEY_EDIT_MONSTER_SET)
				{	mypoMonsterSetEditor->EditMonsterSet(&Game()->MonsterSet(), Game());
				}
			//- [Plot Monster] -
				else if(iKey == KEY_PLOT_MONSTER)
				{	//If we're not battle editting plot the monster
						if(!myfBattleEdit)
						{	//LL_Monster oMonster = Game()->MonsterSet().Monster(0);
							//oMonster.LoadAnimation("./games/lore/graphics/bluebricks.png", Game()->GraphicsDir());
							//Game()->MapObjectsSet().AddMonster(oMonster, CursorX(), CursorY());		
							int iMonster = mypoMonsterSetEditor->GrabMonster(&Game()->MonsterSet(), Game());
							mypoMapObjectEditor->PlotMonster(mypoGame, iMonster, CursorX(), CursorY(),
        													 CursorLayer());
                  		}
                	//If we are battle editting place a monster warp in point
                		else
                		{	Game()->BattleMap().SetFoeOn(CursorX(), CursorY());
                		}
				}
			//- [Edit Routes] -
				else if(iKey == KEY_EDIT_ROUTES)
				{	//Only when not in battle edit mode
						if(!myfBattleEdit)
						{	//Switch route editting mode
								myfRouteEditting = !myfRouteEditting;
							//If routing is off automatically turn area-ing off
								if(!myfRouteEditting)
									myfLayingArea = false;
     					}
				}
			//- [Place Route] -
				else if(iKey == KEY_EDIT_PLACE_ROUTE)
				{	//Only place route if we're routing
						if(myfRouteEditting)
						{	//Check to make sure we're on a node
								if(mypoPathNodes->NodeOn(CursorX(), CursorY()) != mypoPathNodes->NO_NODE)
								{	mypoRouteEditor->EditRoute(mypoGame, CursorX(), CursorY());
								}
						}
				}
			//- [Unit layer prev\next] -
				else if(iKey == KEY_PREV_LAYER)
				{	if(CursorLayer() - 1 >= 0) SetCursorLayer(CursorLayer() - 1);
				}
				else if(iKey == KEY_NEXT_LAYER)
				{	if(CursorLayer() + 1 < LL_UnitMap::MAP_LAYERS) SetCursorLayer(CursorLayer() + 1);
				}
			//- [Edit item set] -
				else if(iKey == KEY_EDIT_ITEM_SET)
				{	mypoItemSetEditor->EditItemSet(&Game()->ItemSet());
				}
			//- [Plot item] -
				else if(iKey == KEY_PLOT_ITEM)
				{	//Grab a type
			    		int iType = mypoItemSetEditor->GetItemType();
					//If we're placing an armor
 						if(iType == LEDIT_ItemSetEditor::EDITOPTION_ARMORS)
 						{	int iArmor = mypoItemSetEditor->GetArmor(&Game()->ItemSet());
							if(iArmor >= 0)
	 							mypoMapObjectEditor->PlotArmor(	mypoGame, iArmor, CursorX(), CursorY(),
    	    													CursorLayer());
						}
					//If we're placing a weapon
						else if(iType == LEDIT_ItemSetEditor::EDITOPTION_WEAPONS)
						{	int iArmor = mypoItemSetEditor->GetWeapon(&Game()->ItemSet());
							if(iArmor >= 0)
								mypoMapObjectEditor->PlotWeapon(mypoGame, iArmor, CursorX(), CursorY(),
   																CursorLayer());
						}
					//If we're placing a scripted item
						else if(iType == LEDIT_ItemSetEditor::EDITOPTION_SCRIPTS)
						{	int iArmor = mypoItemSetEditor->GetScriptedItem(&Game()->ItemSet());
							if(iArmor >= 0)
	   							mypoMapObjectEditor->PlotScriptedItem(	mypoGame, iArmor, CursorX(), CursorY(),
    	    															CursorLayer());
						}
  					//If we're placing a chest
						else if(iType == LEDIT_ItemSetEditor::EDITOPTION_CHESTS)
						{	//Plot away
								mypoMapObjectEditor->PlotChest(mypoGame, CursorX(), CursorY(), CursorLayer());
						}
				}
			//- [Plot chest] -
				else if(iKey == KEY_PLOT_CHEST)
				{	//Plot away
						mypoMapObjectEditor->PlotChest(mypoGame, CursorX(), CursorY(), CursorLayer());
				}
			//- [Edit vehicle objects set] -
				else if(iKey == KEY_EDIT_VEHICLE_OBJECT_SET)
				{	//Edit the vehicle objects set
						mypoVehiclObjectSetEditor->EditVehicleObjectSet(&mypoGame->VehicleObjectSet());
				}
			//- [Plot vehicle object] -
				else if(iKey == KEY_PLOT_VEHICLE_OBJECT)
				{	mypoMapObjectEditor->PlotVehicleObject(mypoGame, 0, CursorX(), CursorY(),	//!!!
   														   LAYER_VEHICLE);
				}
			//- [Plot transport] -
				else if(iKey == KEY_PLOT_TRANSPORT)
				{	//Plot away
						mypoMapObjectEditor->PlotTransport(mypoGame, CursorX(), CursorY(), CursorLayer());
				}
			//- [Edit vehicle-battle keys] -
				else if(iKey == KEY_EDIT_KEYS)
				{	//Edit the keys
						mypoKeyEditor->EditVehicleBattleKeys();
				}
  			//- [Plot player] -
  				else if(iKey == KEY_PLOT_PLAYER)
  				{	//If we're battle editting place a friend warp point thingy
  						if(myfBattleEdit)
  						{	Game()->BattleMap().SetFriendOn(CursorX(), CursorY());
  						}
  				}
			//- [Plot Spawner] -
				else if(iKey == KEY_PLOT_SPAWNER)
				{	Game()->UnitSet().AddSpawner(CursorX(), CursorY());
				}
			//- [Buttons ...] -
				else if(iKey == KEY_BUTTON_0)	PressButton(0);
				else if(iKey == KEY_BUTTON_1)	PressButton(1);
				else if(iKey == KEY_BUTTON_2)	PressButton(2);
				else if(iKey == KEY_BUTTON_3)	PressButton(3);
				else if(iKey == KEY_BUTTON_4)	PressButton(4);
				else if(iKey == KEY_BUTTON_5)	PressButton(5);
				else if(iKey == KEY_BUTTON_6)	PressButton(6);
				else if(iKey == KEY_BUTTON_7)	PressButton(7);
				else if(iKey == KEY_BUTTON_8)	PressButton(8);
				else if(iKey == KEY_BUTTON_9)	PressButton(9);
				else if(iKey == KEY_BUTTON_10)	PressButton(10);
				else if(iKey == KEY_BUTTON_11)	PressButton(11);
			//- [Main menu] -
				else if(iKey == KEY_MAIN_MENU)
				{	mypoButtonsStrip->SetCurrentSet(BUTTONS_MENU_MAIN);
					myfUpdateButtons = true;
				}
		}
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...  P
void LEDIT_MapEditor::DrawStats()
{	//Clear the stats console and put our stats in
		mypoPainter->StatsConsole().Clear();
		mypoPainter->StatsConsole().CurrentFont(FONT_NORMAL);
		mypoPainter->StatsConsole() << "X\\Y\\L: (" 
									<< CursorX() << ", " << CursorY() << ", " << CursorLayer() << ")\n";
		mypoPainter->StatsConsole() << "Current Terrain:\n\n\n\n";
		if(myfRouteEditting)
		{	mypoPainter->StatsConsole().CurrentFont(FONT_HIGHLIGHT);
			mypoPainter->StatsConsole() << "(r) Route Editting\n";
		}
		if(myfPenDown)
		{	mypoPainter->StatsConsole().CurrentFont(FONT_HIGHLIGHT);
			mypoPainter->StatsConsole() << "(p) Pen Down\n";
		}
		if(myfLayingArea)
		{	mypoPainter->StatsConsole().CurrentFont(FONT_HIGHLIGHT);
			mypoPainter->StatsConsole() << "(a) Laying Area\n";
		}
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...  P
void LEDIT_MapEditor::Draw()
{	//Clear the screen
		mypoScreen->DrawFillRectangle(0, PLAYFIELD_Y, 639, 479 - PLAYFIELD_Y, COLOR_BLACK, 255);
	//Draw stats
		DrawStats();
	//Draw terrain, unit, and path finding (if necessary), maps
		Game()->TerrainMap().Draw(*mypoScreen, lNoLight);
		mypoPainter->DrawUnitMap(&lNoLight, myfHighlightUnits, true);
		if(myfRouteEditting)
		{	Game()->PathNodes().Draw(*mypoScreen, CursorX() - PLAYFIELD_TILEWIDTH/2,
									 CursorY() - PLAYFIELD_TILEHEIGHT/2, PLAYFIELD_X, PLAYFIELD_Y);
	 		RouteEditor()->DrawRoute(CursorX(), CursorY());
	 	}
	 	if(myfBattleEdit)
	 	{	Game()->BattleMap().DrawFFMatrix(*mypoScreen, CursorX() - PLAYFIELD_TILEWIDTH/2,
									 		 CursorY() - PLAYFIELD_TILEHEIGHT/2, PLAYFIELD_X, PLAYFIELD_Y);
	 	}
	//Draw consoles
		mypoPainter->Draw();
	//Draw selected terrain
		DrawOtherInfo();
	//Draw cursor
		mypoPainter->Cursor().BlitTo(*mypoScreen,
  									(PLAYFIELD_X2 - PLAYFIELD_X)/2 - TILE_WIDTH/2  + PLAYFIELD_X,
									(PLAYFIELD_Y2 - PLAYFIELD_Y)/2 - TILE_HEIGHT/2 + PLAYFIELD_Y);
	//Draw the buttons strip
		if(myfUpdateButtons)
		{	//Save pictures of the map
				ASFC_Surface oSurf1(mypoScreen->GetWidth(), mypoScreen->GetHeight(), mypoScreen->GetBpp());
				oSurf1.Blit(*mypoScreen, 0, 0);
			//Clear the button area
				mypoScreen->DrawFillRectangle(CELESTIALVIEW_X, CELESTIALVIEW_Y, 
											  STATVIEW_X - CELESTIALVIEW_X,
											  STATVIEW_Y - CELESTIALVIEW_Y - 5, COLOR_BLACK, 255);
			//Draw consoles
				mypoPainter->Draw();
			//Draw cursor
				mypoPainter->Cursor().BlitTo(*mypoScreen,
  											(PLAYFIELD_X2 - PLAYFIELD_X)/2 - TILE_WIDTH/2  + PLAYFIELD_X,
											(PLAYFIELD_Y2 - PLAYFIELD_Y)/2 - TILE_HEIGHT/2 + PLAYFIELD_Y);
			//Redraw
				mypoButtonsStrip->Draw();
				myfUpdateButtons = false;
			//Update the quick keys
				DrawQuickKeys();
				mypoPainter->Draw();
			//Draw selected terrain
				DrawOtherInfo();
			//Do an effect
				ASFC_Surface oSurf2(mypoScreen->GetWidth(), mypoScreen->GetHeight(), mypoScreen->GetBpp());
				oSurf2.Blit(*mypoScreen, 0, 0);
				myoEffects.Blend(oSurf1, oSurf2, *mypoScreen, 35, 84);
		}
	//Update
		mypoScreen->Update();
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...  P
void LEDIT_MapEditor::WaitForAKey()
{	//Wait for space !!!! TMP MOD FOR ANY KEY !!!
		while(myoInput.KeyUp(SDLK_SPACE)) myoInput.Update();
		while(myoInput.KeyDown(SDLK_SPACE)) myoInput.Update();
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...  P
void LEDIT_MapEditor::MoveScreen(ASFC_DIRECTION iDir)
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
void LEDIT_MapEditor::MoveViewports(ASFC_DIRECTION iDir)
{	//Vars
		int iX = Game()->TerrainMap().ViewX();
		int iY = Game()->TerrainMap().ViewY();
		
	//Offset the coods based on direction
		if(iDir == DIR_NORTH || iDir == DIR_NORTH_WEST || iDir == DIR_NORTH_EAST)	iY--;
		if(iDir == DIR_SOUTH || iDir == DIR_SOUTH_WEST || iDir == DIR_SOUTH_EAST)	iY++;
		if(iDir == DIR_WEST  || iDir == DIR_NORTH_WEST || iDir == DIR_SOUTH_WEST)	iX--;
		if(iDir == DIR_EAST  || iDir == DIR_NORTH_EAST || iDir == DIR_SOUTH_EAST)	iX++;

	//If we're battle editting and moving there is illegal stop!
		if(myfBattleEdit)
		{	if( iX + PLAYFIELD_TILEWIDTH/2+1  <= myiBattleEdgeX1 ||
  				iX + PLAYFIELD_TILEWIDTH/2+1  >  myiBattleEdgeX2 ||
  				iY + PLAYFIELD_TILEHEIGHT/2+1 <= myiBattleEdgeY1 ||
      			iY + PLAYFIELD_TILEHEIGHT/2+1 >  myiBattleEdgeY2)
  			{
     			return;
  			}
		}

	//Now move there
		MoveViewportsTo(iX, iY);
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...  P
void LEDIT_MapEditor::MoveViewportsTo(int iX, int iY)
{	//If we're in battle edit move and this is illegal stop
		if(myfBattleEdit)
		{	if( iX + PLAYFIELD_TILEWIDTH/2+1  <= myiBattleEdgeX1 ||
  				iX + PLAYFIELD_TILEWIDTH/2+1  >  myiBattleEdgeX2 ||
  				iY + PLAYFIELD_TILEHEIGHT/2+1 <= myiBattleEdgeY1 ||
      			iY + PLAYFIELD_TILEHEIGHT/2+1 >  myiBattleEdgeY2)
  			{
     			return;
  			}
		}

	//Only move to iX, iY if legal!
		if(iX >= -PLAYFIELD_TILEWIDTH/2 && iY >= -PLAYFIELD_TILEHEIGHT/2 &&
  		   iX < Game()->TerrainMap().Width()  - PLAYFIELD_TILEWIDTH/2 &&
       	   iY < Game()->TerrainMap().Height() - PLAYFIELD_TILEHEIGHT/2)
		{
		   	Game()->TerrainMap().SetViewX(iX);
		   	Game()->TerrainMap().SetViewY(iY);
 		}
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...  P
void LEDIT_MapEditor::Plot()
{	//If route editting is off plot a terrain
		if(!myfRouteEditting)
			Game()->TerrainMap().Set(CursorX(), CursorY(), myiSelectedTerrain);
	//Else plot a node there
		else
		{	Game()->PathNodes().DynamicallyPlotNode(CursorX(), CursorY());
		}
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...  P
void LEDIT_MapEditor::PlotSquare(C_i4(iRad, iCenterX, iCenterY, iTerrain))
{	//Loop to make a square
		for(int iY = iCenterY - iRad; iY <= iCenterY + iRad; iY++)
			for(int iX = iCenterX - iRad; iX <= iCenterX + iRad; iX++)
				if(	iX >= 0 && iY >= 0 && iX < Game()->TerrainMap().Width() &&
    				iY < Game()->TerrainMap().Height())
				{
					Game()->TerrainMap().Set(iX, iY, iTerrain);
				}
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...  P
void LEDIT_MapEditor::Fill(int iX, int iY, int iTo, int iFrom)
{	//If to and from are difference
		if(iTo != iFrom)
		{	//Fill here
				Game()->TerrainMap().Set(iX, iY, iTo);
		
			//Attempt filling in other directions (if legal)
				if(LegalFill(iX-1, iY, 	iFrom)) Fill(iX-1, iY, iTo, iFrom);
				if(LegalFill(iX+1, iY,  iFrom)) Fill(iX+1, iY, iTo, iFrom);
				if(LegalFill(iX,   iY-1,iFrom)) Fill(iX, iY-1, iTo, iFrom);
				if(LegalFill(iX,   iY+1,iFrom)) Fill(iX, iY+1, iTo, iFrom);
		}
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...P
//Decides if its legal to fill at iX, iY
bool LEDIT_MapEditor::LegalFill(int iX, int iY, int iLegalTerrain)
{	//If the coods are off the map
		if(iX < 0 || iX >= Game()->TerrainMap().Width() ||
		   iY < 0 || iY >= Game()->TerrainMap().Height())
 		{	return(false);
 		}
	//If the coods are off the battle area (when battle editting)
		if(myfBattleEdit)
		{	if( iX <  myiBattleEdgeX1 ||
  				iX >= myiBattleEdgeX2 ||
  				iY <  myiBattleEdgeY1 ||
      			iY >= myiBattleEdgeY2)
  			{
     			return(false);
  			}
		}
 		
	//If this terrain isn't a legal terrain
		if(Game()->TerrainMap().Get(iX, iY) != iLegalTerrain)
			return false;

	//If execution gets here its a-okay and legal
		return true;
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...  P
int	LEDIT_MapEditor::CursorX()
{	return(Game()->TerrainMap().ViewX() + PLAYFIELD_TILEWIDTH/2);
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...  P
int	LEDIT_MapEditor::CursorY()
{	return(Game()->TerrainMap().ViewY() + PLAYFIELD_TILEHEIGHT/2);
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...  P
void LEDIT_MapEditor::DrawQuickKeys()
{	//Be a good editor and always offer help
		mypoPainter->TalkConsole().Clear();
		mypoPainter->TalkConsole().CurrentFont(FONT_NORMAL);
		mypoPainter->TalkConsole() << "Press 'h' for help.\n\n";
	
	//If we're route editting add in info there
		if(myfRouteEditting)
		{	mypoPainter->TalkConsole() << "Route Editting: \n";
			mypoPainter->TalkConsole() << "Space: Plot Node\n";
			mypoPainter->TalkConsole() << "Del:   Remove Node\n";
			mypoPainter->TalkConsole() << "A:     Define Area\n";
			mypoPainter->TalkConsole() << "L:     Draw Route\n";
			mypoPainter->TalkConsole() << "D:     Objects Daily Route\n";
			mypoPainter->TalkConsole() << "Esc/R: Stop Routing\n";
		}
	//If we're battle map editting add in info there
		else if(myfBattleEdit)
		{	mypoPainter->TalkConsole() << "Battle Map Editting: \n";
			mypoPainter->TalkConsole() << "f: Plot enemy entrance\n";
			mypoPainter->TalkConsole() << "z: Plot player entrance\n";
			mypoPainter->TalkConsole() << "~: Switch to battle map\n";
			mypoPainter->TalkConsole() << "m: Switch to normal map\n";
		}
	//Otherwise draw the menu keys
		else
		{	mypoPainter->TalkConsole() << "Menu keys: \n";
			mypoPainter->TalkConsole() << "~: Goto main menu\n";
			mypoButtonsStrip->DrawKeyInfo(&mypoPainter->TalkConsole());
		}
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...  P
void LEDIT_MapEditor::DrawOtherInfo()
{	//Draw the selected terrain
		Game()->TerrainSet().Terrain(myiSelectedTerrain).BlitTo(*mypoScreen, INFOVIEW_X + TILE_WIDTH,
									 STATVIEW_Y + 29);
	//And logo
		myoLogo.BlitTo(*mypoScreen, LLVIEW_X, LLVIEW_Y);
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...  P
void LEDIT_MapEditor::GemView()
{	//Draw view, and wait for a key
		mypoPainter->TalkConsole().Clear();
		mypoPainter->TalkConsole().CurrentFont(FONT_NORMAL);
		mypoPainter->TalkConsole() << "Gem view. Press space to continue...";
		mypoPainter->TalkConsole().Draw(0xFF);

	//While no key has been pressed
		while(myoInput.KeyUp(SDLK_SPACE))
		{	Game()->TerrainMap().DrawGemView(*Screen(), true);
			mypoPainter->DrawGemSpawners();
			
			//If we're routing draw the routes on the gem view map to
				if(myfRouteEditting)
				{	RouteEditor()->DrawGemViewRoute();
	   				Game()->PathNodes().DrawGemView(*Screen());
				}
		
			Screen()->Update();
			myoInput.Update();
		}
      	while(myoInput.KeyDown(SDLK_SPACE)) myoInput.Update();
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...  P
void LEDIT_MapEditor::PressButton(int iNum)
{	//Highlight this button until the key and mouse is released
		mypoButtonsStrip->Highlight(iNum);
		mypoScreen->Update();
		myfUpdateButtons = true;
		myoInput.Update();
			 if(iNum == 0)  while(myoInput.KeyDown(KEY_BUTTON_0))  myoInput.Update();
		else if(iNum == 1)  while(myoInput.KeyDown(KEY_BUTTON_1))  myoInput.Update();
		else if(iNum == 2)  while(myoInput.KeyDown(KEY_BUTTON_2))  myoInput.Update();
		else if(iNum == 3)  while(myoInput.KeyDown(KEY_BUTTON_3))  myoInput.Update();
		else if(iNum == 4)  while(myoInput.KeyDown(KEY_BUTTON_4))  myoInput.Update();
		else if(iNum == 5)  while(myoInput.KeyDown(KEY_BUTTON_5))  myoInput.Update();
		else if(iNum == 6)  while(myoInput.KeyDown(KEY_BUTTON_6))  myoInput.Update();
		else if(iNum == 7)  while(myoInput.KeyDown(KEY_BUTTON_7))  myoInput.Update();
		else if(iNum == 8)  while(myoInput.KeyDown(KEY_BUTTON_8))  myoInput.Update();
		else if(iNum == 9)  while(myoInput.KeyDown(KEY_BUTTON_9))  myoInput.Update();
		else if(iNum == 10) while(myoInput.KeyDown(KEY_BUTTON_10)) myoInput.Update();
		else if(iNum == 11) while(myoInput.KeyDown(KEY_BUTTON_11)) myoInput.Update();
		mypoButtonsStrip->Draw();

	//Decide what to do based on the button being pressed in the current menu
		switch(mypoButtonsStrip->CurrentSet())
		{	case BUTTONS_MENU_MAIN:
			{	switch(iNum)
				{	case MAIN_MAP_OPTIONS:
					{	mypoButtonsStrip->SetCurrentSet(BUTTONS_MENU_MAP_OPTIONS);
						myfUpdateButtons = true;
					}break;

					case MAIN_TERRAINS:
					{	mypoButtonsStrip->SetCurrentSet(BUTTONS_MENU_TERRAINS);
						myfUpdateButtons = true;
					}break;

					case MAIN_ITEMS:
					{	mypoButtonsStrip->SetCurrentSet(BUTTONS_MENU_ITEMS);
						myfUpdateButtons = true;
					}break;

					case MAIN_MONSTERS:
					{	mypoButtonsStrip->SetCurrentSet(BUTTONS_MENU_MONSTERS);
						myfUpdateButtons = true;
					}break;

					case MAIN_VEHICLES:
					{	mypoButtonsStrip->SetCurrentSet(BUTTONS_MENU_VEHICLES);
						myfUpdateButtons = true;
					}break;

					case MAIN_SCRIPTING:
					{	mypoButtonsStrip->SetCurrentSet(BUTTONS_MENU_SCRIPTS);
						myfUpdateButtons = true;
					}break;

					case MAIN_TRANSPORTS:
					{	mypoButtonsStrip->SetCurrentSet(BUTTONS_MENU_TRANSPORTS);
						myfUpdateButtons = true;
					}break;

					case MAIN_DECORATIONS:
					{	mypoButtonsStrip->SetCurrentSet(BUTTONS_MENU_DECORATIONS);
						myfUpdateButtons = true;
					}break;

					case MAIN_USER_CONFIG:
					{	// !!!
					}break;

					case MAIN_PLAYER_SET:
					{	mypoPlayerSetEditor->EditPlayerSet(&Game()->PlayerSet(), Game());
					}break;

					case MAIN_ROUTING:
					{	HandleEdittingKey(KEY_EDIT_ROUTES, MOD_NONE);
					}break;

					case MAIN_SPECIAL_VIEWS:
					{	mypoButtonsStrip->SetCurrentSet(BUTTONS_MENU_VIEWS);
						myfUpdateButtons = true;
					}break;
				}
			}break;

			case BUTTONS_MENU_MAP_OPTIONS:
			{	switch(iNum)
				{	case MAP_OPTIONS_SAVE:
					{	HandleEdittingKey(KEY_SAVE, MOD_NONE);
					}break;
					
					case MAP_OPTIONS_LOAD:
					{	// !!!
					}break;

					case MAP_OPTIONS_SWITCH:
					{	HandleEdittingKey(KEY_SWITCH_MAPS, MOD_NONE);
					}break;

					case MAP_OPTIONS_SWITCH_BATTLE:
					{	HandleEdittingKey(KEY_EDIT_BATTLE_MAP, MOD_NONE);
					}break;

					case MAP_OPTIONS_CLEAR:
					{	HandleEdittingKey(KEY_CLEAR_MAP, MOD_NONE);
					}break;

					case MAP_OPTIONS_INFORMATION:
					{	HandleEdittingKey(KEY_EDIT_INFO, MOD_NONE);
					}break;

					case MAP_OPTIONS_GLOBAL_INFORMATION:
					{	HandleEdittingKey(KEY_EDIT_GLOBAL_INFO, MOD_NONE);
					}break;

					case MAP_OPTIONS_MOVE_TO:
					{	//If we're not battle map editting prompt for a location
							if(!myfBattleEdit)
							{	//Vars
									int iX, iY;
								//Ask for X, Y
									mypoPainter->TalkConsole().Clear();
									mypoPainter->TalkConsole().CurrentFont(FONT_HIGHLIGHT);
									mypoPainter->TalkConsole() << "Where would you like to place the cursor?\n";
									mypoPainter->TalkConsole().CurrentFont(FONT_NORMAL);
									mypoPainter->TalkConsole() << "X: ";
									mypoPainter->TalkConsole() >> iX;
									mypoPainter->TalkConsole() << "\nY: ";
									mypoPainter->TalkConsole() >> iY;
	
								//Move to X, Y if possible
									if(iX >= 0 && iX < Game()->TerrainMap().Width())
									{	Game()->TerrainMap().SetViewX(iX - PLAYFIELD_TILEWIDTH/2);
									}
									if(iY >= 0 && iY < Game()->TerrainMap().Height())
									{	Game()->TerrainMap().SetViewY(iY - PLAYFIELD_TILEWIDTH/2);
									}
    						}
    	 				//We're battle map editting so ask for a map #
	     					else
     						{	//Vars
									int iNum, iX, iY;
								//Ask for X, Y
									mypoPainter->TalkConsole().Clear();
									mypoPainter->TalkConsole().CurrentFont(FONT_HIGHLIGHT);
									mypoPainter->TalkConsole() << "What battle map # would you like to edit?\n";
									mypoPainter->TalkConsole().CurrentFont(FONT_NORMAL);
									mypoPainter->TalkConsole() << "#: ";
									mypoPainter->TalkConsole() >> iNum;
    							//Calculate the X, Y of dis' map
									iX = Game()->BattleMap().MapEdgeX(iNum);
									iY = Game()->BattleMap().MapEdgeY(iNum);
    							//Set the restrictions
    								myiBattleEdgeX1 = iX;
	                 				myiBattleEdgeY1 = iY;
                 					myiBattleEdgeX2 = iX + PLAYFIELD_TILEWIDTH;
                     				myiBattleEdgeY2 = iY + PLAYFIELD_TILEHEIGHT;
								//Move to X, Y if possible
									Game()->TerrainMap().SetViewX(iX);
									Game()->TerrainMap().SetViewY(iY);
     						}
					}break;

					case MAP_OPTIONS_PREV_LAYER:
					{	HandleEdittingKey(KEY_PREV_LAYER, MOD_NONE);
					}break;

					case MAP_OPTIONS_NEXT_LAYER:
					{	HandleEdittingKey(KEY_NEXT_LAYER, MOD_NONE);
					}break;

					case MAP_OPTIONS_HELP:
					{	HandleEdittingKey(KEY_HELP, MOD_NONE);
					}break;

					case MAP_OPTIONS_ABOUT:
					{	HandleEdittingKey(KEY_ABOUT, MOD_NONE);
					}break;
				}
			}break;

			case BUTTONS_MENU_TERRAINS:
			{	switch(iNum)
				{	case TERRAINS_EDIT_SET:
					{	HandleEdittingKey(KEY_CHANGETERRAIN, MOD_NONE);
					}break;

					case TERRAINS_PICK:
					{	myiSelectedTerrain = int(Game()->TerrainMap().Get(CursorX(), CursorY()));
					}break;
				}
			}break;

			case BUTTONS_MENU_ITEMS:
			{	switch(iNum)
				{	case ITEMS_EDIT_SET:
					{	HandleEdittingKey(KEY_EDIT_ITEM_SET, MOD_NONE);
					}break;

					case ITEMS_PLACE:
					{	HandleEdittingKey(KEY_PLOT_ITEM, MOD_NONE);
					}break;

					case ITEMS_TEMPLATE_CHEST:
					{	//Plot
							mypoMapObjectEditor->PlotChest(mypoGame, CursorX(), CursorY(), CursorLayer(), true);
						//Config
							int iChestNum = Game()->UnitSet().NumChests();
      						LL_Chest* mypoChest = &Game()->UnitSet().Chest(iChestNum);
							mypoChest->LoadAnimation
							(	"objects/chest.png", mypoGame->GraphicsDir()
							);
							mypoChest->SetDisappears(true);
					}break;
					
					case ITEMS_TEMPLATE_BARREL:
					{	//Plot
							mypoMapObjectEditor->PlotChest(mypoGame, CursorX(), CursorY(), CursorLayer(), true);
						//Config
							int iChestNum = Game()->UnitSet().NumChests();
      						LL_Chest* mypoChest = &Game()->UnitSet().Chest(iChestNum);
							mypoChest->LoadAnimation
							(	"objects/barrel.png", mypoGame->GraphicsDir()
							);
							mypoChest->SetDisappears(false);
					}break;

					case ITEMS_TEMPLATE_SACK:
					{	//Plot
							mypoMapObjectEditor->PlotChest(mypoGame, CursorX(), CursorY(), CursorLayer(), true);
						//Config
							int iChestNum = Game()->UnitSet().NumChests();
      						LL_Chest* mypoChest = &Game()->UnitSet().Chest(iChestNum);
							mypoChest->LoadAnimation
							(	"objects/sack.png", mypoGame->GraphicsDir()
							);
							mypoChest->SetDisappears(true);
					}break;

					case ITEMS_TEMPLATE_DRAWERS:
					{	//Plot
							mypoMapObjectEditor->PlotChest(mypoGame, CursorX(), CursorY(), CursorLayer(), true);
						//Config
							int iChestNum = Game()->UnitSet().NumChests();
      						LL_Chest* mypoChest = &Game()->UnitSet().Chest(iChestNum);
							mypoChest->LoadAnimation
							(	"objects/drawers.png", mypoGame->GraphicsDir()
							);
							mypoChest->SetDisappears(false);
					}break;
				}
			}break;

			case BUTTONS_MENU_MONSTERS:
			{	switch(iNum)
				{	case MONSTERS_EDIT_SET:
					{	HandleEdittingKey(KEY_EDIT_MONSTER_SET, MOD_NONE);
					}break;

					case MONSTERS_KEYS:
					{	HandleEdittingKey(KEY_EDIT_KEYS, MOD_NONE);
					}break;

					case MONSTERS_PLACE:
					{	HandleEdittingKey(KEY_PLOT_MONSTER, MOD_NONE);
					}break;
				}
			}break;

			case BUTTONS_MENU_VEHICLES:
			{	switch(iNum)
				{	case VEHICLES_EDIT_SET:
					{	HandleEdittingKey(KEY_EDIT_VEHICLE_SET, MOD_NONE);
					}break;

					case VEHICLES_EDIT_OBJECTS_SET:
					{	HandleEdittingKey(KEY_EDIT_VEHICLE_OBJECT_SET, MOD_NONE);
					}break;

					case VEHICLES_KEYS:
					{	HandleEdittingKey(KEY_EDIT_KEYS, MOD_NONE);
					}break;

					case VEHICLES_PLACE:
					{	HandleEdittingKey(KEY_PLOT_VEHICLE_OBJECT, MOD_NONE);
					}break;
				}
			}break;

			case BUTTONS_MENU_SCRIPTS:
			{	switch(iNum)
				{	case SCRIPTS_LOCAL_CLASSES:
					{	HandleEdittingKey(KEY_EDIT_CLASS_SET, MOD_NONE);
					}break;

					case SCRIPTS_GLOBAL_CLASSES:
					{	HandleEdittingKey(KEY_EDIT_GLOBAL_CLASS_SET, MOD_NONE);
					}break;

					case SCRIPTS_GLOBAL_SCRIPT:
					{	HandleEdittingKey(KEY_EDIT_GLOBAL_SCRIPT, MOD_NONE);
					}break;

					case SCRIPTS_PLACE:
					{	HandleEdittingKey(KEY_PLOT_INSTANCE, MOD_NONE);
					}break;
				}
			}break;

			case BUTTONS_MENU_TRANSPORTS:
			{	switch(iNum)
				{	case TRANSPORTS_TEMPLATE_STAIRS_UP:
					{	//Plot
							mypoMapObjectEditor->PlotTransport(mypoGame, CursorX(), CursorY(), 2, true);
						//Config
							int iTransportNum = Game()->UnitSet().NumTransports() - 1;
      						LL_Transport* mypoTransport = &Game()->UnitSet().Transport(iTransportNum);
							mypoTransport->LoadAnimation
							(	"transports/stairsup.png", mypoGame->GraphicsDir()
							);
							mypoTransport->SetTransportIfPlayerOn(true);
					}break;
					
					case TRANSPORTS_TEMPLATE_STAIRS_DOWN:
					{	//Plot
							mypoMapObjectEditor->PlotTransport(mypoGame, CursorX(), CursorY(), 2, true);
						//Config
							int iTransportNum = Game()->UnitSet().NumTransports() - 1;
      						LL_Transport* mypoTransport = &Game()->UnitSet().Transport(iTransportNum);
							mypoTransport->LoadAnimation
							(	"transports/stairsdn.png", mypoGame->GraphicsDir()
							);
							mypoTransport->SetTransportIfPlayerOn(true);
					}break;
					
					case TRANSPORTS_TEMPLATE_LADDER_UP:
					{	//Plot
							mypoMapObjectEditor->PlotTransport(mypoGame, CursorX(), CursorY(), 2, true);
						//Config
							int iTransportNum = Game()->UnitSet().NumTransports() - 1;
      						LL_Transport* mypoTransport = &Game()->UnitSet().Transport(iTransportNum);
							mypoTransport->LoadAnimation
							(	"transports/ladderup.png", mypoGame->GraphicsDir()
							);
							mypoTransport->SetTransportIfPlayerOn(true);
					}break;
					
					case TRANSPORTS_TEMPLATE_LADDER_DOWN:
					{	//Plot
							mypoMapObjectEditor->PlotTransport(mypoGame, CursorX(), CursorY(), 2, true);
						//Config
							int iTransportNum = Game()->UnitSet().NumTransports() - 1;
      						LL_Transport* mypoTransport = &Game()->UnitSet().Transport(iTransportNum);
							mypoTransport->LoadAnimation
							(	"transports/ladderdn.png", mypoGame->GraphicsDir()
							);
							mypoTransport->SetTransportIfPlayerOn(true);
					}break;
					
					case TRANSPORTS_TEMPLATE_VILLAGE:
					{	//Plot
							mypoMapObjectEditor->PlotTransport(mypoGame, CursorX(), CursorY(), 2, true);
						//Grab a graphic
							ASFC_LinkedList<string> tlimg;
							tlimg.Push("transports/village1.png");
							tlimg.Push("transports/city1.png");
							tlimg.Push("transports/shrine.png");
							string sGraphic = mypoGraphicsList->ChooseGraphic(tlimg, LL_MapObject__DEFAULT_GRAHPICS_DIR);
						//Config
							int iTransportNum = Game()->UnitSet().NumTransports() - 1;
      						LL_Transport* mypoTransport = &Game()->UnitSet().Transport(iTransportNum);
							mypoTransport->LoadAnimation
							(	sGraphic, mypoGame->GraphicsDir()
							);
							mypoTransport->SetTransportIfPlayerOn(true);
					}break;
				}
			}break;

			case BUTTONS_MENU_DECORATIONS:
			{	switch(iNum)
				{	case DECORATIONS_CHAIR:
					{	//Ask for a direction
							mypoPainter->DisplayMessage("Use the arrow keys to",
														"specify which direction the chair",
														"should be facing.", 0);
						//Ask for a direction
							int iDirection = PromptDirection();
						//Put the chair down
							switch(iDirection)
							{	case DIR_NORTH:
								{	mypoMapObjectEditor->PlotTemplateInstance
									(	mypoGame,  mypoClassSetEditor,
    									CursorX(), CursorY(), 2,
										"pushable", "chair", "objects/chair_n.png"
									);
								}break;
								case DIR_SOUTH:
								{	mypoMapObjectEditor->PlotTemplateInstance
									(	mypoGame,  mypoClassSetEditor,
    									CursorX(), CursorY(), 2,
										"pushable", "chair", "objects/chair_s.png"
									);
								}break;
								case DIR_WEST:
								{	mypoMapObjectEditor->PlotTemplateInstance
									(	mypoGame,  mypoClassSetEditor,
    									CursorX(), CursorY(), 2,
										"pushable", "chair", "objects/chair_w.png"
									);
								}break;
								case DIR_EAST:
								{	mypoMapObjectEditor->PlotTemplateInstance
									(	mypoGame,  mypoClassSetEditor,
    									CursorX(), CursorY(), 2,
										"pushable", "chair", "objects/chair_e.png"
									);
								}break;
							}
					}break;
					
					case DECORATIONS_TABLE:
					{	mypoMapObjectEditor->PlotTemplateInstance
						(	mypoGame,  mypoClassSetEditor,
    						CursorX(), CursorY(), 3,
							"pushable", "table", "objects/liltable.png"
						);
					}break;

					case DECORATIONS_CANDLES:
					{	mypoMapObjectEditor->PlotTemplateInstance
						(	mypoGame,  mypoClassSetEditor,
    						CursorX(), CursorY(), 4,
							"candles", "candles", "objects/candles.png"
						);
					}break;
					
					case DECORATIONS_BED_W:
					{	mypoMapObjectEditor->PlotTemplateInstance
						(	mypoGame,  mypoClassSetEditor,
    						CursorX(), CursorY(), 2,
							"bed", "bedw", "objects/bed1.png"
						);
					}break;
					
					case DECORATIONS_BED_E:
					{	mypoMapObjectEditor->PlotTemplateInstance
						(	mypoGame,  mypoClassSetEditor,
    						CursorX(), CursorY(), 2,
							"bed", "bede", "objects/bed3.png"
						);
					}break;
					
					case DECORATIONS_TOMB:
					{	ASFC_LinkedList<string> tlimg;
						tlimg.Push("objects/tomb.png");
						tlimg.Push("objects/cross.png");
						string sGraphic = mypoGraphicsList->ChooseGraphic(tlimg, LL_MapObject__DEFAULT_GRAHPICS_DIR);
						mypoMapObjectEditor->PlotTemplateInstance
						(	mypoGame,  mypoClassSetEditor,
    						CursorX(), CursorY(), 3,
							"tomb", "tomb", sGraphic
						);
					}break;
					
					case DECORATIONS_FOUNTAIN:
					{	mypoMapObjectEditor->PlotTemplateInstance
						(	mypoGame,  mypoClassSetEditor,
    						CursorX(), CursorY(), 3,
							"fountain", "fountain", "objects/fountain.png"
						);
					}break;
					
					case DECORATIONS_CORPSE:
					{	mypoMapObjectEditor->PlotTemplateInstance
						(	mypoGame,  mypoClassSetEditor,
    						CursorX(), CursorY(), 3,
							"corpse", "corpse", "creatures/dead.png"
						);
					}break;
					
					case DECORATIONS_SIGN:
					{	ASFC_LinkedList<string> tlimg;
						tlimg.Push("objects/sign.png");
						tlimg.Push("objects/mountedsign.png");
						string sGraphic = mypoGraphicsList->ChooseGraphic(tlimg, LL_MapObject__DEFAULT_GRAHPICS_DIR);
						mypoMapObjectEditor->PlotTemplateInstance
						(	mypoGame,  mypoClassSetEditor,
    						CursorX(), CursorY(), 3,
							"sign", "sign", sGraphic
						);
					}break;
				}
			}break;

			case BUTTONS_MENU_VIEWS:
			{	switch(iNum)
				{	case VIEWS_GEM_VIEW:
					{	HandleEdittingKey(KEY_GEM_VIEW, MOD_NONE);
					}break;

					case VIEWS_HIGHLIGHT:
					{	myfHighlightUnits = !myfHighlightUnits;
					}break;

					case VIEWS_HELP:
					{	HandleEdittingKey(KEY_HELP, MOD_NONE);
					}break;

					case VIEWS_JOT_NOTES:
					{	HandleEdittingKey(KEY_JOT_NOTES, MOD_NONE);
					}break;
				}
			}break;
		}
}
//P.. ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...  P
ASFC_DIRECTION LEDIT_MapEditor::PromptDirection()
{	//Loop until we return
	while(1 == 1)
	{	//Update Input
			myoInput.Update();
 
 		//Decide what to do based on what keys are down
	  		//- [North] -
  			if(myoInput.KeyDown(KEY_MOVECUR_NORTH))
     		{	while(myoInput.KeyDown(KEY_MOVECUR_NORTH)) myoInput.Update();
       			return(DIR_NORTH);
			}
			
			//- [South] -
			else if(myoInput.KeyDown(KEY_MOVECUR_SOUTH))
			{	while(myoInput.KeyDown(KEY_MOVECUR_SOUTH)) myoInput.Update();
   				return(DIR_SOUTH);
			}
			
			//- [Move West] -
			else if(myoInput.KeyDown(KEY_MOVECUR_WEST))
			{	while(myoInput.KeyDown(KEY_MOVECUR_WEST)) myoInput.Update();
   				return(DIR_WEST);
			}
			
			//- [Move East] -
			else if(myoInput.KeyDown(KEY_MOVECUR_EAST))
			{	while(myoInput.KeyDown(KEY_MOVECUR_EAST)) myoInput.Update();
   				return(DIR_EAST);
			}
	}
}
