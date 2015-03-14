/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			unitmap.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: 
*/
#ifndef UNITMAP_H_
#define UNITMAP_H_

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Realizes
//	#include "unitset.h"
//Dependencies
	#include <asfc/utils.h>
	#include "guimetrics.h"
	#include <asfc/matrix.h>

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_UnitMap
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_UnitMap
{	public:
	//Const
		const static int LAYER_VEHICLE = 2;
		const static int MAP_WIDTH	= 100;
		const static int MAP_HEIGHT	= 100;
		const static int MAP_LAYERS	= 5;
		static const int SEG_SCRIPTED_ITEMS = 0x0;
		static const int SEG_WEAPONS		= 0x1;
		static const int SEG_ARMORS			= 0x2;
		static const int SEG_MONSTERS		= 0x3;
		static const int SEG_SCRIPTED_UNITS	= 0x4;
		static const int SEG_BATTLE_ENEMY	= 0x5;
		static const int SEG_BATTLE_PLAYER	= 0x6;
		static const int SEG_CHESTS			= 0x7;
		static const int SEG_TRANSPORTS		= 0x8;
		static const int SEG_GUTS			= 0x9;
		static const int SEG_VEHICLE		= 0xA;
		static const int SEG_SPAWNER		= 0xB;
		static const int SEG_PLAYER			= 0xFE;
		static const int SEG_NULL			= 0xFF;
		static const int OFF_NULL			= 0xFF;
		static const int OFF_PLAYER			= 0x0;

	//- [Constructor] -
		LL_UnitMap::LL_UnitMap();
	//- [Element Handeling] -
		void UpdateAfterUnitDelete(int iDeletedSeg, int iDeletedOff);
	//- [Map Data] -
		void Clear();
		bool IsPassable(int iX, int iY, int iLayerFrom);
		bool IsUnitOn(int iX, int iY, int iLayer);
		bool IsUnitOn(int iX, int iY);
		Uint8 SegOn(int iX, int iY, int iLayer);
		int   OffOn(int iX, int iY, int iLayer);
		Uint8 TopSegOn(int iX, int iY);
		int   TopOffOn(int iX, int iY);
		int	  TopLayerOn(int iX, int iY);
		void  SetUnitOn(int iX, int iY, int iLayer, int iSeg, int iOff);
		void  RemoveUnitOn(int iX, int iY, int iLayer);
		MEMVAR_SETGET(SetKnownPlayerX, KnownPlayerX, int, myiKnownPlayerX);
		MEMVAR_SETGET(SetKnownPlayerY, KnownPlayerY, int, myiKnownPlayerY);
	
  	protected:
   	//Vars
//   		LL_UnitSet* mypoUnitSet;
		Uint8 myiMapSeg[MAP_WIDTH][MAP_HEIGHT][MAP_LAYERS];
		int	  myiMapOff[MAP_WIDTH][MAP_HEIGHT][MAP_LAYERS];
		int	  myiKnownPlayerX, myiKnownPlayerY;
};

#endif
