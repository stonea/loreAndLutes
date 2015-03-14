/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			mobilityterrainmap.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: A mobility terrain map maps mobilities to terrains. Descriptive, huh? Also it includes
         		 information about cross vehicular battle maps.
*/
#ifndef LL_MOBILITYTERRAINMAP_H_
#define LL_MOBILITYTERRAINMAP_H_

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Aggregates
	#include <asfc/matrix.h>
	#include "mobility.h"
	#include "vehicle.h"
//Dependencies
	#include <asfc/utils.h>
	#include <iostream>
	using namespace std;

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//											LL_MobilityTerrainMap
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_MobilityTerrainMap
{	public:
	//Const
		const static int NO_KEY = -1;
	//Type
  		struct LL_VehicleBattleKey
  		{	int iVehicleCode1;
  			int iVehicleCode2;
  			int iBattleMap;
  		};
	
	//- [Constuctors] -
 		LL_MobilityTerrainMap();
	//- [File I/O] -
		void Save(ofstream &oFile);
		void Load(ifstream &oFile);
	//- [Reading] -
		bool 		 LegalMove(int iTerrain1, int iTerrain2, int iVehicle, ASFC_DIRECTION iDir);
		bool 		 LegalMoveIn(int iTerrain, int iVehicle, ASFC_DIRECTION iDir);
		LL_Mobility& Mobility (int iTerrain,  int iVehicle);
		int KeyBetweenVehicles(int iVehicle1, int iVehicle2);
  		LL_VehicleBattleKey& VehicleBattleKey(int iKeyNum);
  		int NumVehicleBattleKeys();
  		void DeleteBattleKey(int iKey);
	//- [Writting] -
		void SetMobility(int iTerrain, int iVehicle, LL_Mobility oTo);
		void Resize(int iNumTerrains, int iNumVehicles);
    	void AddVehicleBattleKey(int iVehicle1, int iVehicle2, int iBattleMap);
    	
 	protected:
	//P- [Misc.] -P
		ASFC_DIRECTION OppositeDir(ASFC_DIRECTION iDir);
 	//Vars
		ASFC_Matrix<LL_Mobility> mylMobilities;
		ASFC_LinkedList<LL_VehicleBattleKey> mylVehicleBattleKey;
};

#endif
