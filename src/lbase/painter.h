/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			painter.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/15/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: A painter basically is set up to include the routines of what to draw and how to draw it.
				 If for some reason there is a need to make some major changes to the L&L interface a lot
 				 of should be resolved in here. Also the painter can make changes to the interface through
  			 	 .gui files. Finally the painter includes a series of ASFC consoles, and the font palette
        		 that they use.
*/
#ifndef LL_PAINTER_H_
#define LL_PAINTER_H_

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Aggregates
	#include "border.h"
	#include <asfc/screen.h>
	#include <asfc/fontpalette.h>
	#include <asfc/console.h>
	#include <asfc/surface.h>
//Recognizes
	#include "game.h"
	#include "guimetrics.h"
//Dependencies
	#include <asfc/surface.h>

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class LL_Painter
{	public:
	//- [Construction] -
		LL_Painter();
	//- [GUI Files] -
		bool Load(string sFile);
	//- [Updating] -
		virtual void Draw();
		void DrawNarateConsole();
		void DrawUnitMap(ASFC_Matrix<bool>* plLight, bool fHighlight = false, bool fDrawSpawners = false);
		void DrawPlayerInfo(int iLocked, int iSelected);
		void DrawGemSpawners();
	//- [Prompting] -
		bool PromptYN(string sLine1, string sLine2, string sLine3, int iFont);
		bool PromptKey(SDLKey iKey1, SDLKey iKey2, string sLine1, string sLine2, string sLine3,
  					   int iFont);
		void DisplayMessage(string sLine1, string sLine2, string sLine3, int iFont);
	//- [Console Handelins'] -
		MEMVAR_GETREF(MainConsole,	ASFC_Console,	myoMainConsole);
		MEMVAR_GETREF(StatsConsole,	ASFC_Console,	myoStatsConsole);
		MEMVAR_GETREF(TalkConsole,	ASFC_Console,	myoTalkConsole);
		MEMVAR_GETREF(NarateConsole,ASFC_Console,   myoNarateConsole);
	//- [Cursor\Error Image Handeling] -
		MEMVAR_GETREF(Cursor, ASFC_Surface, myimgCursor);
		MEMVAR_GETREF(Error1, ASFC_Surface, myimgError1);
		MEMVAR_GETREF(Error2, ASFC_Surface, myimgError2);
	//- [Game Linking] -
		MEMVAR_SETGET(SetGame, Game, LL_Game*, mypoGame);
		MEMVAR_SETGET(SetScreen, Screen, ASFC_Screen*, myoScreen);
		MEMVAR_GETREF(FontPalette, ASFC_FontPalette, myoFontPalette);

	protected:
	//Const
		const static int CONSOLE_WIDTH = 80;
		const static int TIMER_DELAY = 300;
	
	//Vars
		ASFC_Timer			myoTimer;
		ASFC_Screen*		myoScreen;
		ASFC_Surface		myimgCursor;
		ASFC_Surface		myimgError1;
		ASFC_Surface		myimgError2;
		LL_Border 			myoBorder;
		ASFC_FontPalette	myoFontPalette;
		ASFC_Console		myoMainConsole;
		ASFC_Console		myoStatsConsole;
		ASFC_Console		myoTalkConsole;
		ASFC_Console		myoNarateConsole;
		LL_Game*			mypoGame;
		int					myiTransHighlight;
		bool				myfFlash;
};

#endif
