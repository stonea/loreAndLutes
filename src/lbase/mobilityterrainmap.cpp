/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			mobilityterrainmap.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "mobilityterrainmap.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//											LL_MobilityTerrainMap
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_MobilityTerrainMap::LL_MobilityTerrainMap()
{
}
//------------------------------------------------------------------------------------------- [File I/O] -
void LL_MobilityTerrainMap::Save(ofstream &oFile)
{	//%Num Terrains%, %Num Vehicles%
		oFile << mylMobilities.Width() << " " << mylMobilities.Height() << endl;

	//<Loop though all terrains and vehicles>
		for(int iTerrain = 0; iTerrain < mylMobilities.Width(); iTerrain++)
		{	for(int iVehicle = 0; iVehicle < mylMobilities.Height(); iVehicle++)
			{	//<Save Mobility>
					mylMobilities[iTerrain][iVehicle].Save(oFile);
			}
		}
		oFile << " ";
	//Loop through all battle-vehicle keys
		oFile << mylVehicleBattleKey.Length() << " ";
		for(int i = 0; i < mylVehicleBattleKey.Length(); i++)
		{	oFile << mylVehicleBattleKey[i].iVehicleCode1 << " ";
			oFile << mylVehicleBattleKey[i].iVehicleCode2 << " ";
			oFile << mylVehicleBattleKey[i].iBattleMap	  << " ";
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_MobilityTerrainMap::Load(ifstream &oFile)
{	//Vars
		int iNumTerrains, iNumVehicles, iNumKeys;

	//%Num Terrains%, %Num Vehicles%
		oFile >> iNumTerrains >> iNumVehicles;
		Resize(iNumTerrains, iNumVehicles);

	//<Loop though all terrains and vehicles>
		for(int iTerrain = 0; iTerrain < mylMobilities.Width(); iTerrain++)
		{	for(int iVehicle = 0; iVehicle < mylMobilities.Height(); iVehicle++)
			{	//<Load Mobility>
					mylMobilities[iTerrain][iVehicle].Load(oFile);
			}
		}
	//<Loop through all battle-vehicle keys>
		oFile >> iNumKeys;
		mylVehicleBattleKey.Resize(iNumKeys);
		for(int i = 0; i < mylVehicleBattleKey.Length(); i++)
		{	oFile >> mylVehicleBattleKey[i].iVehicleCode1;
			oFile >> mylVehicleBattleKey[i].iVehicleCode2;
			oFile >> mylVehicleBattleKey[i].iBattleMap;
		}
}
//-------------------------------------------------------------------------------------------- [Reading] -
bool LL_MobilityTerrainMap::LegalMove(int iTerrain1, int iTerrain2, int iVehicle, ASFC_DIRECTION iDir)
{	return	mylMobilities[iTerrain1][iVehicle].Out(iDir) &&
			mylMobilities[iTerrain2][iVehicle].In(OppositeDir(iDir));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_MobilityTerrainMap::LegalMoveIn(int iTerrain, int iVehicle, ASFC_DIRECTION iDir)
{	return mylMobilities[iTerrain][iVehicle].In(OppositeDir(iDir));
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_Mobility& LL_MobilityTerrainMap::Mobility (int iTerrain,  int iVehicle)
{	return(mylMobilities[iTerrain][iVehicle]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_MobilityTerrainMap::KeyBetweenVehicles(int iVehicle1, int iVehicle2)
{	//Check all keys
		for(int i = 0; i < mylVehicleBattleKey.Length(); i++)
		{	if((mylVehicleBattleKey[i].iVehicleCode1 == iVehicle1 &&
				mylVehicleBattleKey[i].iVehicleCode2 == iVehicle2) ||
				(mylVehicleBattleKey[i].iVehicleCode1 == iVehicle2 &&
				mylVehicleBattleKey[i].iVehicleCode2 == iVehicle1))
 			{
 				return(i);
 			}
		}
	//Default
		return(NO_KEY);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_MobilityTerrainMap::LL_VehicleBattleKey& LL_MobilityTerrainMap::VehicleBattleKey(int iKeyNum)
{	return(mylVehicleBattleKey[iKeyNum]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_MobilityTerrainMap::NumVehicleBattleKeys()
{	return(mylVehicleBattleKey.Length());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_MobilityTerrainMap::DeleteBattleKey(int iKey)
{	mylVehicleBattleKey.Delete(iKey);
}
//------------------------------------------------------------------------------------------- [Writting] -
void LL_MobilityTerrainMap::SetMobility(int iTerrain, int iVehicle, LL_Mobility oTo)
{	mylMobilities[iTerrain][iVehicle] = oTo;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_MobilityTerrainMap::Resize(int iNumTerrains, int iNumVehicles)
{	mylMobilities.Resize(iNumTerrains, iNumVehicles);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_MobilityTerrainMap::AddVehicleBattleKey(int iVehicle1, int iVehicle2, int iBattleMap)
{	mylVehicleBattleKey.Resize(mylVehicleBattleKey.Length() + 1);
	mylVehicleBattleKey[mylVehicleBattleKey.Length() - 1].iVehicleCode1	= iVehicle1;
	mylVehicleBattleKey[mylVehicleBattleKey.Length() - 1].iVehicleCode2	= iVehicle2;
	mylVehicleBattleKey[mylVehicleBattleKey.Length() - 1].iBattleMap	= iBattleMap;
}
//P-------------------------------------------------------------------------------------------- [Misc.] -P
ASFC_DIRECTION LL_MobilityTerrainMap::OppositeDir(ASFC_DIRECTION iDir)
{		 if(iDir == DIR_NORTH)	return DIR_SOUTH;
	else if(iDir == DIR_SOUTH)	return DIR_NORTH;
	else if(iDir == DIR_WEST)	return DIR_EAST;
	else if(iDir == DIR_EAST)	return DIR_WEST;
}
