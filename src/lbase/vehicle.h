/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			vehicle.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: A vehicle object describes how a creature moves across various terrains.
*/
#ifndef LL_VEHICLE_H_
#define LL_VEHICLE_H_

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Dependencies
	#include <asfc/utils.h>

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Vehicle
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_Vehicle
{	public:
	//- [Constuctors] -
 		LL_Vehicle(); 	
 	//- [Attribute Handeling] -
 		MEMVAR_SETGET(SetCode, Code, int, myiCode);
 		MEMVAR_SETGET(SetIdentifier, Identifier, string, mysIdentifier);	
    	
 	private:
 	//Vars
 		int myiCode;			//The Vehicular code
 		string mysIdentifier;	//Vehicle identifier (e.g. "boat". "carpet", or "walk");
};

#endif
