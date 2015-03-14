/*	Protected under the GNU General Public License read and see copying.txt for details
	ANNEX SOLUTIONS
	By: Andy Stone

	File for: TE_TextEditor
*/

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Multiple inclusion protection:
	#ifndef TEXTEDITOR_H_
	#define TEXTEDITOR_H_
	
//Depends on:
	#include "text.h"
	#include <asfc/utils.h>
	
//Agregates
	#include <asfc/input.h>
	#include <asfc/timer.h>

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												TE_TextEditor
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class TE_TextEditor
{	public:
	//- [Constuctors] -
 		TE_TextEditor();
 		void SetConsole(ASFC_Console* pConsole);
 		void SetDefaults();
 		
	//- [Text Editting] -
		void EditText(TE_Text* poTextToEdit);
		void EditText(TE_Text* poTextToEdit, int* piProtectedMinRow, int* piProtectedMaxRow);
		void EditText(TE_Text* poTextToEdit, int* piProtectedMinRow, int* piProtectedMaxRow, int iCur);
		void ViewText(TE_Text* poTextToEdit);
 	
 	protected:
 	//P- [Updating] -P
 		void EditText();
 		void UpdateTextEdit();
 		void UpdateTextViewer();
 		void DrawText();
 		void DrawCursor();
 		void HandleKeys();
 		void HandleMouse();
 		void HandleViewingKeys();
 		void MoveDownARow();
 		void MoveUpARow();
 		void CheckCursorPosition();
 		void AddRow();
 		void DeleteRow();
 		int	 NumUnprotectedRows();
 		
	//P- [Debugging] -P
		bool EditorReady();
		
	//Types
		enum myeState
		{	STATE_GOOD,
			STATE_EXIT
		};
 	
 	//Vars
 		TE_Text* 		mypoText;
		ASFC_Console*	mypoConsole;
		bool			myfConsoleSet;
		int				myiRowAtTopOfScreen;
		int				myiProtectedMin;
		int				myiProtectedMax;
		bool			myfProtectData;
		bool			myfShiftDown;
		myeState		myiState;
		ASFC_Input		myoInput;
		int				myiFont;
		ASFC_Timer		myoTimer;
	//Const
		//Keys
			static const SDLKey KEY_EXIT 	= SDLK_ESCAPE;
			static const SDLKey KEY_LEFT 	= SDLK_LEFT;
			static const SDLKey KEY_RIGHT 	= SDLK_RIGHT;
			static const SDLKey KEY_UP		= SDLK_UP;
			static const SDLKey KEY_DOWN	= SDLK_DOWN;
			static const SDLKey KEY_DELETE	= SDLK_DELETE;
			static const SDLKey KEY_BACKSPACE= SDLK_BACKSPACE;
			static const SDLKey KEY_HOME	 = SDLK_HOME;
			static const SDLKey KEY_END		 = SDLK_END;
			static const SDLKey KEY_PAGEUP	 = SDLK_PAGEUP;
			static const SDLKey KEY_PAGEDOWN = SDLK_PAGEDOWN;
			static const SDLKey KEY_NEWROW 	 = SDLK_RETURN;
			static const SDLKey KEY_TYPEABLE1= SDLK_SPACE;
			static const SDLKey KEY_TYPEABLE2= SDLK_z;
			static const SDLKey KEY_REMOVEROW= SDLK_y;
		//Timing
			static const int SHIFT_DELAY = 5;	//Milliseconds shift free before we recognize it as so
};

//Now ending texteditor.h
	#endif
