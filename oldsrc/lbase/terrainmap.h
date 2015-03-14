/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			terrainmap.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: Includes an array of #s (from the map class) that represent terrains from the recognized
				 terrain set.
*/
#ifndef LL_TERRAINMAP_H_
#define LL_TERRAINMAP_H_
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Parent
	#include "map.h"
//Agregates
	#include <asfc/timer.h>
//Recognizes
	#include "terrainset.h"
	#include "mobilityterrainmap.h"
	#include <asfc/sound.h>
//Dependencies
	#include "legalmovesmap.h"
	#include <string>
	#include <fstream>
	using namespace std;
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_BorderEffect
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Border effects describe the type of animation that should occur when the player hits the border of a map
enum LL_BORDER_EFFECT
{	BORDER_EFFECT_NONE = 0,
	BORDER_EFFECT_FADE,
	BORDER_EFFECT_DISSOLVE,
	BORDER_EFFECT_TRIAMBULATE,
	BORDER_EFFECT_CHECKERBOARD,
	BORDER_EFFECT_BLEND,
	BORDER_EFFECT_SPLIT_VERTICLE,
	BORDER_EFFECT_SPLIT_HORIZONTAL,
	BORDER_EFFECT_NUMEFFECTS
};
enum LL_BORDER_WARP_TYPE
{	WARP_TYPE_ROLL,
	WARP_TYPE_DEFAULT_POSITION,
	WARP_TYPE_ROLL_LAST_POSITION,
	WARP_TYPE_DEFAULT_NUMEFFECTS
};
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_TerrainMap
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_TerrainMap : public LL_Map
{	public:
	//- [Constuctors] -
		LL_TerrainMap();
	//- [File I/O] -
		void Save(ofstream &oFile);
		void Load(ifstream &oFile, string sMusicDir);
	//- [Map Data] -
		MEMVAR_SETGET(SetMobilityTerrainMap, MobilityTerrainMap, LL_MobilityTerrainMap*, mypoMobilityTerrainMap);
		MEMVAR_SETGET(SetTerrainSet, TerrainSet, LL_TerrainSet*, mypoTerrainSet);
		MEMVAR_SETGET(SetSound, Sound,	ASFC_Sound*, mypoSound);
		LL_Terrain& GetTerrain(int iTileX, int iTileY);
		void Clear();
		void GrabLegalSpaces(int iVehicleCode, LL_LegalMovesMap* plfMap);
	//- [Updating] -
		void Draw(ASFC_Surface &oScreen, ASFC_Matrix<bool> &lLight);
		void DrawGemView(ASFC_Surface &oScreen, bool fDrawPosition = false);
		void DrawGemSpawners();
	//- [Map Data] -
		MEMVAR_SETGET(SetDescription, 		Description, 	string, mysDescription);
		MEMVAR_SETGET(SetMusicFile,			MusicFile,		string,	mysMusicFile);
		MEMVAR_SETGET(SetTerrainSetFile,	TerrainSetFile,	string,	mysTerrainSet);
		MEMVAR_SETGET(SetTicksPerMinute,	TicksPerMinute,	int,	myiTicksPerMinute);
		MEMVAR_SETGET(SetMaxMonsters,		MaxMonsters,	int,	myiMaxMonsters);
		MEMVAR_SETGET(SetChanceOfMonsters,	ChanceOfMonsters,int,	myiChanceOfMaxMonsters);		
		MEMVAR_SETGET(SetPlayerX, PlayerX, int, myiDefaultPlayerX);
		MEMVAR_SETGET(SetPlayerY, PlayerY, int, myiDefaultPlayerY);
		MEMVAR_SETGET(MapNorth,   MapNorth,int, myiMapNorth);
		MEMVAR_SETGET(MapSouth,   MapSouth,int, myiMapSouth);
		MEMVAR_SETGET(MapWest,    MapWest, int, myiMapWest);
		MEMVAR_SETGET(MapEast,	  MapEast, int, myiMapEast);
		MEMVAR_SETGET(SetMapBorderNorthY, MapBorderNorthY,	int, myiNorthBorderY);
		MEMVAR_SETGET(SetMapBorderSouthY, MapBorderSouthY,	int, myiSouthBorderY);
		MEMVAR_SETGET(SetMapBorderWestX,  MapBorderWestX,	int, myiWestBorderX);
		MEMVAR_SETGET(SetMapBorderEastX,  MapBorderEastX,	int, myiEastBorderX);
		MEMVAR_SETGET(SetNorthEffect, NorthEffect,	LL_BORDER_EFFECT, myiNorthBorderEffect);
		MEMVAR_SETGET(SetSouthEffect, SouthEffect,	LL_BORDER_EFFECT, myiSouthBorderEffect);
		MEMVAR_SETGET(SetWestEffect,  WestEffect,	LL_BORDER_EFFECT, myiWestBorderEffect);
		MEMVAR_SETGET(SetEastEffect,  EastEffect,	LL_BORDER_EFFECT, myiEastBorderEffect);
		MEMVAR_SETGET(SetNorthWarpType, NorthWarpType,	LL_BORDER_WARP_TYPE, myiNorthBorderWarpType);
		MEMVAR_SETGET(SetSouthWarpType, SouthWarpType,	LL_BORDER_WARP_TYPE, myiSouthBorderWarpType);
		MEMVAR_SETGET(SetWestWarpType,  WestWarpType,	LL_BORDER_WARP_TYPE, myiWestBorderWarpType);
		MEMVAR_SETGET(SetEastWarpType,  EastWarpType,	LL_BORDER_WARP_TYPE, myiEastBorderWarpType);
		MEMVAR_SETGET(SetFirstLoad, FirstLoad, bool, myfFirstLoad);
		MEMVAR_SETGET(SetExitX, ExitX, int, myiExitX);
		MEMVAR_SETGET(SetExitY, ExitY, int, myiExitY);
		void SetMapType(string sType);
		MEMVAR_GET(MapType, string, mysMapType);
		
	protected:
	//P- [Constuctors] -P
		void SetDefaults();
	//P- [Utilities] -P
		int Repeats(C_i3(iX, iY, iVal));
	//P- [Debugging] -P
		bool ValidVersionNum(C_s(sErrorCode), C_s(sFileType), C_i(iVersionNum));
	
	//Const
		const static int ANIMATION_DELAY = 200;
 	//Vars
 		//Map Data
 			string mysDescription;			//Map description
 			string mysMusicFile;			//Background music file
 			string mysTerrainSet;			//.terrain file to use
			LL_TerrainSet* mypoTerrainSet;	//Points to the terrain set currently used by this map
			int	   myiTicksPerMinute;		//# of ticks per minute on this map
			int	   myiMaxMonsters;			//The maximum # of monsters that may appear on this board
			int	   myiChanceOfMaxMonsters;	//The % chance of the maxmimum # of monsters appearing
			int	   myiMapNorth,				//Bordering maps
				   myiMapSouth,
   				   myiMapWest,
  				   myiMapEast;
			int	myiNorthBorderY,		//Borders
				myiSouthBorderY,
				myiWestBorderX,
				myiEastBorderX;
			int myiDefaultPlayerX,
				myiDefaultPlayerY;
			int myiExitX, myiExitY;
			LL_BORDER_EFFECT	myiNorthBorderEffect,
								myiSouthBorderEffect,
								myiWestBorderEffect,
								myiEastBorderEffect;
			LL_BORDER_WARP_TYPE	myiNorthBorderWarpType,
								myiSouthBorderWarpType,
								myiWestBorderWarpType,
								myiEastBorderWarpType;
			string mysMapType;
			LL_MobilityTerrainMap* mypoMobilityTerrainMap;
			ASFC_Sound* mypoSound;
   			ASFC_Timer myoTimer;
			bool myfFirstLoad;
};

//Now ending terrainmap.h
	#endif
