/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			locationpicker.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: <Please Enter Here>
*/
#ifndef LEDIT_LOCATIONPICKER_H_
#define LEDIT_LOCATIONPICKER_H_

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Parent
	#include "editor.h"
//Realizes
	#include <lbase/game.h>
	#include "routeeditor.h"
//Aggregates
	#include <asfc/input.h>
	#include <asfc/timer.h>

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class LEDIT_LocationPicker : public LEDIT_Editor
{	public:
	//- [Construction] -
		LEDIT_LocationPicker();
		MEMVAR_SETGET(SetGame, Game, LL_Game*, mypoGame);
		MEMVAR_SETGET(SetRouteEditor, RouteEditor, LEDIT_RouteEditor*,  mypoRouteEditor);
	//- [Picking] -
		void PickPoint(int* piX, int* piY);
		void SetStartLocation(int iX, int iY);

	protected:
	//P- [Picking] -P
		void Update();
		SDLKey GetKey(SDLKey* piMod);
		void HandleKey(SDLKey iKey, SDLKey iMod);
		void Draw();
		void MoveViewports(ASFC_DIRECTION iDir);
		void MoveViewportsTo(int iX, int iY);
		void MoveScreen(ASFC_DIRECTION iDir);
		void DrawStats();
		void DrawQuickKeys();
		int  CursorX();
		int  CursorY();
		
	//vars
		LL_Game* mypoGame;
		LEDIT_RouteEditor* mypoRouteEditor;
		ASFC_Matrix<bool> lNoLight;
		ASFC_Input		myoInput;
		ASFC_Timer		myoTimer;
		bool			myfExit;
	//Const
		//Mods
			static const SDLKey MOD_NONE			= SDLKey(int(-1));
			static const SDLKey MOD_CTRL			= SDLK_LCTRL;
  		//NoMod + 
			static const SDLKey KEY_EXIT			= SDLK_ESCAPE;
			static const SDLKey KEY_MOVECUR_NORTH	= SDLK_UP;
			static const SDLKey KEY_MOVECUR_NORTH2	= SDLK_KP8;
			static const SDLKey KEY_MOVECUR_SOUTH	= SDLK_DOWN;
			static const SDLKey KEY_MOVECUR_SOUTH2	= SDLK_KP2;
			static const SDLKey KEY_MOVECUR_WEST	= SDLK_LEFT;
			static const SDLKey KEY_MOVECUR_WEST2	= SDLK_KP4;
			static const SDLKey KEY_MOVECUR_EAST	= SDLK_RIGHT;
			static const SDLKey KEY_MOVECUR_EAST2	= SDLK_KP6;
			static const SDLKey KEY_MOVECUR_NRTHWST	= SDLK_KP7;
			static const SDLKey KEY_MOVECUR_NRTHEST	= SDLK_KP9;
			static const SDLKey KEY_MOVECUR_STHWST	= SDLK_KP1;
			static const SDLKey KEY_MOVECUR_STHEST	= SDLK_KP3;
			static const SDLKey KEY_PICK			= SDLK_SPACE;
			static const SDLKey KEY_PICK2			= SDLK_RETURN;
		//Control + 
			static const SDLKey KEY_MOVESCRN_NORTH	= SDLK_UP;
			static const SDLKey KEY_MOVESCRN_NORTH2	= SDLK_KP8;
			static const SDLKey KEY_MOVESCRN_SOUTH	= SDLK_DOWN;
			static const SDLKey KEY_MOVESCRN_SOUTH2	= SDLK_KP2;
			static const SDLKey KEY_MOVESCRN_WEST	= SDLK_LEFT;
			static const SDLKey KEY_MOVESCRN_WEST2	= SDLK_KP4;
			static const SDLKey KEY_MOVESCRN_EAST	= SDLK_RIGHT;
			static const SDLKey KEY_MOVESCRN_EAST2	= SDLK_KP6;
			static const SDLKey KEY_MOVESCRN_NRTHWST= SDLK_KP7;
			static const SDLKey KEY_MOVESCRN_NRTHEST= SDLK_KP9;
			static const SDLKey KEY_MOVESCRN_STHWST	= SDLK_KP1;
			static const SDLKey KEY_MOVESCRN_STHEST	= SDLK_KP3;
};

#endif
