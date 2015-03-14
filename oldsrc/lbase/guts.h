/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			guts.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description:
*/
#ifndef LL_GUTS_H_
#define LL_GUTS_H_

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Parent
	#include "unit.h"
//Dependencies
	#include <asfc/utils.h>
	#include "inventory.h"
	#include <asfc/console.h>
	#include "unitmap.h"

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Guts
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_Guts : public LL_Unit
{	public:
	//- [Constuctors] -
 		LL_Guts();
 		MEMVAR_SETGET(SetChanceOfFood,	ChanceOfFood, int, myiChanceOfFood);
 		MEMVAR_SETGET(SetMaxFood, 		MaxFood,	  int, myiMaxFood);
 		MEMVAR_SETGET(SetInventory,		Inventory,	  LL_Inventory*, mypoInventory);
 		MEMVAR_SETGET(SetConsole, 		Console,	  ASFC_Console*, mypoConsole);
 		MEMVAR_SETGET(SetUnitMap, 		UnitMap,	  LL_UnitMap*,	 mypoUnitMap);
	//- [Callbacks] -
		virtual void Talk();
		virtual void Look();
		virtual bool Push();
		virtual void Search();
		virtual void Attack();
		void RemoveFromMap();

 	private:
	//Vars
		int myiChanceOfFood;
		int myiMaxFood;
		LL_Inventory* mypoInventory;
  		ASFC_Console* mypoConsole;
  		LL_UnitMap*   mypoUnitMap;
};

#endif
