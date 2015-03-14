/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			monstereditor.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: <Please Enter Here>
*/
#ifndef LEDIT_MONSTEREDITOR_H_
#define LEDIT_MONSTEREDITOR_H_

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Parent
	#include "consoleeditor.h"
//Realizes
	#include <lbase/monstertemplate.h>
	#include "vehicleseteditor.h"
	#include "filechooser.h"
	#include "itemseteditor.h"
	#include "chesteditor.h"
	#include "friendeditor.h"

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class LEDIT_MonsterEditor : public LEDIT_ConsoleEditor
{	public:
	//- [Construction] -
		LEDIT_MonsterEditor();
		MEMVAR_SETGET(SetVehicleSetEditor, VehicleSetEditor, LEDIT_VehicleSetEditor*, mypoVehicleSetEditor);
		MEMVAR_SETGET(SetFileChooser,	   FileChooser,	 	 LEDIT_FileChooser*,	  mypoFileChooser);
		MEMVAR_SETGET(SetItemSetEditor,	   ItemSetEditor,	 LEDIT_ItemSetEditor*,	  mypoItemSetEditor);
		MEMVAR_SETGET(SetChestEditor,	   ChestEditor,		 LEDIT_ChestEditor*,	  mypoChestEditor);
		MEMVAR_SETGET(SetFriendEditor,	   FriendEditor,	 LEDIT_FriendEditor*,	  mypoFriendEditor);
	//- [Editting] -
		void EditMonster(LL_MonsterTemplate* poMonster, LL_Game* poGame);
	
	protected:
	//P- [Editting] -P
		void Setup();
		bool EditOption(int i);
	//P- [Strategy ditting] -P
		void EditStrategies();
		void DrawStrategyQuickKeys();
		void SetupStrategies();
		bool EditStrategy(int i, int iKey);
	
	//Type
		enum EDITOPTIONS
		{	EDITOPTION_NAME = 0,
			EDITOPTION_IMAGE,
			EDITOPTION_CUSTOM_IMAGE,
			EDITOPTION_STRENGTH,
			EDITOPTION_DEXTERITY,
			EDITOPTION_INTELLIGENCE,
			EDITOPTION_MP,
			EDITOPTION_HP,
			EDITOPTION_EXPERIENCE,
			EDITOPTION_RARITY,
			EDITOPTION_VEHICLE,
			EDITOPTION_WEAPON1,
			EDITOPTION_WEAPON2,
			EDITOPTION_ARMOR1,
			EDITOPTION_ARMOR2,
			EDITOPTION_STRATEGIES,
			EDITOPTION_PARTSIZE_MIN,
			EDITOPTION_PARTSIZE_MAX,
			EDITOPTION_FRIENDS,
			EDITOPTION_CHEST_CHANCE,
			EDITOPTION_FOOD_CHANCE,
			EDITOPTION_MAX_FOOD,
			EDITOPTION_DEATH_CHEST,
			EDITOPTION_NUM_OPTIONS
		};
	//Const
		const static SDLKey KEY_DELETE = SDLK_DELETE;
	//Vars
		LL_MonsterTemplate* mypoMonster;
		LL_Game* 	mypoGame;
		LEDIT_FileChooser*		mypoFileChooser;
		LEDIT_VehicleSetEditor*	mypoVehicleSetEditor;
		LEDIT_ItemSetEditor*	mypoItemSetEditor;
		LEDIT_ChestEditor*		mypoChestEditor;
		LEDIT_FriendEditor*		mypoFriendEditor;
};

#endif
