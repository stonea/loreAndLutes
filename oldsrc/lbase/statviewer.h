/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			statviewer.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Runner
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: <Please Enter Here>
*/
#ifndef LL_STATVIEWER_H_
#define LL_STATVIEWER_H_

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Dependencies
	#include <asfc/linkedlist.h>
//Aggregates
	#include <asfc/input.h>
//Realizes
	#include <asfc/screen.h>
	#include "painter.h"

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class LL_StatViewer
{	public:
	//Const
		static const int OPTION_EXIT = -1;
		static const int OPTION_NEXT_SCREEN = -2;
		static const int OPTION_PREV_SCREEN = -3;

	//- [Construction] -
		LL_StatViewer();
		MEMVAR_SETGET(SetPainter, Painter, LL_Painter*, mypoPainter);	
		MEMVAR_SETGET(SetScreen, Screen, ASFC_Screen*, mypoScreen);
	//- [Grab key] -
		int GrabOption();
		
	protected:
	//P- [Display] -P
		void Draw();
		SDLKey GrabKey();
		void ProcessKey(SDLKey iKey);
		
	//Const
		static const SDLKey KEY_EXIT		= SDLK_ESCAPE;
		static const SDLKey KEY_PREV		= SDLK_UP;
		static const SDLKey KEY_NEXT		= SDLK_DOWN;
		static const SDLKey KEY_PREV_SCREEN	= SDLK_LEFT;
		static const SDLKey KEY_NEXT_SCREEN	= SDLK_RIGHT;
		static const SDLKey KEY_CHOOSE 	 	=  SDLK_RETURN;
		static const SDLKey KEY_CHOOSE2		=  SDLK_SPACE;
		//Timing
			static const int DELAY = 100;	//Delay between choosing thingies
	
	//Vars
		LL_Painter* mypoPainter;
		ASFC_Screen* mypoScreen;
		ASFC_LinkedList<string> mylEntries;
		ASFC_Input myoInput;
		ASFC_Timer myoTimer;
		int myiLine;
		int myiOption;
		bool myfDone;
		bool myfScreenLock;
		bool myfDrawCursor;
		int myiFirstSelectableLine;
};

#endif
