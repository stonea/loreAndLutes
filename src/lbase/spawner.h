/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			vehicleobject.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description:
*/
#ifndef LL_SPAWNER_H_
#define LL_SPAWNER_H_

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Aggregates
	#include "unit.h"
//Dependencies
	#include <math.h>
	#include <asfc/utils.h>

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//											LL_VehicleObject
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_Spawner
{	public:
	//- [Constuctors] -
 		LL_Spawner();
	//- [Position] -
		MEMVAR_SETGET(SetX, X, int, myiX);
		MEMVAR_SETGET(SetY, Y, int, myiY);
		MEMVAR_GETREF(Monsters,	   ASFC_LinkedList<int>, myliMonsters);
	//- [File I/O] -
		void Save(ofstream &oFile);
		void Load(ifstream &oFile, string sGraphicsPath);
	//- [Picker] -
		int PickMonster();
    	
 	private:
		int myiX, myiY;
		ASFC_LinkedList<int> myliMonsters;
};

#endif
