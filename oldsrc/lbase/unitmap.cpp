/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			unitmap.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "unitmap.h"
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_UnitMap
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_UnitMap::LL_UnitMap()
{
}
//---------------------------------------------------------------------------------- [Element Handeling] -
void LL_UnitMap::UpdateAfterUnitDelete(int iDeletedSeg, int iDeletedOff)
{	//Loop through all units looking for units of the same segment
		for(int iLayer = 0; iLayer < MAP_LAYERS; iLayer++)
		{	for(int iY = 0; iY < MAP_HEIGHT; iY++)
			{	for(int iX = 0; iX < MAP_WIDTH; iX++)
				{	if(myiMapSeg[iX][iY][iLayer] == iDeletedSeg)
					{	//If this unit has a higher offset promote it
							if(myiMapOff[iX][iY][iLayer] > iDeletedOff)
							{	myiMapOff[iX][iY][iLayer]--;
							}
					}
				}
			}
		}
}
//------------------------------------------------------------------------------------------- [Map Data] -
void LL_UnitMap::Clear()
{	//Reset all values to NULL
		for(int iLayer = 0; iLayer < MAP_LAYERS; iLayer++)
		{	for(int iY = 0; iY < MAP_HEIGHT; iY++)
			{	for(int iX = 0; iX < MAP_WIDTH; iX++)
				{	myiMapSeg[iX][iY][iLayer] = SEG_NULL;
				}
			}
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_UnitMap::IsPassable(int iX, int iY, int iLayerFrom)
{	return(myiMapSeg[iX][iY][iLayerFrom] == SEG_NULL);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_UnitMap::IsUnitOn(int iX, int iY, int iLayer)
{	return(myiMapSeg[iX][iY][iLayer] != SEG_NULL);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_UnitMap::IsUnitOn(int iX, int iY)
{	for(int i = 0; i < MAP_LAYERS; i++)
	{	if(IsUnitOn(iX, iY, i))
			return true;
	}
	
	return false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
Uint8 LL_UnitMap::SegOn(int iX, int iY, int iLayer)
{	return(myiMapSeg[iX][iY][iLayer]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_UnitMap::OffOn(int iX, int iY, int iLayer)
{	return(myiMapOff[iX][iY][iLayer]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
Uint8 LL_UnitMap::TopSegOn(int iX, int iY)
{	//Loop through all layers
		for(int i = MAP_LAYERS - 1; i >= 0; i--)
		{	//If a unit exists here return it
				if(IsUnitOn(iX,  iY, i))
				{	return(SegOn(iX, iY, i));
				}
		}

	//Return nada seg
		return(SEG_NULL);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_UnitMap::TopOffOn(int iX, int iY)
{	//Loop through all layers
		for(int i = MAP_LAYERS - 1; i >= 0; i--)
		{	//If a unit exists here return it
				if(IsUnitOn(iX,  iY, i))
				{	return(OffOn(iX, iY, i));
				}
		}

	//Return nada off
		return(OFF_NULL);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int	LL_UnitMap::TopLayerOn(int iX, int iY)
{	//Loop through all layers
		for(int i = MAP_LAYERS - 1; i >= 0; i--)
		{	//If a unit exists here return this layer
				if(IsUnitOn(iX,  iY, i))
				{	return(i);
				}
		}

	//Return nada
		return(OFF_NULL);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_UnitMap::SetUnitOn(int iX, int iY, int iLayer, int iSeg, int iOff)
{	myiMapSeg[iX][iY][iLayer] = iSeg;
	myiMapOff[iX][iY][iLayer] = iOff;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_UnitMap::RemoveUnitOn(int iX, int iY, int iLayer)
{	//Vars
		int iSeg, iOff;
		
	//Capture the seg and offset of the unit here
		iSeg = SegOn(iX, iY, iLayer);
		iOff = OffOn(iX, iY, iLayer);
		
	//Remove this unit
		SetUnitOn(iX, iY, iLayer, SEG_NULL, OFF_NULL);
		
	//If this segment is an item we're done
		if(iSeg == SEG_SCRIPTED_ITEMS || iSeg == SEG_WEAPONS || iSeg == SEG_ARMORS)
		{	return;
		}
		
	//Promote all units within the same seg with higher offsets
		for(int iCheckY = 0; iCheckY < MAP_HEIGHT; iCheckY++)
		{	for(int iCheckX = 0; iCheckX < MAP_WIDTH; iCheckX++)
			{	for(int iCheckL = 0; iCheckL < MAP_LAYERS; iCheckL++)
				{	if(SegOn(iCheckX, iCheckY, iCheckL) == iSeg)
					{	if(OffOn(iCheckX, iCheckY, iCheckL) > iOff)
						{	SetUnitOn(iCheckX, iCheckY, iCheckL, iSeg,
      								  OffOn(iCheckX, iCheckY, iCheckL) - 1);
						}
					}
				}
			}
		}
}
