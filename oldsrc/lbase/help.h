/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			help.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: <Please Enter Here>
*/
#ifndef LL_HELP_H_
#define LL_HELP_H_

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Aggregates
	#include <textedit/text.h>
	#include <textedit/texteditor.h>
	#include "painter.h"
	#include <asfc/screen.h>
//Dependencies
	#include <lbase/painter.h>
	
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class LL_Help
{	public:
	//- [Construction] -
		LL_Help();
		void Setup(LL_Painter* poPainter, ASFC_Screen* poScreen);
	//- [Help] -
		void MapEditorHelp();
		void RunnerHelp();
	//- [Self Help] -
		void JotNotes(string sNotesFile);
		
	protected:
	//P- [Drawing] -P
		void DrawBackground();
		void DrawViewingInfo();
		void DrawJottingInfo();
	
	//Const
		#define LL_Help__MapEditorHelp "./data/docs/edit.txt"
		#define LL_Help__RunnerHelp "./data/docs/run.txt"
	//Vars
		LL_Painter*		mypoPainter;
		ASFC_Screen*		mypoScreen;
		TE_Text 		myoText;
		TE_TextEditor 	myoTextEditor;
};

#endif
