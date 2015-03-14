/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			route.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: A route describes a series of movements to get from one coordinate on a map to another.
				 For example to get to from (0,0) to (5,1) the route might go: DIR_EAST, DIR_EAST,
				 DIR_EAST, DIR_SOUTH, DIR_EAST, DIR_EAST
*/
#ifndef LL_ROUTE_H_
#define LL_ROUTE_H_
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Parent
	#include <asfc/linkedlist.h>
//Dependencies
	#include <asfc/utils.h>
	#include <iostream>

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Route
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_Route : public ASFC_LinkedList<ASFC_DIRECTION>
{	public:
	//- [Constuctors] -
 		LL_Route();
	//- [File I/O] -
		void Save(ofstream &oFile);
		void Load(ifstream &oFile);
		string String();
	//- [Optimization] -
		void Optimize();
		void Copy(LL_Route& oFrom);
	//- [Appending] -
		void AppendRoute(LL_Route oRHS, bool fStart);
		ASFC_DIRECTION OppositeDir(ASFC_DIRECTION iDirection);
	//- [Placing] -
		MEMVAR_SETGET(SetX, X, int, myiStartX);
		MEMVAR_SETGET(SetY, Y, int, myiStartY);
		MEMVAR_SETGET(SetEndX, EndX, int, myiEndX);
		MEMVAR_SETGET(SetEndY, EndY, int, myiEndY);
 		
	protected:
		int myiStartX, 	myiStartY;
		int myiEndX,	myiEndY;
};

#endif
