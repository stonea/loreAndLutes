/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			starter.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Starter
   | ----` |	Last Updated:	
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: 
*/
#ifndef LSTART_STARTER_H_
#define LSTART_STARTER_H_

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Aggregates
	#include <asfc/input.h>
	#include <ledit/leditstart.h>
	#include <lrun/lrunstart.h>
	#include <asfc/surface.h>
	#include "descriptionviewer.h"
	#include "gameslist.h"
	#include "gamemaker.h"
//Dependencies
	#include <asfc/screen.h>

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class LSTART_Starter
{	public:
	//- [Constructor] -
		LSTART_Starter(ASFC_Screen* poScreen);
	//- [Starter] -
		void Run();

	protected:
	//P- [Starter] -P
		void CheckKeys();
		void Draw();
		int  HandleMouse();
		
	//Type
		enum START_STATE
		{	STATE_NOTHING = 0,
			STATE_PLAY,
			STATE_EDIT,
			STATE_NEW,
			STATE_EXIT,
			STATE_NUM_STATES
		};
	//Const
		static const SDLKey KEY_PLAY  = SDLK_p;
		static const SDLKey KEY_EDIT  = SDLK_e;
		static const SDLKey KEY_QUIT  = SDLK_q;
		static const SDLKey KEY_QUIT2 = SDLK_ESCAPE;
		static const SDLKey KEY_NEW   = SDLK_n;
		static const SDLKey KEY_PREV  = SDLK_UP;
		static const SDLKey KEY_NEXT  = SDLK_DOWN;
		static const int GAMES_MENU_X  = 20;
		static const int GAMES_MENU_Y  = 106;
		static const int GAMES_MENU_W  = 16;
		static const int GAMES_MENU_H  = 18;
		static const int LOGO_X        = 364;
		static const int LOGO_Y        = 21;
		static const int DESCRIPTION_X = 364;
		static const int DESCRIPTION_Y = 106;		
		static const int DESCRIPTION_W = 32;
		static const int DESCRIPTION_H = 18;
	//Vars
		START_STATE myiState;
		ASFC_Screen* mypoScreen;
		ASFC_Input myoInput;
		LEDIT_LEditStart myoEditor;
		LRUN_LRunStart myoRunner;
		ASFC_Surface myimgBackground;
		ASFC_Surface myimgLogo;
		LSTART_DescriptionViewer myoDescriptionViewer;
		LSTART_GamesList myoGamesList;
		string mysGame;
		ofstream out;
		ASFC_Console myoConsole;
		ASFC_Font 		myoConFont;
		ASFC_FontPalette myoFonts;
		LSTART_GameMaker myoGameMaker;
};

#endif
