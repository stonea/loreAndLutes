/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			painter.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/15/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "painter.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 LL_Painter
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//------------------------------------------------------------------------------------ [Construction] -
LL_Painter::LL_Painter()
{	myiTransHighlight = 50;
	myfFlash = true;
	myoTimer.Reset();
}
//--------------------------------------------------------------------------------------- [GUI Files] -
bool LL_Painter::Load(string sFile)
{	//Vars
		ifstream oFile(sFile.c_str(), ios::binary);
		string 	 sFileType;
		int	   	 iFileVersion;
		string	 sProgramName,
  				 sProgramIcon,
		 		 sCursorImage,
		 		 sError1Image,
		 		 sError2Image,
				 sBorderFile;
		int		 iFontWidth,
				 iFontHeight;
		string	 sNormalFontImage,
				 sBoldFontImage,
				 sAccentFontImage,
 				 sTalkFontImage,
	 			 sRunicFontImage;
		int		 iMainConsoleX, 	iMainConsoleY,  iMainConsoleWidth,  iMainConsoleHeight,
				 iStatsConsoleX,	iStatsConsoleY, iStatsConsoleWidth, iStatsConsoleHeight,
				 iTalkConsoleX,		iTalkConsoleY,  iTalkConsoleWidth,  iTalkConsoleHeight,
				 iNarateConsoleX,	iNarateConsoleY,iNarateConsoleWidth,iNarateConsoleHeight;
		
 	//If the file didn't open return an error
 		if(!oFile.is_open())
 			return false;

	//Read in the file type and version
		oFile >> sFileType;
		oFile >> iFileVersion;

	//If we have the right type of file
		//"Program Name", "Program Icon", "Cursor Image", "Err 1", "Err 2", "Border file"
			sProgramName = ReadString(oFile);
			sProgramIcon = ReadString(oFile);
			sCursorImage = ReadString(oFile);
			sError1Image = ReadString(oFile);
			sError2Image = ReadString(oFile);
			sBorderFile  = ReadString(oFile);
		//%Font Width%,	%Font Height%
			oFile >> iFontWidth;
			oFile >> iFontHeight;
		//"Normal Font Image", "Bold Font Image", "Accent Font Image" "Runic Font Image"
			sNormalFontImage 	= ReadString(oFile);
			sBoldFontImage 		= ReadString(oFile);
			sAccentFontImage 	= ReadString(oFile);
			sTalkFontImage		= ReadString(oFile);
			sRunicFontImage		= ReadString(oFile);
		//%Main Position X%, %Main Position Y%, %Main Width%, %Main Height%
			oFile >> iMainConsoleX;
    		oFile >> iMainConsoleY;
       		oFile >> iMainConsoleWidth;
        	oFile >> iMainConsoleHeight;
		//%Stats Position X%, %Stats Position Y%, %Stats Width%, %Stats Height%
			oFile >> iStatsConsoleX;
    		oFile >> iStatsConsoleY;
       		oFile >> iStatsConsoleWidth;
        	oFile >> iStatsConsoleHeight;
		//%Talk Position X%, %Talk Position Y%, %Talk Width%, %Talk Height%
			oFile >> iTalkConsoleX;
    		oFile >> iTalkConsoleY;
       		oFile >> iTalkConsoleWidth;
          	oFile >> iTalkConsoleHeight;
		//%Narate Position X%, %Narate Position Y%, %Narate Width%, %Narate Height%
			oFile >> iNarateConsoleX;
    		oFile >> iNarateConsoleY;
       		oFile >> iNarateConsoleWidth;
          	oFile >> iNarateConsoleHeight;
		//Now use this read in info and setup the GUI
			//Setup the program name & icon	
				SDL_WM_SetCaption(sProgramName.c_str(), sProgramName.c_str());
				SDL_WM_SetIcon(SDL_LoadBMP(sProgramIcon.c_str()), NULL);
				myimgCursor.LoadImage(sCursorImage, COLOR_BLUE);
				myimgError1.LoadImage(sError1Image);
				myimgError2.LoadImage(sError2Image);
			//Setup the border
				myoBorder.Load(sBorderFile);
			//Setup the fonts
				myoFontPalette.AddFont(sNormalFontImage, 	iFontWidth, iFontHeight, COLOR_BLUE);
				myoFontPalette.AddFont(sBoldFontImage, 		iFontWidth, iFontHeight, COLOR_BLUE);
				myoFontPalette.AddFont(sAccentFontImage, 	iFontWidth, iFontHeight, COLOR_BLUE);
				myoFontPalette.AddFont(sTalkFontImage,		iFontWidth,	iFontHeight, COLOR_BLUE);
				myoFontPalette.AddFont(sRunicFontImage,		iFontWidth,	iFontHeight, COLOR_BLUE);
			//Setup consoles
				myoMainConsole.SetConsolePosition	(iMainConsoleX, iMainConsoleY);
				myoMainConsole.SetConsolePosition	(iMainConsoleX, iMainConsoleY);
			    myoMainConsole.SetConsoleSize		(CONSOLE_WIDTH, iMainConsoleHeight);
			    myoMainConsole.SetViewportSize		(iMainConsoleWidth, iMainConsoleHeight);
			    myoMainConsole.SetSurface(myoScreen);
			    myoMainConsole.SetFontPalette(&myoFontPalette);
			    myoStatsConsole.SetConsolePosition	(iStatsConsoleX, iStatsConsoleY);
				myoStatsConsole.SetConsolePosition	(iStatsConsoleX, iStatsConsoleY);
			    myoStatsConsole.SetConsoleSize		(iStatsConsoleWidth, iStatsConsoleHeight);
			    myoStatsConsole.SetViewportSize		(iStatsConsoleWidth, iStatsConsoleHeight);
			    myoStatsConsole.SetSurface(myoScreen);
			    myoStatsConsole.SetFontPalette(&myoFontPalette);
			    myoTalkConsole.SetConsolePosition	(iTalkConsoleX, iTalkConsoleY);
				myoTalkConsole.SetConsolePosition	(iTalkConsoleX, iTalkConsoleY);
			    myoTalkConsole.SetConsoleSize		(iTalkConsoleWidth, iTalkConsoleHeight);
			    myoTalkConsole.SetViewportSize		(iTalkConsoleWidth, iTalkConsoleHeight);
			    myoTalkConsole.SetSurface(myoScreen);
			    myoTalkConsole.SetFontPalette(&myoFontPalette);
			    myoNarateConsole.SetConsolePosition	(iNarateConsoleX, iNarateConsoleY);
				myoNarateConsole.SetConsolePosition	(iNarateConsoleX, iNarateConsoleY);
			    myoNarateConsole.SetConsoleSize		(iNarateConsoleWidth, iNarateConsoleHeight);
			    myoNarateConsole.SetViewportSize	(iNarateConsoleWidth, iNarateConsoleHeight);
			    myoNarateConsole.SetSurface(myoScreen);
			    myoNarateConsole.SetFontPalette(&myoFontPalette);
		//UI Loaded correctly
			return true;
}
//----------------------------------------------------------------------------------------- [Updating] -
void LL_Painter::Draw()
{	//The Border
		myoBorder.Draw(*myoScreen);
	//Consoles
		StatsConsole().Draw(0xFF);
		TalkConsole().Draw(0xFF);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Painter::DrawNarateConsole()
{	//Consoles
 		myoNarateConsole.Draw(0x55);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Painter::DrawUnitMap(ASFC_Matrix<bool>* plLight, bool fHighlight, bool fDrawSpawners)
{	//Vars
		int iTileX;
		int	iTileY;
		int iSeg, iOff;
		LL_Unit* tpoUnit;
		int iX, iY;
	//Calculate the location of the top left tile
		iTileX = Game()->TerrainMap().ViewX();
		iTileY = Game()->TerrainMap().ViewY();
	//Reset animations
	//	Game()->UnitSet().ResetAnimations();
	//Loop through the highlihgt color
		myiTransHighlight = myiTransHighlight + 20;
		if(myiTransHighlight > 0xFF)
			myiTransHighlight = 50;

	//Loop through all the tiles and draw them
		for(int iY = 0; iY <= PLAYFIELD_TILEHEIGHT; iY++)	
		{	for(int iX = 0; iX <= PLAYFIELD_TILEWIDTH; iX++)
			{	//If this is a valid tile
					if(	iTileX >= 0 && iTileX < Game()->TerrainMap().Width() && iTileY >= 0 &&
     					iTileY < Game()->TerrainMap().Height())
					{	//If visible					
							if((*plLight)[iX][iY])
							{	//Loop through all layers
									for(int iLayer = 0; iLayer < LL_UnitMap::MAP_LAYERS; iLayer++)
									{	//If a unit exists here draw
											if(Game()->UnitMap().IsUnitOn(iTileX, iTileY, iLayer))
											{	//If highlighting highlight it
													if(fHighlight)
													{	myoScreen->DrawFillRectangle
	             										(	iX * TILE_WIDTH + PLAYFIELD_X,
		                         							iY * TILE_HEIGHT + PLAYFIELD_Y,
	    	                     							TILE_WIDTH,
	        	                 							TILE_HEIGHT,
	            	             							COLOR_RED,
                    	             						0xFF
	                    	     						);
	                    	     					}
           										iSeg = Game()->UnitMap().SegOn(iTileX, iTileY, iLayer);
       											iOff = Game()->UnitMap().OffOn(iTileX, iTileY, iLayer);
           										tpoUnit =
           											&Game()->UnitSet().Unit(iSeg, iOff);
           											
           										//See if this unit is checking for occupation
           											bool fDrawOccupied = false;
           											if(tpoUnit->Occupied())
           											{	//Check all layers above for occupation
           													for(int iLCheck = iLayer + 1; iLCheck < LL_UnitMap::MAP_LAYERS; iLCheck++)
   															{	if(Game()->UnitMap().IsUnitOn(iTileX, iTileY, iLCheck))
																{	fDrawOccupied = true;
																}
															}
           											}
           										//If not occupied draw
           											if(!fDrawOccupied)
           											{	tpoUnit->BlitTo
		               									(	*myoScreen, iX * TILE_WIDTH + PLAYFIELD_X,
        		                 							iY * TILE_HEIGHT + PLAYFIELD_Y
                		                				);
                		                			}
                		                			else
                		                			{	tpoUnit->BlitOccupiedTo
		               									(	*myoScreen, iX * TILE_WIDTH + PLAYFIELD_X,
        		                 							iY * TILE_HEIGHT + PLAYFIELD_Y
                		                				);
                		                				iLayer = LL_UnitMap::MAP_LAYERS;
                		                			}
                                				
                                				//If highlighting highlight it
                                					if(fHighlight)
                                					{	myoScreen->DrawFillRectangle
	             										(	iX * TILE_WIDTH + PLAYFIELD_X,
		                         							iY * TILE_HEIGHT + PLAYFIELD_Y,
	    	                     							TILE_WIDTH,
	        	                 							TILE_HEIGHT,
	            	             							COLOR_ORANGE,
                    	                   					myiTransHighlight
	                    	     						);
	                    	     					}
											}
									}
							}
					}
				iTileX++;
			}
			iTileY++;
			iTileX = Game()->TerrainMap().ViewX();
		}
	//If we're drawing those crazy spawners
		if(fDrawSpawners)
		{	for(int i = 0; i < Game()->UnitSet().NumSpawners(); i++)
			{	//Grab this X, Y 
					iX = Game()->UnitSet().Spawner(i).X();
					iY = Game()->UnitSet().Spawner(i).Y();
				//If this is in the viewable area
					if(iX >= Game()->TerrainMap().ViewX()
					   && iX <= Game()->TerrainMap().ViewX() + PLAYFIELD_TILEWIDTH
					   && iY >= Game()->TerrainMap().ViewY()
					   && iY <= Game()->TerrainMap().ViewY() + PLAYFIELD_TILEWIDTH)
					{
						//Draw this shizzle fo' sho'
							myoScreen->DrawFillRectangle
	             			(	(iX - Game()->TerrainMap().ViewX()) * TILE_WIDTH + PLAYFIELD_X,
		                        (iY - Game()->TerrainMap().ViewY()) * TILE_HEIGHT + PLAYFIELD_Y,
	    	                    TILE_WIDTH,
	        	                TILE_HEIGHT,
	        	   	            COLOR_BLUE,
                    	        0x66
							);
							myoScreen->DrawFillRectangle
	             			(	(iX - Game()->TerrainMap().ViewX()) * TILE_WIDTH + PLAYFIELD_X + 5,
		                        (iY - Game()->TerrainMap().ViewY()) * TILE_HEIGHT + PLAYFIELD_Y + 5,
	    	                    TILE_WIDTH - 10,
	        	                TILE_HEIGHT - 10,
	            	            COLOR_RED,
                    	        0x66
							);
					}
			}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Painter::DrawGemSpawners()
{	//Vars
		int iPixX, iPixY;
		int iStartX, iStartY;
		int iTileWidth, iTileHeight;
	
	//Calculate the tile width & height
		iTileWidth = (PLAYFIELD_X2 - PLAYFIELD_X) / 100;
		iTileHeight= (PLAYFIELD_Y2 - PLAYFIELD_Y) / 100;
 	 								  
 	//Calculate the offset of the map (e.g. where the topleft pixel of it should be drawn)
 		iStartX = PLAYFIELD_X + ((PLAYFIELD_X2 - PLAYFIELD_X) - (iTileWidth  * 100))/2;
 		iStartY = PLAYFIELD_Y + ((PLAYFIELD_Y2 - PLAYFIELD_Y) - (iTileHeight * 100))/2;

	//Loop through all the tiles
		for(int iY = 0; iY < 100; iY++)
		{	for(int iX = 0; iX < 100; iX++)
			{	//If a node or area exists here
					if(mypoGame->UnitSet().SpawnerAt(iX, iY) >= 0)
					{	//Calculate where to draw this tile
			   				iPixX = iStartX + iTileWidth  * iX;
							iPixY = iStartY + iTileHeight * iY;
							
						//If its a node draw the node circle
							if(myfFlash)
							{	myoScreen->DrawFillCircle(iPixX + iTileWidth/2-1, iPixY + iTileHeight/2-1,
														  iTileWidth/2+1, COLOR_BLUE, 0xAA);
	      						myoScreen->DrawFillCircle(iPixX + iTileWidth/2, iPixY + iTileHeight/2,
														  iTileWidth/2, COLOR_RED, 0xAA);
							}
					}
			}
		}
	//Switch the flash state
		if(myoTimer.Ellapsed() >= TIMER_DELAY)
		{	myfFlash = !myfFlash;
			myoTimer.Reset();
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Painter::DrawPlayerInfo(int iLocked, int iSelected)
{	//Vars
		string s;
	//Clear out old data
		StatsConsole().Clear();
	//Loop through all party members
		for(int i = 0; i < Game()->Player().PartyMembers().Length(); i++)
		{	StatsConsole().CurrentFont(0);
  			if(i == iLocked)
				StatsConsole() << ">";
  			s = Game()->Player().PartyMembers()[i].State();
  			if(iSelected == i)
     			StatsConsole().CurrentFont(1);
  			StatsConsole() << s												<< " ";
			StatsConsole() << Val(Game()->Player().PartyMembers()[i].HP())	<< " ";
			StatsConsole() << Game()->Player().PartyMembers()[i].Name()		<< "\n";
		}
}
//---------------------------------------------------------------------------------------- [Prompting] -
bool LL_Painter::PromptYN(string sLine1, string sLine2, string sLine3, int iFont)
{	//Prompt with the y and N keys
		return(PromptKey(SDLK_y, SDLK_n, sLine1, sLine2, sLine3, iFont));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Painter::PromptKey(SDLKey iKey1, SDLKey iKey2, string sLine1, string sLine2, string sLine3,
						   int iFont)
{	//Draw it
		DisplayMessage(sLine1, sLine2, sLine3, iFont);
	//Now grab a Key1 or Key2
		ASFC_Input oInput;
		while(1 == 1)
  		{	oInput.Update();
    		if(oInput.KeyDown(iKey1))
  			{	while(oInput.KeyDown(iKey1)) {oInput.Update();}
  				return true;
  			}
  			if(oInput.KeyDown(iKey2))
  			{	while(oInput.KeyDown(iKey2)) {oInput.Update();}
  				return false;
  			}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Painter::DisplayMessage(string sLine1, string sLine2, string sLine3, int iFont)
{	//Vars
		int iNumChars;
		int iCenterX, iCenterY;
		int iFontWidth, iFontHeight;
		int iX;
		
	//Figure out the # of chars in the longest of those lines
		iNumChars = sLine1.size();
		if(sLine2.size() > iNumChars) iNumChars = sLine2.size();
		if(sLine3.size() > iNumChars) iNumChars = sLine3.size();
		
	//Figure out where the center of the screen is, and the fonts width and height
		iCenterX = myoScreen->GetWidth()  / 2;
		iCenterY = myoScreen->GetHeight() / 2;
		iFontWidth  = myoFontPalette[iFont].Width();
		iFontHeight = myoFontPalette[iFont].Height();
		
	//Using this info draw a rectangle border
		myoScreen->DrawRectangle(iCenterX - (iNumChars * iFontWidth)/2 - 4,
  								 iCenterY - (3 * iFontHeight)/2 - 4,
						  		 iFontWidth * iNumChars + 4, iFontHeight * 3 + 4, COLOR_WHITE, 200);
		myoScreen->DrawRectangle(iCenterX - (iNumChars * iFontWidth)/2 - 3,
  								 iCenterY - (3 * iFontHeight)/2 - 3,
						  		 iFontWidth * iNumChars + 3, iFontHeight * 3 + 3, COLOR_GRAY, 200);
		myoScreen->DrawFillRectangle(iCenterX - (iNumChars * iFontWidth)/2 - 2,
  									 iCenterY - (3 * iFontHeight)/2 - 2,
						  			 iFontWidth * iNumChars + 2, iFontHeight * 3 + 2, COLOR_BLACK, 200);
		
	//Draw these three lines of text
		myoFontPalette[iFont].WriteTo(*myoScreen, iCenterX - (sLine1.size() * iFontWidth)/2,
  									  iCenterY - iFontHeight - iFontHeight/2, sLine1);
		myoFontPalette[iFont].WriteTo(*myoScreen, iCenterX - (sLine2.size() * iFontWidth)/2,
  									  iCenterY - iFontHeight/2, sLine2);
		myoFontPalette[iFont].WriteTo(*myoScreen, iCenterX - (sLine3.size() * iFontWidth)/2,
	  								  iCenterY + iFontHeight/2, sLine3);
  	
  	//Draw the back buffer
  		myoScreen->Update();
}
//------------------------------------------------------------------------------- [Console Handelins'] -
//MEMVAR_GETREF(MainConsole,	LL_Console,	myoMainConsole);
//MEMVAR_GETREF(StatsConsole,	LL_Console,	myoStatsConsole);
//MEMVAR_GETREF(TalkConsole,	LL_Console,	myoTalkConsole);
//------------------------------------------------------------------------------------- [Game Linking] -
//MEMVAR_GETSET(SetGame, Game, ASFC_Game* mypoGame);
