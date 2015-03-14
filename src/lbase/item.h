/*Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			item.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: An item is a map object that a creature can possess through inventory.
*/
#ifndef LL_ITEM_H_
#define LL_ITEM_H_

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Parent
	#include "unit.h"
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Item
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_Item : public LL_Unit
{	public:
	//- [Constuctors] -
 		LL_Item();
	//- [Callbacks] -
		void Talk();
		void Look();
		void Search();
		void Attack();
	//- [Attributes Handeling] -
		MEMVAR_SETGET(SetWeight, 		Weight, 	 int, myiWeight);
		MEMVAR_SETGET(SetValue,  		Value,  	 int, myiValue);
		MEMVAR_SETGET(SetMaxHoldable,	MaxHoldable, int, myiMaxHoldable);
 	
 	private:
 	//Vars
 		//Attributes
	 		int	myiWeight,
 				myiValue,			//$ wise
 				myiMaxHoldable;
};

#endif
