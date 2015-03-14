/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			battlemap.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description:
*/
#ifndef LL_BATTLEMAP_H_
#define LL_BATTLEMAP_H_
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Dependencies
	#include <asfc/surface.h>
	#include "guimetrics.h"
	#include <iostream>
	using namespace std;

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_BattleMap
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_BattleMap
{	public:
	//Const
		const static int MAPS_ACROSS_X = 9;
		const static int MAP_SIZE_X = 11;
		const static int MAPS_ACROSS_Y = 9;
		const static int MAP_SIZE_Y = 11;
		const static int NUM_MAPS   = 81;
		const static int MAP_WIDTH  = 100;
		const static int MAP_HEIGHT = 100;
		const static Uint8 ENTER_NONE   = 0;
		const static Uint8 ENTER_FOE    = 1;
		const static Uint8 ENTER_FRIEND = 2;

	//- [Constuctors] -
		LL_BattleMap();
	//- [File I/O] -
		void Save(ofstream &oFile);
		void Load(ifstream &oFile);
	//- [Viewports] -
		int MapEdgeX(int iMap);
		int MapEdgeY(int iMap);
		void SetToMap(int iMap);
	//- [Foe\Friend (FF) Matrix] -
		bool FoeOn(int iX, int iY);
		bool FriendOn(int iX, int iY);
		void SetNoneOn(int iX, int iY);
		void SetFoeOn(int iX, int iY);
		void SetFriendOn(int iX, int iY);
		void DrawFFMatrix( ASFC_Surface &oScreen, int iStartX, int iStartY,
  						   int iPixStartX, int iPixStartY);

	protected:
	//Vars
		Uint8 myiFFMatrix[MAP_WIDTH][MAP_HEIGHT];
};

#endif
