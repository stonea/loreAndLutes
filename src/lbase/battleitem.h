/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			battleitem.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/19/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: A battle item is an item that can be equipped. All equiped items effect how the player
				 attacks and defends in battle.
*/
#ifndef LL_BATTLEITEM_H_
#define LL_BATTLEITEM_H_
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Parent
	#include "item.h"

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_BattleItem
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_BattleItem : public LL_Item
{	public:
	//- [Constuctors] -
 		LL_BattleItem();
	//- [Callbacks] -
		void Run();
		void Talk();
		void Look();
		void Search();
		void Attack();
	//- [Equipabibility] -
 			MEMVAR_SETGET(SetEquipsHands, EquipsHands, int,  myiEquipsHands);
 			MEMVAR_SETGET(SetEquipsArms,  EquipsArms,  bool, myfEquipsArms);
 			MEMVAR_SETGET(SetEquipsTorso, EquipsTorso, bool, myfEquipsTorso);
 			MEMVAR_SETGET(SetEquipsHead,  EquipsHead,  bool, myfEquipsHead);
 	
 	private:
 	//Vars
 		//Equipabiility
 			int		myiEquipsHands;
			bool	myfEquipsArms,
   					myfEquipsTorso,
   					myfEquipsHead;
};

#endif
