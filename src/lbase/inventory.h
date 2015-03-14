/*Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			inventory.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: An inventory object realizes 
*/
#ifndef LL_INVENTORY_H_
#define LL_INVENTORY_H_
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Aggregates
	#include <asfc/linkedlist.h>
//Depenencies
	#include <string>
	#include "itemset.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Inventory
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_Inventory
{	public:
	//- [Constuctors] -
 		LL_Inventory();
 		void Init(LL_ItemSet* poSet);
	//- [File I/O] -
		void SaveRecordingInfo(ofstream &oFile);
		void LoadRecordingInfo(ifstream &oFile, string sGraphicsDir);
	//- [Give and take] -
		void GiveArmor(int iNum, int iAmount);
		bool TakeArmor(int iNum, int iAmount);
		int  Armors(int iNum);
		void SetArmors(int iNum, int iTo);
		void GiveWeapon(int iNum, int iAmount);
		bool TakeWeapon(int iNum, int iAmount);
		int  Weapons(int iNum);
		void SetWeapons(int iNum, int iTo);
		void GiveScriptedItem(int iNum, int iAmount);
		bool TakeScriptedItem(int iNum, int iAmount);	
		int  ScriptedItems(int iNum);
		void SetScriptedItems(int iNum, int iTo);
  		void GiveGold(int iAmount);
		bool TakeGold(int iAmount);
		MEMVAR_SETGET(SetGold, Gold, int, myiGold);
		void GiveFood(int iAmount);
		bool TakeFood(int iAmount);
		MEMVAR_SETGET(SetFood, Food, int, myiFood);
		void GiveTorches(int iAmount);
		bool TakeTorches(int iAmount);
		MEMVAR_SETGET(SetTorches, Torches, int, myiTorches);
	//- [List generation] -
		ASFC_LinkedList<string> BattleItemInventory(LL_ItemSet* poSet);
		ASFC_LinkedList<string> ScriptedItemInventory(LL_ItemSet* poSet);
		int ScriptedItemNum(int iNum);
	//- [List information] -
		int NumTypesArmors();
		int NumTypesWeapons();
		int NumTypesScriptedItems();

	protected:
	//Vars
		ASFC_LinkedList<int> mylArmors;
		ASFC_LinkedList<int> mylWeapons;
		ASFC_LinkedList<int> mylScriptedItems;
		int myiGold, myiFood, myiTorches;
		LL_ItemSet* mypoSet;
};

//Now ending inventory.h
	#endif
