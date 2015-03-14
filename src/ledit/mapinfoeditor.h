/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			mapinfoeditor.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: <Please Enter Here>
*/
#ifndef LEDIT_MAPINFOEDITOR_H_
#define LEDIT_MAPINFOEDITOR_H_

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Parent
	#include "consoleeditor.h"
//Realizes
	#include <lbase/game.h>
	#include "filechooser.h"
	#include <lbase/terrainmap.h>
	#include <lbase/mapset.h>
	#include "mapseteditor.h"

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class LEDIT_MapInfoEditor : public LEDIT_ConsoleEditor
{	public:
	//- [Construction] -
		LEDIT_MapInfoEditor();
	//- [Editting] -
		MEMVAR_SETGET(SetGame, Game, LL_Game*, mypoGame);
		MEMVAR_SETGET(SetFileChooser, FileChooser, LEDIT_FileChooser*, mypoFileChooser);
		MEMVAR_SETGET(SetMapSet, MapSet, LL_MapSet*, mypoMapSet);
		MEMVAR_SETGET(SetMapSetEdit, MapSetEdit, LEDIT_MapSetEditor*, mypoMapSetEdit);
		void EditMap(LL_TerrainMap* poMap);
	
	protected:	
	//P- [Editting] -P
		void 	Setup();
		bool	EditOption(int i);
		string	Effect(LL_BORDER_EFFECT i);
		string	WarpType(LL_BORDER_WARP_TYPE i);

	//Type
		enum EDITOPTIONS
		{	EDITOPTION_DESCRIPTION = 0,
			EDITOPTION_MUSIC_FILE,
			EDITOPTION_TERRAIN_SET,
			EDITOPTION_TICKS_PER_MINUTE,
			EDITOPTION_MAP_TYPE,
			EDITOPTION_PLAYER_X,
			EDITOPTION_PLAYER_Y,
			EDITOPTION_MAX_MONSTERS,
			EDITOPTION_CHANCE_MONSTERS,
			EDITOPTION_MAPNORTH,
			EDITOPTION_NORTH_BORDER,
			EDITOPTION_NORTH_WARP,
			EDITOPTION_NORTH_EFFECT,
			EDITOPTION_MAPSOUTH,
			EDITOPTION_SOUTH_BORDER,
			EDITOPTION_SOUTH_WARP,
			EDITOPTION_SOUTH_EFFECT,
			EDITOPTION_MAPWEST,
			EDITOPTION_WEST_BORDER,
			EDITOPTION_WEST_WARP,
			EDITOPTION_WEST_EFFECT,
			EDITOPTION_MAPEAST,
			EDITOPTION_EAST_BORDER,
			EDITOPTION_EAST_WARP,
			EDITOPTION_EAST_EFFECT,
			EDITOPTION_NUM_OPTIONS
		};
	//Vars
		LL_Game*			mypoGame;
		LEDIT_FileChooser*	mypoFileChooser;
		LL_TerrainMap* 		mypoMap;
		LL_MapSet*	   		mypoMapSet;
		LEDIT_MapSetEditor*	mypoMapSetEdit;
};

#endif
