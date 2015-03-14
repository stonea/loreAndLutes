/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			mapobjectremover.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Self
	#include "mapobjectremover.h"
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//											 LEDIT_MapObjectRemover
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//---------------------------------------------------------------------------------------- [Construction] -
LEDIT_MapObjectRemover::LEDIT_MapObjectRemover()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LEDIT_MapObjectRemover::RemoveInstance(int iX, int iY)
{	//If an actual unit exists at iX, iY
		if(mypoGame->UnitMap().IsUnitOn(iX, iY))
		{	//Remove it from the map objects set
				mypoGame->UnitSet().RemoveUnit(	mypoGame->UnitMap().TopSegOn(iX, iY),
    											mypoGame->UnitMap().TopOffOn(iX, iY));
			
			//Now its okay to remove it from the map (It HAS TO BE removed from the objects set 1st!)
				mypoGame->UnitMap().RemoveUnitOn(iX, iY, mypoGame->UnitMap().TopLayerOn(iX, iY));
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LEDIT_MapObjectRemover::AnyInstancesUseClass(string sIdentifier)
{	//Loop through all scripted units
		for(int i = 0; i < mypoGame->UnitSet().NumScriptedUnits(); i++)
		{	if(UpperString(mypoGame->UnitSet().ScriptedUnit(i).Class()) == UpperString(sIdentifier))
			{	return true;
			}
		}
		
	//Else no instances on this map uses this class
		return false;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LEDIT_MapObjectRemover::DeleteInstancesUsingClass(string sIdentifier)
{	//Vars
		int iX, iY;
		
	//Translate the identifier into caps
		sIdentifier = UpperString(sIdentifier);

	//Loop through all scripted units
		for(int i = 0; i < mypoGame->UnitSet().NumScriptedUnits(); i++)
		{	if(UpperString(mypoGame->UnitSet().ScriptedUnit(i).Class()) == sIdentifier)
			{	//Grab its X, Y position
					iX = mypoGame->UnitSet().ScriptedUnit(i).X();
					iY = mypoGame->UnitSet().ScriptedUnit(i).Y();
				
				//Remove this sucka'
					RemoveInstance(iX, iY);
				
   				i--;
			}
		}
}
