/*Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			itemset.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description:
*/
#ifndef LL_ITEMSET_H_
#define LL_ITEMSET_H_
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Dependencies
	#include <iostream>
//Aggregates
	#include "armor.h"
	#include "weapon.h"
	#include "scripteditem.h"

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class LL_ItemSet
{	public:
 	//- [Construction] -
		LL_ItemSet();
	//- [File I/O] -
		void Save(ofstream &oFile);
		void Load(ifstream &oFile, string sGraphicsPath);
 	//- [Armor Handeling] -
		void AddArmor(LL_Armor &oAdd);
		LL_Armor& Armor(int iIndex);
		int	NumArmors();
	//- [Weapon Handeling] -
		void AddWeapon(LL_Weapon &oAdd);
		LL_Weapon& Weapon(int iIndex);
		int NumWeapons();
	//- [ScriptedItem Handeling] -
		void AddScriptedItem(LL_ScriptedItem &oAdd);
		LL_ScriptedItem& ScriptedItem(int iIndex);
		int NumScriptedItems();

	protected:
	//Vars
		ASFC_LinkedList<LL_Armor>		 myloArmors;
		ASFC_LinkedList<LL_Weapon>		 myloWeapons;
		ASFC_LinkedList<LL_ScriptedItem> myloScriptedItems;
		LL_Armor myoDefaultArmor;
		LL_Weapon myoDefaultWeapon;
};

#endif
