/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			terraineditor.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: <Please Enter Here>
*/
#ifndef LEDIT_TERRAINEDITOR_H_
#define LEDIT_TERRAINEDITOR_H_

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Parent
	#include "consoleeditor.h"
//Realizes
	#include <lbase/terrain.h>
	#include "mobilityeditor.h"
	#include "filechooser.h"
	#include "vehicleseteditor.h"
//Dependencies
	#include <asfc/utils.h>

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class LEDIT_TerrainEditor : public LEDIT_ConsoleEditor
{	public:
	//- [Construction] -
		LEDIT_TerrainEditor();
	//- [Editting] -
		MEMVAR_SETGET(SetMobilityTerrainMap, MobilityTerrainMap, LL_MobilityTerrainMap*, mypoMobilityTerrainMap);
		MEMVAR_SETGET(SetMobilityEditor, MobilityEditor, LEDIT_MobilityEditor*, mypoMobilityEditor);
		MEMVAR_SETGET(SetFileChooser,	 FileChooser,	 	 LEDIT_FileChooser*,		mypoFileChooser);
		MEMVAR_SETGET(SetVehicleSetEditor, 		SetVehicleSetEditor,
					  LEDIT_VehicleSetEditor*,	mypoVehicleSetEditor);
		void EditTerrain(LL_Terrain* poTerrain, LL_Game* poGame);
		
	protected:
	//P- [Editting] -P
		void 	Setup();
		void	MobilityOptions();
		bool	EditOption(int i);
		string	LightEffect(LL_LIGHTEFFECT i);

	//Const
		//Type
		enum EDITOPTIONS
		{	EDITOPTION_IMAGE		= 0,
			EDITOPTION_CUSTOM_IMAGE,
			EDITOPTION_EDITIMAGE,
			EDITOPTION_COLORRED,
			EDITOPTION_COLORGREEN,
			EDITOPTION_COLORBLUE,
			EDITOPTION_LIGHT,
			EDITOPTION_BATTLE_MAP,
			EDITOPTION_GROUP,
			EDITOPTION_DESCRIPTION
		};
	//Vars
		LL_Game* 				mypoGame;
		LL_Terrain* 			mypoTerrain;
		LL_MobilityTerrainMap*	mypoMobilityTerrainMap;
		LEDIT_MobilityEditor*	mypoMobilityEditor;
		LEDIT_FileChooser*		mypoFileChooser;
		LEDIT_VehicleSetEditor*	mypoVehicleSetEditor;
};

#endif
