/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			consoleeditor.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	09/20/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: A console editor contains a list of text. If the user presses a special selection key
				 such as space a value is returned representing a position within this list.
*/
#ifndef LEDIT_CONSOLEEDITOR_H_
#define LEDIT_CONSOLEEDITOR_H_

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Parent
	#include "editor.h"
//Aggregates
	#include <asfc/input.h>
	#include <asfc/timer.h>
	#include <vector.h>
	#include <asfc/linkedlist.h>

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class LEDIT_ConsoleEditor : public LEDIT_Editor
{	public:
	//Type
		//A LEDIT_CONSOLE_EDIT_TYPE value defines what type (heading, option, etc...) a piece of text is
			enum LEDIT_CONSOLE_EDIT_TYPE
			{	CONSOLE_EDIT_TYPE_HEADING = 0,
				CONSOLE_EDIT_TYPE_OPTION
			};
		//A console edit info object contains one piece of data that gets written to the console
			struct LEDIT_ConsoleEditInfo
			{	string 					s;		//The text of this piece of data
				LEDIT_CONSOLE_EDIT_TYPE	iType;	//The type of this piece o' data
			};

	//- [Constuctors] -
		LEDIT_ConsoleEditor();
  		void Reset(bool fResetCursor);	//Resets the state of the console editor
	//- [Writting] -
		void Heading(const string sHeading);	//Writes a heading (unselectable portion of text)
		void Option(const string sOption);		//Writes the option sOption
	//- [Editting] -
		int GrabOption();		//Sits waiting for a user to select an option, returns the selected option
		//Grabs an option and returns the key used to select it (within the list of choosers)
		int GrabOption(int* piKey, ASFC_LinkedList<int> lChoosers);
		int HandleMouse(int* piKey, ASFC_LinkedList<int> lChoosers);
		int NumOptions();			//Returns the # of options
		MEMVAR_SETGET(SetSelected, Selected, int, myiSelected);
		int 	GrabInt(string sText, int iMin, int iMax);
		int 	GrabIntWithoutAClear(string sText, int iMin, int iMax);
		string	GrabString(string sText);
		string	YesNo(bool f);
 	
 	protected:
 	//P- [Drawing] -P
 		void DrawInit();
 		void Draw();
 		virtual void DrawQuickKeys();
 	
 	//Vars
 		//Input objects
 			ASFC_Input myoInput;
			ASFC_Timer myoTimer;
		//Edit info
	 		int myiSelected;					//Currently selected option
	 		int myiNumOptions;					//The # o' options
 			vector<LEDIT_ConsoleEditInfo> myoInfo;	//All the information that gets writtten onto this console
	//Const
		//Keys
			static const SDLKey KEY_CHOOSE 	 =  SDLK_RETURN;
			static const SDLKey KEY_CHOOSE2	 =  SDLK_SPACE;
			static const SDLKey KEY_CANCEL	 =	SDLK_ESCAPE;
			static const SDLKey KEY_PREVIOUS =	SDLK_UP;
			static const SDLKey KEY_NEXT	 =	SDLK_DOWN;
			static const SDLKey KEY_PG_UP	 =	SDLK_PAGEUP;
			static const SDLKey KEY_PG_DN	 =	SDLK_PAGEDOWN;
		//Timing
			static const int DELAY = 75;	//Delay between choosing thingies
		//Console info
			static const int NO_LINK = -1;
};

#endif
