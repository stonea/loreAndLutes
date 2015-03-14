/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			itemseteditor.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: <Please Enter Here>
*/
#ifndef LEDIT_ITEMSETEDITOR_H_
#define LEDIT_ITEMSETEDITOR_H_

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Parent
	#include "consoleeditor.h"
//Dependencies
	#include <lbase/unitset.h>
	#include "armoreditor.h"
	#include "weaponeditor.h"
	#include "scripteditemeditor.h"

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class LEDIT_ItemSetEditor : public LEDIT_ConsoleEditor
{	public:
	//Type
		enum EDITOPTIONS
		{	EDITOPTION_ARMORS = 0,
			EDITOPTION_WEAPONS,
			EDITOPTION_SCRIPTS,
			EDITOPTION_CHESTS,		//Only for choosing!
		};

	//- [Construction] -
		LEDIT_ItemSetEditor();
		MEMVAR_SETGET(SetFileChooser, FileChooser, LEDIT_FileChooser*, mypoFileChooser);
		MEMVAR_SETGET(SetGame, Game, LL_Game*, mypoGame);
		MEMVAR_SETGET(SetArmorEditor, ArmorEditor, LEDIT_ArmorEditor*, mypoArmorEditor);
		MEMVAR_SETGET(SetWeaponEditor, WeaponEditor, LEDIT_WeaponEditor*, mypoWeaponEditor);
		MEMVAR_SETGET(SetScriptedItemEditor, ScriptedItemEditor, LEDIT_ScriptedItemEditor*, mypoScriptedItemEditor);
	//- [Editting] -
		void EditItemSet(LL_ItemSet* poSet);
		int  GetItemType();
		int  GetArmor(LL_ItemSet* poSet);
		int  GetWeapon(LL_ItemSet* poSet);
		int  GetScriptedItem(LL_ItemSet* poSet);
	
	protected:	
	//P- [Editting] -P
		void Setup(bool fEditing);
		bool EditOption(int i);
	//P- [Armors editting] -P
		void EditArmors();
		void SetupArmors(bool fEditing);
		bool EditArmorOption(int i);
		void NewArmor();
	//P- [Weapons editting] -P
		void EditWeapons();
		void SetupWeapons(bool fEditing);
		bool EditWeaponOption(int i);
		void NewWeapon();
	//P- [ScriptedItem set] -P
		void EditScriptedItems();
		void SetupScriptedItems(bool fEditing);
		bool EditScriptedItemOption(int i);
		void NewScriptedItem();
		
	//Vars
		LL_Game* mypoGame;
		LL_ItemSet* mypoSet;
		LEDIT_FileChooser* mypoFileChooser;
		LEDIT_ArmorEditor* mypoArmorEditor;
		LEDIT_WeaponEditor* mypoWeaponEditor;
		LEDIT_ScriptedItemEditor* mypoScriptedItemEditor;
};

#endif
