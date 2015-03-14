/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			terrainmap.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "terrainmap.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_TerrainMap
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_TerrainMap::LL_TerrainMap()
	: myiNorthBorderWarpType(WARP_TYPE_ROLL),
	  myiSouthBorderWarpType(WARP_TYPE_ROLL),
	  myiWestBorderWarpType(WARP_TYPE_ROLL),
	  myiEastBorderWarpType(WARP_TYPE_ROLL),
	  myiExitX(50),
	  myiExitY(50),
	  mysMapType("DEFAULT")
{	//Set various variables to their default states
		SetDefaults();
		myoTimer.Reset();
		myfFirstLoad = true;
}
//------------------------------------------------------------------------------------------- [File I/O] -
void LL_TerrainMap::Save(ofstream &oFile)
{	//Vars
		int iTile, iRepeats;
		char cTile, cRepeats;
		int iX, iY;

	//~.map 0~				File type and version number
		oFile << ".map 0" << endl;
		
	//$Map Description$
		oFile << Qoute(mysDescription) << endl;
		
	//$MIDI File$
		oFile <<  Qoute(mysMusicFile) << endl;
		
	//Terrain Set
		oFile <<  Qoute(mysTerrainSet) << endl;
	
	//"Map Type"
		oFile << Qoute(mysMapType) << endl;
	
	//%Ticks Per Minute%
		oFile << myiTicksPerMinute << endl;

	//%Maximum # of monsters%, %Chance of reaching max monsters%
		oFile << myiMaxMonsters << " " << myiChanceOfMaxMonsters << endl;
	
	//%ViewportWidth%, %ViewportHeight%, %TileWidth%, %TileHeight%,	%ViewX%, %ViewY%, %X%, %Y%, 
 	//%Map Width%, %Map Height%
 		oFile << ViewportWidth() << " "	<< ViewportHeight() << " ";
		oFile << TILE_WIDTH 	 << " " << TILE_HEIGHT		<< " ";
		oFile << ViewX() 		 << " " << ViewY()			<< " ";
		oFile << X()			 << " " << Y()				<< " ";
		oFile << Width() 	 	 << " " << Height() 		<< "\n";
 	
 	//%Map North%, %Map South%, %Map West%,	%Map West%
 		oFile <<  myiMapNorth << endl;
 		oFile <<  myiMapSouth << endl;
 		oFile <<  myiMapWest  << endl;
 		oFile <<  myiMapEast  << endl;
 		 	
	//%North Border Y%,	%South Border Y%,	%West Border X%,	%East Border X%
		oFile << myiNorthBorderY << " " << myiSouthBorderY << " " << myiWestBorderX <<  " " <<
  				 myiEastBorderX  << endl;

	//%North Border Effect%, %South Border Effect%,	%West Border Effect%, %East Border Effect%
		oFile << myiNorthBorderEffect << " " << myiSouthBorderEffect << " " <<
				 myiWestBorderEffect  << " " << myiEastBorderEffect  << endl;

	//%North Border Warp%, %South Border Warp%,	%West Border Warp%, %East Border Warp%
		oFile << myiNorthBorderWarpType << " " << myiSouthBorderWarpType << " " <<
				 myiWestBorderWarpType  << " " << myiEastBorderWarpType  << endl;
	
	//%Default PlayerX%, %Default PlayerY%
		oFile << myiDefaultPlayerX << " " << myiDefaultPlayerY << endl;
	
	//"Error Image File Path and Name"
//		oFile <<  Qoute(mysimgError) << endl;
		oFile << Qoute("./data/gui/editor/error.png") << endl;
		
	//'Dummy character (to mark where we start reading in terrains'	//From this point no whitespace!
		oFile << '|';

	//Record all the map data
		//Set iX, iY to the start
			iX = 0;
			iY = 0;
		//While we still have more tiles to save
			while(iY < Height())
			{	//Get info on the current tile
					iTile 	 = Get(iX, iY);				//The actual tile code
					iRepeats = Repeats(iX, iY, iTile);	//The # of times this tile repeats
					cTile    = char(iTile);
					cRepeats = char(iRepeats);
					
				//Save this information as characterss
					oFile.write(&cTile, 1);
					oFile.write(&cRepeats, 1);
					
				//Move the cursor
					iX += iRepeats;
					while(iX >= Width())
					{	iX -= Width();
						iY++;
					}
			}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_TerrainMap::Load(ifstream &oFile, string sMusicDir)
{	//Vars
		string 	sFileType;
		int	   	iVersionNumber;
		int	   	iViewportWidth, iViewportHeight,
				iTileWidth, iTileHeight,
				iViewX, iViewY,
				iX, iY,
				iMapWidth, iMapHeight;
		string	sErrorImagePath;
		unsigned char	cRepeats, cTerrainNum;
		int		iRepeats, iTerrainNum;
		int		ti;
	
	//~.map 0~				File type and version number
		oFile >> sFileType;
  		oFile >> iVersionNumber;
  	//This is the first load (by default)
  		myfFirstLoad = true;
    //If we have a valid version	
		if(ValidVersionNum("cTerrainMap::Load 000, Invalid file type or version", sFileType,
			iVersionNumber))
		{	//$Map Description$
				mysDescription = ReadString(oFile);
		
			//$MIDI File$
				mysMusicFile = ReadString(oFile);
				string tsMusicFile = sMusicDir + "/" + mysMusicFile;
				mypoSound->LoadMusic(tsMusicFile);
				mypoSound->PlayMusic();
		
			//Terrain Set
				mysTerrainSet = ReadString(oFile);
	
			//"Map Type"
				mysMapType = ReadString(oFile);
	
			//%Ticks Per Minute%
				oFile >> myiTicksPerMinute;

			//%Maximum # of monsters%, %Chance of reaching max monsters%
				oFile >> myiMaxMonsters >> myiChanceOfMaxMonsters;
	
			//%ViewportWidth%, %ViewportHeight%, %TileWidth%, %TileHeight%,	%ViewX%, %ViewY%, %X%, %Y%, 
		 	//%Map Width%, %Map Height%
 				//Read in various metrics
					oFile >> iViewportWidth;
					oFile >> iViewportHeight;
					oFile >> iTileWidth;
					oFile >> iTileHeight;
					oFile >> iViewX;
					oFile >> iViewY;
					oFile >> iX;
					oFile >> iY;
					oFile >> iMapWidth;
					oFile >> iMapHeight;
	
				//Using this info set various vars and stuff
					SetViewportWidth(iViewportWidth);
					SetViewportHeight(iViewportHeight);
				/*	SetTileWidth(iTileWidth);		!!!
					SetTileHeight(iTileHeight);*/
					SetViewX(iViewX);
					SetViewY(iViewY);
					SetX(iX);
					SetY(iY);
					Resize(iMapWidth, iMapHeight);
		
		 	//%Map North%, %Map South%, %Map West%,	%Map West%
 				oFile >> myiMapNorth;
		 		oFile >> myiMapSouth;
 				oFile >> myiMapWest;
		 		oFile >> myiMapEast;
 		 	
			//%North Border Y%,	%South Border Y%,	%West Border X%,	%East Border X%
				oFile >> myiNorthBorderY >> myiSouthBorderY >> myiWestBorderX >> myiEastBorderX;

			//%North Border Effect%, %South Border Effect%,	%West Border Effect%, %East Border Effect%
				oFile >> ti;		myiNorthBorderEffect = LL_BORDER_EFFECT(ti);
     			oFile >> ti;		myiSouthBorderEffect = LL_BORDER_EFFECT(ti);
     			oFile >> ti;   		myiWestBorderEffect	 = LL_BORDER_EFFECT(ti);
        		oFile >> ti;		myiEastBorderEffect  = LL_BORDER_EFFECT(ti);

			//%North Border Warp%, %South Border Warp%,	%West Border Warp%, %East Border Warp%
				oFile >> ti;		myiNorthBorderWarpType = LL_BORDER_WARP_TYPE(ti);
     			oFile >> ti;		myiSouthBorderWarpType = LL_BORDER_WARP_TYPE(ti);
     			oFile >> ti;   		myiWestBorderWarpType  = LL_BORDER_WARP_TYPE(ti);
        		oFile >> ti;		myiEastBorderWarpType  = LL_BORDER_WARP_TYPE(ti);
	
			//%Default PlayerX%, %Default PlayerY%
				oFile >> myiDefaultPlayerX >> myiDefaultPlayerY;
	
			//"Error Image File Path and Name"
				mysimgErr = ReadString(oFile);
				LoadErrImage(mysimgErr);
		
			//Read in the map data (NOTE: iX, iY now used to hold map locations)
				//Reset iX, iY
	    			iX = 0; iY = 0;
	    			
 				//Read in the dummy marking character
 					oFile >> cTerrainNum;
 					
				//While we haven't read in all the terrains yet	    			
					while(iY < iMapHeight)
					{	//Get info on the current tile
							oFile.read(&cTerrainNum, 1);
							oFile.read(&cRepeats, 1);
							iTerrainNum  = (int)(cTerrainNum);
							iRepeats     = (int)(cRepeats);
													
						//Go through and plot down these terrains
						for(int i = 0; i < iRepeats; i++)
						{	//Plot here (if legal)
								if(iX >= 0 && iX < iMapWidth && iY >= 0 && iY < iMapHeight)
								{	Set(iX, iY, iTerrainNum);
		     					}
				
							//Move down a plot
								iX++;
					
      						//If the cursor needs to go onto a new line	
								while(iX >= iMapWidth)
								{	iX -= iMapWidth;
									iY++;
								}
						}
					}
		}
}
//------------------------------------------------------------------------------------------- [Map Data] -
void LL_TerrainMap::SetMapType(string sType)
{	mysMapType = UpperString(sType);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//MEMVAR_SETGET(SetTerrainSet, TerrainSet, LL_TerrainSet*, mypoTerrainSet);
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_Terrain& LL_TerrainMap::GetTerrain(int iTileX, int iTileY)
{	return(mypoTerrainSet->Terrain(Get(iTileX, iTileY)));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_TerrainMap::Clear()
{	//Loop though all the tiles
		for(int iY = 0; iY < Height(); iY++)
			for(int iX = 0; iX < Width(); iX++)
				Set(iX, iY, 0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_TerrainMap::GrabLegalSpaces(int iVehicleCode, LL_LegalMovesMap* plfMap)
{	//Vars
		int iCodeOn;
	
	//Loop through all spaces
		for(int iY = 0; iY < 100; iY++)
		{	for(int iX = 0; iX < 100; iX++)
			{	//Grab the terrain code at iX, iY
					iCodeOn = mypoTerrainSet->Terrain(myliData[iX][iY]).Code();
     						  
   				if(iY-1 > 0)
    			{	if(	mypoMobilityTerrainMap->LegalMove(iCodeOn,
						mypoTerrainSet->Terrain(myliData[iX][iY-1]).Code(), iVehicleCode, DIR_NORTH))
					{
						(*plfMap).SetLegalNorth(iX, iY, true);
					}
				}
	
				if(iY+1 < 100)
				{	if(	mypoMobilityTerrainMap->LegalMove(iCodeOn,
						mypoTerrainSet->Terrain(myliData[iX][iY+1]).Code(), iVehicleCode, DIR_SOUTH))
					{
						(*plfMap).SetLegalSouth(iX, iY, true);
					}
				}
	
				if(iX-1 > 0)
				{	if(	mypoMobilityTerrainMap->LegalMove(iCodeOn,
						mypoTerrainSet->Terrain(myliData[iX-1][iY]).Code(), iVehicleCode, DIR_WEST))
					{
						(*plfMap).SetLegalWest(iX, iY, true);
					}
				}
	
				if(iX+1 < 100)
				{	if(	mypoMobilityTerrainMap->LegalMove(iCodeOn,
						mypoTerrainSet->Terrain(myliData[iX+1][iY]).Code(), iVehicleCode, DIR_EAST))
					{
						(*plfMap).SetLegalEast(iX, iY, true);
					}
				}
			}
		}
}
//------------------------------------------------------------------------------------------- [Updating] -
//Draws the map
void LL_TerrainMap::Draw(ASFC_Surface &oScreen, ASFC_Matrix<bool> &lLight)
{	//Vars
		//Cursor
			int iTileX = myiViewX; 		//Holds (map wise) of the location of the tile to draw
			int	iTileY = myiViewY;
			int iPixX  = myiX;			//Where to draw the tile
   			int	iPixY  = myiY;			
		//Terrain & Last Terrain Info
			int iLastTerrainCode = -1;
			int iTerrainCode;
			LL_Terrain* pTerrain;
		//Misc. Variables
			int iWidth  = Width();	//# of tiles across the screen to draw
			int iHeight = Height();	//# of tiles down the screen to draw
			
	//Reset animations if enough time has passed
		if(myoTimer.Ellapsed(ANIMATION_DELAY))
		{	myoTimer.Reset();
			mypoTerrainSet->ResetAnimations();
		}
		
	//Loop through all the tiles and draw them
			for(int iY = 0; iY < myiViewportHeight; iY++)	
			{	for(int iX = 0; iX < myiViewportWidth; iX++)
				{	//If this is a valid tile
						if(iTileX >= 0 && iTileX < iWidth && iTileY >= 0 && iTileY < iHeight)
						{	//Grab the terrain here, if its new grab it
	   		 					iTerrainCode = Get(iTileX, iTileY);
     							if(iTerrainCode != iLastTerrainCode)
								{	//Grab this terrain	(if valid)
										if(iTerrainCode != NO_TILE)
    	     								pTerrain = &GetTerrain(iTileX, iTileY);
         								
									iLastTerrainCode = iTerrainCode;
								}
								
							//Draw this terrain	(if valid) and seen
								if(iTerrainCode != NO_TILE && lLight[iX][iY])
	     						{  			pTerrain->BlitTo(oScreen, iPixX, iPixY);
	     						}
						}
					//Or draw the Invalid tile sybol:
						else
						{	myimgErr.BlitTo(oScreen, iPixX, iPixY);
						}
					//Move our invisible cursor to the next tile
						iTileX++;
						iPixX += TILE_WIDTH;
				}
				//Move our invisible cursor to the next row
					iTileY++;
					iTileX = myiViewX;
					iPixX  = myiX;
					iPixY += TILE_HEIGHT;
			}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//Draws the map in "gem view"
void LL_TerrainMap::DrawGemView(ASFC_Surface &oScreen, bool fDrawPosition)
{	//Vars
		int iPixX, iPixY, iPixX2, iPixY2;
		int iStartX, iStartY;
		int iTileWidth, iTileHeight;
		LL_Terrain* pTerrain;
		
	//Draw the background black rect
		oScreen.DrawFillRectangle(PLAYFIELD_X, PLAYFIELD_Y, PLAYFIELD_X2 - PLAYFIELD_X,
 	 							  PLAYFIELD_Y2 - PLAYFIELD_Y, COLOR_BLACK, 255);
 	 							  
	//Calculate the tile width & height
		iTileWidth = (PLAYFIELD_X2 - PLAYFIELD_X) / Width();
		iTileHeight= (PLAYFIELD_Y2 - PLAYFIELD_Y) / Height();
 	 								  
 	//Calculate the offset of the map (e.g. where the topleft pixel of it should be drawn)
 		iStartX = PLAYFIELD_X + ((PLAYFIELD_X2 - PLAYFIELD_X) - (iTileWidth  * Width()))/2;
 		iStartY = PLAYFIELD_Y + ((PLAYFIELD_Y2 - PLAYFIELD_Y) - (iTileHeight * Height()))/2;

	//Loop through all the tiles
		for(int iY = 0; iY < Height(); iY++)
		{	for(int iX = 0; iX < Width(); iX++)
			{	//Calculate where to draw this tile
	   				iPixX = iStartX + iTileWidth  * iX;
					iPixY = iStartY + iTileHeight * iY;
					
				//Grab & Draw this tile
					pTerrain = &GetTerrain(iX, iY);
					oScreen.DrawFillRectangle(iPixX, iPixY, iTileWidth, iTileHeight,
     							pTerrain->ColorRed(), pTerrain->ColorGreen(), pTerrain->ColorBlue(), 255);
			}
		}
		
	//If we have to draw our screen position draw it
		if(fDrawPosition)
		{	//Calculate where to the screen
	   			iPixX  = iStartX + iTileWidth  * ViewX();
				iPixY  = iStartY + iTileHeight * ViewY();
				iPixX2 = iStartX + iTileWidth  * (ViewX() + myiViewportWidth);
				iPixY2 = iStartY + iTileHeight * (ViewY() + myiViewportHeight);
				
				if(iPixX < iStartX)
					iPixX = iStartX;
				if(iPixY < iStartY)
					iPixY = iStartY;
				
				if(iPixX2 > iStartX + iTileWidth * Width())
    				iPixX2 = iStartX + iTileWidth * Width();
    			if(iPixY2 > iStartY + iTileHeight * Height())
    				iPixY2 = iStartY + iTileHeight * Height();
				
				oScreen.DrawRectangle(iPixX,   iPixY,   iPixX2 - iPixX, iPixY2 - iPixY, COLOR_WHITE, 255);
				oScreen.DrawRectangle
    				(iPixX-1, iPixY-1, iPixX2 - iPixX + 2, iPixY2 - iPixY + 2, COLOR_WHITE, 255);
		}
}
//P-------------------------------------------------------------------------------------- [Constuctors] -P
//Sets cMap to its default state
void LL_TerrainMap::SetDefaults()
{	SetViewportWidth(11);
	SetViewportHeight(11);
	SetViewX(0);
	SetViewY(0);
	SetX(0);
	SetY(0);
}
//P---------------------------------------------------------------------------------------- [Utilities] -P
//Returns the # of times (1-255) that iVal repeats in the matrix from iX, iY
int LL_TerrainMap::Repeats(C_i3(iX, iY, iVal))
{	int iCurrentX, iCurrentY;
	int iRepeats = 0;
	bool fDone = false;
	const int MAX_REPEATS = 255;	//The # of repeats allowed by maximum

	//Set the current coods to the current values passed by params
		iCurrentX = iX;
		iCurrentY = iY;
				
	//While our current value matches the value we want to count and we're not off the matrix
		while(fDone == false)
		{	//If we have a repeat
				if(Get(iCurrentX, iCurrentY) == iVal)
				{	//Increment the repeats counter
				 		iRepeats++;
		
   					//Move the cursor
						iCurrentX++;

					//See if we should go to the next y
						while(iCurrentX >= Width())
						{	iCurrentX -= Width();
							iCurrentY++;
						}
			
					//Make sure we're still on the matrix
						if(iCurrentY >= Height())
							fDone = true;
					
					//Make sure we still have room for more repeats
						if(iRepeats >= MAX_REPEATS)
							fDone  = true;
				}
			//If we have a non repeater
				else
				{	fDone = true;
				}
		}
	
	//Return the # of repeats
		return iRepeats;
}
//P---------------------------------------------------------------------------------------- [Debugging] -P
//Makes sure iVersionNumber is the correct version number for a .terrain file, if it is return true
bool LL_TerrainMap::ValidVersionNum(C_s(sErrorCode), C_s(sFileType), C_i(iVersionNum))
{	//Const
		const string REQUIRED_FILE_TYPE 		= ".map";	//Holds the required file type
		const int	 REQUIRED_VERSION_NUMBER	= 0;		//Holds the required version number
		
	//If invalid
		if(sFileType != REQUIRED_FILE_TYPE || iVersionNum != REQUIRED_VERSION_NUMBER)
		{	cout << sErrorCode << endl;
			cout << "--[File Type]-->               "  << sFileType   				<< endl;
			cout << "--[Required File Type]-->      "  << REQUIRED_FILE_TYPE   		<< endl;
			cout << "--[Version Number]-->          "  << iVersionNum   			<< endl;
			cout << "--[Required Version Number]--> "  << REQUIRED_VERSION_NUMBER   << endl;
			return false;
		}
		else
			return true;
}
