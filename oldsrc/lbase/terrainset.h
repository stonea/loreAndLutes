/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			terrainset.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: Just contains lots of terrains, mapping each to a numerical identifier.
	 Notes:		 Remember! Terrain sets want to work with map files (vs. 0), and thus there can not
	 			 be > 256 terrains!
*/
#ifndef LL_TERRAINSET_H_
#define LL_TERRAINSET_H_
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Parents
	#include "set.h"
//Aggregates
	#include "terrain.h"
//Dependencies
	#include <asfc/utils.h>
	#include <iostream>
	#include "terrain.h"
	#include "guimetrics.h"

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_TerrainSet
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_TerrainSet : public LL_Set
{	public:
	//Const
		static const int MAX_NUM_TERRAINS = 254;
	
	//- [Constuctors] -
 		LL_TerrainSet();
	//- [Terrains Handeling] -
		void 	  	AddTerrain(LL_Terrain &oAdd);
		void 	  	RemoveTerrain(int &iTerrainNum);
		LL_Terrain& Terrain(C_i(iTerrainNum));
	  	int 	  	NumTerrains();
	  	void	  	ResetAnimations();		//Reset animation cycle on all terrains
	//- [File I/O] -
		void Save(ofstream &oFile);
		bool Load(ifstream &oFile, string sGraphicsPath);

 	private:
 	//P- [Debugging] -P
 		//Makes sure terrain iTerrainNum is a valid terrain number if it is return true, else false
	 		bool ValidTerrainNum(C_s(sErrorCode), C_i(iTerrainNum));
		//Makes sure iVersionNumber is the correct file type and version number for a .terrain file, if it is return true
	 		bool ValidVersionNum(C_s(sErrorCode), C_s(sFileType), C_i(iVersionNum));
 	
 	//Vars
 		ASFC_LinkedList<LL_Terrain>	myloTerrains;
};

//Now ending terrainset.h
	#endif
