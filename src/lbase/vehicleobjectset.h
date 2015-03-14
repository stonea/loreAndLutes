/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			vehicleobjectset.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description:
*/
#ifndef LL_VEHICLEOBJECTSET_H_
#define LL_VEHICLEOBJECTSET_H_
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Aggregates
	#include "vehicleobject.h"

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//											LL_VehicleObjectSet
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_VehicleObjectSet
{	public:
	//- [Constuctors] -
 		LL_VehicleObjectSet();
	//- [File I/O] -
		void Save(ofstream &oFile);
		bool Load(ifstream &oFile, string sGraphicsDir);
	//- [Handeling] -
		void AddVehicleObject(LL_VehicleObject oAdd);
		void AddDefaultVehicleObject();
		LL_VehicleObject& VehicleObject(int iIndex);
		int	NumVehicleObject();

	protected:
	//Vars
		ASFC_LinkedList<LL_VehicleObject> myloVehicles;
};

#endif
