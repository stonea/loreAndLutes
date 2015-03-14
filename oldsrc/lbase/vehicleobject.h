/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			vehicleobject.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description:
*/
#ifndef LL_VEHICLEOBJECTS_H_
#define LL_VEHICLEOBJECTS_H_

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Aggregates
	#include "unit.h"
//Dependencies
	#include <asfc/utils.h>

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//											LL_VehicleObject
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_VehicleObject : public LL_Unit
{	public:
	//- [Constuctors] -
 		LL_VehicleObject();
	//- [Attributes] -
		MEMVAR_SETGET(SetVehicleCode, VehicleCode, int, myiVehicleCode);
	//- [File I/O] -
		void Save(ofstream &oFile);
		void Load(ifstream &oFile, string sGraphicsPath);
	//- [Callbacks] -
		virtual void Talk();
		virtual void Look();
		virtual bool Push();
		virtual void Search();
		virtual void Attack();
    	
 	private:
		int myiVehicleCode;
};

#endif
