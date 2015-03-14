/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			terrain.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/16/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: A terrain is a map object that describes how and if a unit can move on it (through
				 mobility). Terrains also include a light effect which describes whether the terrain
 				 should generate or block light. Terrains should be contained within a TerrainSet
 				 object.
*/
#ifndef LL_TERRAIN_H_
#define LL_TERRAIN_H_

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Parent
	#include "mapobject.h"
//Aggregates
	#include <asfc/linkedlist.h>
	#include "mobility.h"
//Dependencies
	#include "guimetrics.h"

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_LIGHTEFFECT
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//A light effect describes how this particular terrain handles light (block it, generate it, etc.)
enum LL_LIGHTEFFECT
{	
	LIGHTEFFECT_NONE   = 0,
	LIGHTEFFECT_BLOCK,
	LIGHTEFFECT_ILLUMINATE,
	LIGHTEFFECT_SMALL_TORCH,
	LIGHTEFFECT_TORCH,
	LIGHTEFFECT_LIGHTHOUSE,
	LIGHEFFECT_MAX
};

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Terrain
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_Terrain : public LL_MapObject
{	public:
	//- [Constuctors] -
 		LL_Terrain();
	//- [File I/O] -
		void SaveTerrain(ofstream &oFile);
		void LoadTerrain(ifstream &oFile, string sGraphicsPath);
	//- [Callbaccks] -
		string Info();
	//- [Info Attributes] -
		MEMVAR_SET		(SetInfo, 		string, mysInfo);
		MEMVAR_SETGET	(SetCode,		Code,		int, myiCode);
		MEMVAR_SETGET	(SetColorRed, 	ColorRed, 	int, myiColorRed);
		MEMVAR_SETGET	(SetColorGreen,	ColorGreen, int, myiColorGreen);
		MEMVAR_SETGET	(SetColorBlue, 	ColorBlue, 	int, myiColorBlue);
		MEMVAR_SETGET	(SetLightEffect,LightEffect,LL_LIGHTEFFECT, myiLightEffect);
		MEMVAR_SETGET	(SetBattleMap,	BattleMap,	int, myiBattleMap);
		MEMVAR_SETGET	(SetGroup,		Group,		string, mysGroup);
	//- [Group Reading] -
		bool IsGroup(string sGroup);
		
 	private:
 	//Vars
		//Info Attributes
			string mysInfo;
			LL_LIGHTEFFECT myiLightEffect;
			int myiColorRed, myiColorGreen, myiColorBlue;
			int myiCode;
			int myiBattleMap;
			string mysGroup;
};

//Now ending terrain.h
	#endif
