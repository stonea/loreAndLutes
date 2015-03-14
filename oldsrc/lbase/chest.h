/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			chest.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description:
*/
#ifndef LL_CHEST_H_
#define LL_CHEST_H_

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Parent
	#include "unit.h"
//Dependencies
	#include <asfc/utils.h>
	#include "inventory.h"
	#include "itemset.h"
	#include <asfc/console.h>

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Chest
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_Chest : public LL_Unit
{	public:
	//Type
		enum LL_ChestItemType
		{	TYPE_ARMOR = 0,
  			TYPE_WEAPON,
  			TYPE_SCRIPTED_ITEM,
  			TYPE_GOLD,
  			TYPE_FOOD,
  			TYPE_TORCHES
		};
		struct LL_ChestItem
		{	LL_ChestItemType iType;		//The type of item (armor, weapon, gold)
			int iItemOff;				//Item numeric identifier (e.g. leather armor identifier, etc)
			int iAmount;
			double iChance;      		//The % chance of this item appearing in the chest
		};
	
	//- [Constuctors] -
 		LL_Chest();
		MEMVAR_SETGET(SetDisappears, Disappears, bool, myfDisappears);
	//- [File I/O] -
		void Save(ofstream &oFile);
		bool Load(ifstream &oFile, string sGraphicsDir);
	//- [Callbacks] -
		virtual void Talk();
		virtual void Look();
		virtual bool Push();
		virtual void Search(LL_ItemSet* poItemSet, ASFC_Console* poConsole);
		virtual void Attack();
	//- [Contents] -
		void AddArmor(int iArmor, int iAmount);
		void AddWeapon(int iWeapon, int iAmount);
		void AddScriptedItem(int iScriptedItem, int iAmount);
		void AddGold(int iAmount);
		void AddFood(int iAmount);
		void AddTorches(int iAmount);
		int NumItems();
		LL_ChestItem& Item(int iNum);
		void ClearItems();
	//- [Giving] -
		void AddToInventory(LL_Inventory* poInventory, LL_ItemSet* poItemSet, ASFC_Console* poConsole);
		
 	private:
	//Vars
		bool myfDisappears;
		ASFC_LinkedList<LL_ChestItem> myloItems;
};

#endif
