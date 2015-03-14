/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			tilematrixeditor.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	09/21/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: A tile matrix editor consists of a a matrix of animations (tiles) that can be
				 chosen from.
*/
#ifndef LEDIT_TILEMATRIXEDITOR_H_
#define LEDIT_TILEMATRIXEDITOR_H_

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Parent
	#include "editor.h"
//Aggregates
	#include <asfc/timer.h>
//Dependencies
	#include <asfc/utils.h>
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class LEDIT_TileMatrixEditor : public LEDIT_Editor
{	public:
	//Const
		//Options
			static const int CANCEL = -1;
			
	//- [Construction] -
		LEDIT_TileMatrixEditor();
	//- [Editting] -
		virtual int ChooseTile();

	protected:
	//P- [Drawing] -P
		void 		 Draw();
		virtual void DrawTile(int iX, int iY, int iTile);
	//P- [Editting] -P
		int GrabOption(int* piKey, ASFC_LinkedList<int> lChoosers);
		
	//Const
		//Timing
			static const int DELAY = 100;
		//Keys
			static const SDLKey KEY_CHOOSE		= SDLK_RETURN;
			static const SDLKey KEY_CHOOSE2		= SDLK_SPACE;
			static const SDLKey KEY_CANCEL		= SDLK_ESCAPE;
			static const SDLKey KEY_PREVIOUS	= SDLK_LEFT;
			static const SDLKey KEY_NEXT		= SDLK_RIGHT;
			static const SDLKey KEY_PREVIOUSROW	= SDLK_UP;
			static const SDLKey KEY_NEXTROW		= SDLK_DOWN;
	//Vars
		int myiNumTiles;
		int	myiSelected;
		int myiTopLeftTile;
		ASFC_Timer myoTimer;
		ASFC_Input myoInput;
};

#endif
