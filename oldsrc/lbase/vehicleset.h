/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			vehicleset.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/19/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: A container of vehicles.
*/
#ifndef LL_VEHICLESET_H_
#define LL_VEHICLESET_H_
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Parent
	#include "set.h"
//Aggregates
	#include "vehicle.h"
	#include <asfc/linkedlist.h>

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_VehicleSet
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_VehicleSet : public LL_Set
{	public:
	//- [Constuctors] -
 		LL_VehicleSet();	
	//- [Vehicle Handeling] -
		void 	  	AddVehicle(LL_Vehicle &oAdd);
		void 	  	RemoveVehicle(int &iVehicleNum);
		LL_Vehicle& Vehicle(C_i(iVehicleNum));
	  	int 	  	NumVehicles();
 	//- [File I/O] -
		void Save(ofstream &oFile);
		void Load(ifstream &oFile);

  	protected:
	//P- [Error Handeling] -P
		bool ValidVersionNum(C_s(sErrorCode), C_s(sFileType), C_i(iVersionNum));
 	//Vars
 		ASFC_LinkedList<LL_Vehicle>	myloVehicles;
};

//Now ending vehicleset.h
	#endif
