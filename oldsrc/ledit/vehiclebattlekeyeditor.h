/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			vehiclebattlekeyeditor.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: <Please Enter Here>
*/
#ifndef LEDIT_VEHICLEBATTLEKEYEDITOR_H_
#define LEDIT_VEHICLEBATTLEKEYEDITOR_H_

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Parent
	#include "consoleeditor.h"
//Realizes
	#include <lbase/mobilityterrainmap.h>
	#include "vehicleseteditor.h"

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class LEDIT_VehicleBattleKeyEditor : public LEDIT_ConsoleEditor
{	public:
	//- [Construction] -
		LEDIT_VehicleBattleKeyEditor();
		MEMVAR_SETGET(SetMobilityTerrainMap, MobilityTerrainMap, LL_MobilityTerrainMap*, mypoMobilityTerrainMap);
		MEMVAR_SETGET(SetVehicleSet, VehicleSet, LL_VehicleSet*, mypoSet);
		MEMVAR_SETGET(SetVehicleSetEditor, VehicleSetEditor, LEDIT_VehicleSetEditor*, mypoVehicleSetEditor);
	//- [Editting] -
		void EditVehicleBattleKeys();
	
	protected:	
	//P- [Editting] -P
		void	DrawQuickKeys();
		void 	Setup();
		bool	EditOption(int iOpt, int iKey);
	//P- [Editting Key] -P
		void	EditKey(int iKey);
		void	DrawKeyQuickKeys();
		void 	SetupKey();
		bool	EditKeyOption(int iOpt);

	//Const
		const static SDLKey KEY_DELETE = SDLK_DELETE;
	//Type
		enum LEDIT_Option
		{	OPTION_VEHICLE1 = 0,
			OPTION_VEHICLE2,
			OPTION_MAP
		};
	//Vars
		LL_MobilityTerrainMap* mypoMobilityTerrainMap;
		LL_MobilityTerrainMap::LL_VehicleBattleKey* mypoKey;
		LL_VehicleSet* mypoSet;
		LEDIT_VehicleSetEditor* mypoVehicleSetEditor;
};

#endif
