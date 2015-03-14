/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			battlemap.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "battlemap.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_BattleMap
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_BattleMap::LL_BattleMap()
{	//Clear the FF matrix
		for(int iY = 0; iY < MAP_HEIGHT; iY++)
		{	for(int iX = 0; iX < MAP_WIDTH; iX++)
			{
   				myiFFMatrix[iX][iY] = ENTER_NONE;
			}
		}
}
//------------------------------------------------------------------------------------------- [File I/O] -
void LL_BattleMap::Save(ofstream &oFile)
{	//Vars
		char cData;
	//Loop through all tiles
		for(int iY = 0; iY < MAP_HEIGHT; iY++)
		{	for(int iX = 0; iX < MAP_WIDTH; iX++)
			{	if(myiFFMatrix[iX][iY] == ENTER_NONE)
					oFile << '.';
				else if(myiFFMatrix[iX][iY] == ENTER_FRIEND)
					oFile << 'X';
				else
					oFile << 'O';
			}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_BattleMap::Load(ifstream &oFile)
{	//Vars
		char cData;
	//Loop through all tiles
		for(int iY = 0; iY < MAP_HEIGHT; iY++)
		{	for(int iX = 0; iX < MAP_WIDTH; iX++)
			{	oFile >> cData;
				if(cData == '.')
	   				myiFFMatrix[iX][iY] = ENTER_NONE;
    			else if(cData == 'X')
    				myiFFMatrix[iX][iY] = ENTER_FRIEND;
    			else
    				myiFFMatrix[iX][iY] = ENTER_FOE;
			}
		}
}
//------------------------------------------------------------------------------------------ [Viewports] -
int LL_BattleMap::MapEdgeX(int iMap)
{	//If we have an illegal map, set to map 0
		if(iMap < 0 || iMap >= NUM_MAPS)
			return 0;

	return((iMap / MAPS_ACROSS_X) * MAP_SIZE_X);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_BattleMap::MapEdgeY(int iMap)
{	//If we have an illegal map, set to map 0
		if(iMap < 0 || iMap >= NUM_MAPS)
			return 0;

	return((iMap % MAPS_ACROSS_Y) * MAP_SIZE_Y);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
//A battle map is really a 100x100 terrain map split up into several smaller maps
//There are 9x9 smaller maps on the big map.
void LL_BattleMap::SetToMap(int iMap)
{	//Vars
		int iMapX, iMapY;
		
	//Calculate the X, Y
		iMapX = MapEdgeX(iMap);
		iMapY = MapEdgeY(iMap);
}
//--------------------------------------------------------------------------- [Foe\Friend (FF) Matrix] -
bool LL_BattleMap::FoeOn(int iX, int iY)
{	if(myiFFMatrix[iX][iY] == ENTER_FOE)
		return true;
	return false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_BattleMap::FriendOn(int iX, int iY)
{	if(myiFFMatrix[iX][iY] == ENTER_FRIEND)
		return true;
	return false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_BattleMap::SetNoneOn(int iX, int iY)
{	myiFFMatrix[iX][iY] = ENTER_NONE;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_BattleMap::SetFoeOn(int iX, int iY)
{	myiFFMatrix[iX][iY] = ENTER_FOE;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_BattleMap::SetFriendOn(int iX, int iY)
{	myiFFMatrix[iX][iY] = ENTER_FRIEND;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_BattleMap::DrawFFMatrix(ASFC_Surface &oScreen, int iStartX, int iStartY,
								int iPixStartX, int iPixStartY)
{	//Vars
		//Cursor
			int iTileX = iStartX; 		//Holds (map wise) of the location of the tile to draw
			int	iTileY = iStartY;
			int iPixX  = iPixStartX;	//Where to draw the tile
   			int	iPixY  = iPixStartY;
		//Misc. Variables
			int iWidth  = 100;	//# of tiles across the screen to draw
			int iHeight = 100;	//# of tiles down the screen to draw

	//Loop through all the tiles and draw them
		for(int iY = 0; iY < PLAYFIELD_TILEHEIGHT; iY++)
		{	for(int iX = 0; iX < PLAYFIELD_TILEWIDTH; iX++)
			{	//If this is a legal local
					if(iTileX >= 0 && iTileX < 100 && iTileY >= 0 && iTileY < 100)
					{	//If a foe exists here draw a translucent red square
							if(FoeOn(iTileX, iTileY))
							{	oScreen.DrawFillRectangle(iPixX, iPixY, TILE_WIDTH, TILE_HEIGHT,
														  COLOR_RED, 100);
						  	}
		  				//If an area exists here draw a translucent blue square
			  				if(FriendOn(iTileX, iTileY))
							{	oScreen.DrawFillRectangle(iPixX, iPixY, TILE_WIDTH, TILE_HEIGHT,
														  COLOR_BLUE, 100);
						  	}
					}
				//Move our invisible cursor to the next tile
					iTileX++;
					iPixX += TILE_WIDTH;
			}
			//Move our invisible cursor to the next row
				iTileY++;
				iTileX = iStartX;
				iPixX  = iPixStartX;
				iPixY += TILE_HEIGHT;
		}
}
