/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			mobility.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: A mobility maps describes how a vehcile object iteracts with a terrain object 
				 (whether the vehicle can move onto a terrain with this mobility, how long it will take,
				 what directions it can move in/out of) That sort of thing.
*/
#ifndef LL_MOBILITY_H_
#define LL_MOBILITY_H_

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Dependencies
	#include <asfc/utils.h>
	#include <SDL/SDL.h>

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Mobility
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_Mobility
{	public:
	//- [Constuctors] -
 		LL_Mobility();
	//- [File I/O] -
		void Save(ofstream &oFile);
		void Load(ifstream &oFile);
 	//- [MEMVAR_MAPS] -
		MEMVAR_SETGET(SetVehicularCode,	VehicularCode,	Uint8,		myiVehicularCode);
		MEMVAR_SETGET(SetInNorth,		InNorth,		bool,		myfInNorth);
		MEMVAR_SETGET(SetInSouth,		InSouth,		bool,		myfInSouth);
		MEMVAR_SETGET(SetInWest,		InWest,			bool,		myfInWest);
		MEMVAR_SETGET(SetInEast,		InEast,			bool,		myfInEast);
		MEMVAR_SETGET(SetOutNorth,		OutNorth,		bool,		myfOutNorth);
		MEMVAR_SETGET(SetOutSouth,		OutSouth,		bool,		myfOutSouth);
		MEMVAR_SETGET(SetOutWest,		OutWest,		bool,		myfOutWest);
		MEMVAR_SETGET(SetOutEast,		OutEast,		bool,		myfOutEast);
		MEMVAR_SETGET(SetNormalTicks,	NormalTicks,	Uint8,		myiNormalTicks);
		MEMVAR_SETGET(SetDamage,		Damage,			Uint8,		myiDamage);
		MEMVAR_SETGET(SetDamageChance,	DamageChance,	Uint8,		myiChanceOfDamage);

		bool In (ASFC_DIRECTION iDir);
		bool Out(ASFC_DIRECTION iDir);
		string Description();

	protected:
	//vars
		Uint8 myiVehicularCode;		//This ability works for all vehicles with this vehicular code
		bool myfInNorth,			//Directions the creature moves from that this mobility applies to
			 myfInSouth,
			 myfInWest,
			 myfInEast;
		bool myfOutNorth,			//Directions that the vehicle can move out to
			 myfOutSouth,
			 myfOutWest,
			 myfOutEast;
		Uint8 myiNormalTicks;		//The normal # of ticks it takes to pass on this terrain
		Uint8 myiDamage;			//The # of HPs taken by walking over this terrain
		Uint8 myiChanceOfDamage;	//The % chance of this damage actually occurring
};

//Now ending mobility.h
	#endif
