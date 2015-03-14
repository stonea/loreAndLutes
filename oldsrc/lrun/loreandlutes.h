/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			loreandlutes.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Runner
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: Starts, and runs a game of Lore And Lutes
*/

#ifndef LRUN_LOREANDLUTES_H_
#define LRUN_LOREANDLUTES_H_
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Aggregates
	#include <lbase/painter.h>
	#include <lbase/game.h>
	#include <lbase/looplib_lore.h>
	#include <lbase/looplib_lorelinker.h>
	#include "shader.h"
	#include <lbase/zstats.h>
	#include <lbase/ready.h>
	#include "battle.h"
	#include "menu.h"
//Realizes
	#include <asfc/screen.h>
	#include <lbase/help.h>
//Dependencies
	#include <asfc/utils.h>
	#include <asfc/timer.h>
	#include <asfc/matrix.h>
	#include <asfc/effects.h>
	#include <time.h>
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class LRUN_LoreAndLutes
{	public:
	//- [Construction] -
		LRUN_LoreAndLutes(ASFC_Screen* poScreen);
		MEMVAR_SETGET(SetHelp, Help, LL_Help*, mypoHelp);
		void Init();
	//- [Game Handeling] -
		MEMVAR_GETREF(Game, LL_Game, myoGame);
		MEMVAR_GETREF(Painter, LL_Painter, myoPaint);
		MEMVAR_SETGET(SetScreen, Screen, ASFC_Screen*, mypoScreen);
		MEMVAR_GET(ReturnToStarter, bool, myfReturnToStarter);
		void LoadGame(string sFile, string sSaveGame);
		bool RunGame();
		void InitForNewMap();
 	
 	protected:
 	//P- [Game Handeling] -P
 		void Draw();
 		bool PlayerAlive();
	//- [EventProc] -
		void ProcessEvents();
 		void PerformEffect(	LL_BORDER_EFFECT iEffect, string sAddImage = "",
   							int iImageX = -1, int iImageY = -1);
           	
 	//Const
		#define LRUN_LoreAndLutes_GUI_PREFERENCE_FILE	"./data/gui/normal.gui"
		#define LRUN_LoreAndLutes_SHADES_FILE			"./data/loreandlutes.shade"
		#define LRUN_LoreAndLutes_MENU_FILE				"./data/gui/buttons/menu.buttons"
	 	static const int GAME_DELAY = 100;
	 	static const int ANIMATION_DELAY = 200;
	 	static const int SLEEP_DELAY = 15;
 	//Vars
 		//GUI
			LL_Painter 		myoPaint;
			ASFC_Screen*	mypoScreen;
			ASFC_Effects	myoEffects;
			ASFC_Input		myoInput;
		//Game Objects
			bool					myfViewAll;
			ASFC_LinkedList<int>	myiOnlyExecuteUnit;
	 		LL_Game 				myoGame;
	 		LL_LOOPLib_LoreLinker 	myoLOOPLibLinker;
	 		LL_LOOPLib_Lore 		myoLOOPLib;
	 		LRUN_Shader 			myoShader;
			LRUN_Menu				myoMenu;
	 		LL_ZStats				myoZStats;
			LL_Ready				myoReady;
			LRUN_Battle				myoBattle;
	 		ASFC_Timer myoAnimationTime;
	 		ASFC_Matrix<bool> lLight;
	 		ASFC_Matrix<bool> lFreeLight;
			LL_Help*				mypoHelp;
			bool myfReturnToStarter;
};
#endif
