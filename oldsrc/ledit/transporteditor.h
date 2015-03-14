/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			transporteditor.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: <Please Enter Here>
*/
#ifndef LEDIT_TRANSPORTEDITOR_H_
#define LEDIT_TRANSPORTEDITOR_H_

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Parent
	#include "consoleeditor.h"
//Realizes
	#include <lbase/game.h>
	#include "filechooser.h"
	#include "mapseteditor.h"

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class LEDIT_TransportEditor : public LEDIT_ConsoleEditor
{	public:
	//- [Construction] -
		LEDIT_TransportEditor();
		MEMVAR_SETGET(SetGame, Game, LL_Game*, mypoGame);
		MEMVAR_SETGET(SetMapSetEdit, MapSetEdit, LEDIT_MapSetEditor*, mypoMapSetEdit);
		MEMVAR_SETGET(SetFileChooser, FileChooser, LEDIT_FileChooser*, mypoFileChooser);
		void EditTransport(LL_Transport* poTransport);
		
	protected:
	//P- [Editting] -P
		void Setup();
		bool EditOption(int i);
		string YesNo(bool f);
		string Effect(LL_BORDER_EFFECT i);

	//Type
		enum LEDIT_Options
		{	OPTION_IMAGE = 0,
			OPTION_CUSTOM_IMAGE,
			OPTION_EDIT_IMAGE,
			OPTION_MAP,
			OPTION_TRANSPORTX,
			OPTION_TRANSPORTY,
			OPTION_EFFECT,
			OPTION_TRANSPORT_IF_PLAYERON,
			OPTION_TRANSPORT_IF_TALK,
			OPTION_TRANSPORT_IF_LOOK,
			OPTION_TRANSPORT_IF_PUSH,
			OPTION_TRANSPORT_IF_SEARCH,
			OPTION_TRANSPORT_IF_ATTACK,
		    OPTION_NUM_OPTIONS
		};

	//Vars
		LL_Game* mypoGame;
		LEDIT_FileChooser* mypoFileChooser;
		LEDIT_MapSetEditor*	mypoMapSetEdit;
		LL_Transport* mypoTransport;
};

#endif
