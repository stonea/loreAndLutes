/* Protected under the GNU General Public License read and see copying.txt For details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			routeeditor.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: <Please Enter Here>
*/
#ifndef LEDIT_ROUTEEDITOR_H_
#define LEDIT_ROUTEEDITOR_H_

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Parent
	#include "editor.h"
//Aggregates
	#include <asfc/input.h>
	#include <asfc/timer.h>
	#include <lbase/route.h>
//Dependencies
	#include <lbase/aistructures.h>
	#include <lbase/game.h>

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class LEDIT_RouteEditor : public LEDIT_Editor
{	public:
	//- [Construction] -
		LEDIT_RouteEditor(LL_Game* poGame);
	//- [Editting routes] -
		void EditRoute(LL_Game*	poGame, int iStartX, int iStartY);
	//- [Drawing] -
		void DrawRoute(int iCurX, int iCurY);
		void DrawGemViewRoute();
	
	protected:
	//P- [Editting] -P
		SDLKey GrabKey();
		void HandleKey(SDLKey iKey);
	//P- [Drawing] -P
		void Draw();
		void DrawGemViewCursor();
		void MoveViewports();
		void DrawQuickKeys();
	//Const
		#define LEDIT_RouteEditor__IMAGE_ARROW_NORTH "./data/gui/editor/arrown.png"
		#define LEDIT_RouteEditor__IMAGE_ARROW_SOUTH "./data/gui/editor/arrows.png"
		#define LEDIT_RouteEditor__IMAGE_ARROW_WEST  "./data/gui/editor/arroww.png"
		#define LEDIT_RouteEditor__IMAGE_ARROW_EAST  "./data/gui/editor/arrowe.png"
		static const int CURSOR_BLINK_RATE = 100;
		static const SDLKey KEY_EXIT			= SDLK_ESCAPE;
		static const SDLKey KEY_EXIT2			= SDLK_SPACE;
		static const SDLKey KEY_EXIT3			= SDLK_RETURN;
		static const SDLKey KEY_EXIT4			= SDLK_l;
		static const SDLKey KEY_MOVECUR_NORTH	= SDLK_UP;
		static const SDLKey KEY_MOVECUR_NORTH2	= SDLK_KP8;
		static const SDLKey KEY_MOVECUR_SOUTH	= SDLK_DOWN;
		static const SDLKey KEY_MOVECUR_SOUTH2	= SDLK_KP2;
		static const SDLKey KEY_MOVECUR_WEST	= SDLK_LEFT;
		static const SDLKey KEY_MOVECUR_WEST2	= SDLK_KP4;
		static const SDLKey KEY_MOVECUR_EAST	= SDLK_RIGHT;
		static const SDLKey KEY_MOVECUR_EAST2	= SDLK_KP6;
		static const SDLKey KEY_GEM_VIEW		= SDLK_g;
	//Vars
		int			myiCurX, myiCurY;
		bool		myfCursorBlink;
		bool		myfEditting;
		bool		myfGemView;
		LL_Game* 	mypoGame;
		ASFC_Input	myoInput;
		ASFC_Timer	myoCursorBlinkTimer;
		LL_PathNodes*	mypoPathNodes;
		LL_Route*		mypoRoute;
		ASFC_Surface myimgArrowN, myimgArrowS, myimgArrowW, myimgArrowE;
		ASFC_Matrix<bool> mylNoLight;
		LL_Node* mypStartNode; 
  		LL_Node* mypEndNode;
		int myiStartNode, myiEndNode;
};

#endif
