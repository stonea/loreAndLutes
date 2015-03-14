/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			battleunitmap.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "battleunitmap.h"
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_BattleUnitMap
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------------- [Clear] -
void LL_BattleUnitMap::ClearBattleUnits()
{	for(int iY = 0; iY < MAP_HEIGHT; iY++)
	{	for(int iX = 0; iX < MAP_WIDTH; iX++)
		{	for(int iL = 0; iL < MAP_LAYERS; iL++)
			{	if(myiMapSeg[iX][iY][iL] == SEG_BATTLE_ENEMY || myiMapSeg[iX][iY][iL] == SEG_BATTLE_PLAYER)
				{	myiMapSeg[iX][iY][iL] = SEG_NULL;
					myiMapOff[iX][iY][iL] = OFF_NULL;
				}
			}
		}
	}
}
//----------------------------------------------------------------------------------------- [Occupation] -
int LL_BattleUnitMap::PlayerOn(int iX, int iY)
{	//If iX, iY is off the map there's no player there
		if(iX < 0 || iY < 0 || iX > MAP_WIDTH || iY > MAP_HEIGHT)
  			return NONE;
	//Loop through all layers here, checking for players
		for(int i = 0; i < MAP_LAYERS; i++)
			if(myiMapSeg[iX][iY][i] == SEG_BATTLE_PLAYER)
				return myiMapOff[iX][iY][i];
		return NONE;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_BattleUnitMap::EnemyOn(int iX, int iY)
{	//If iX, iY is off the map there's no player there
		if(iX < 0 || iY < 0 || iX > MAP_WIDTH || iY > MAP_HEIGHT)
  			return NONE;
	//Loop through all layers here, checking for enemies
		for(int i = 0; i < MAP_LAYERS; i++)
			if(myiMapSeg[iX][iY][i] == SEG_BATTLE_ENEMY)
				return myiMapOff[iX][iY][i];
		return NONE;
}
