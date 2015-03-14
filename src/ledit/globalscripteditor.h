/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			globalscripteditor.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: <Please Enter Here>
*/
#ifndef LEDIT_GLOBALSCRIPTEDITOR_H_
#define LEDIT_GLOBALSCRIPTEDITOR_H_

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Parent
	#include "consoleeditor.h"
//Aggregates
	#include <textedit/text.h>
	#include <textedit/texteditor.h>
//Realizes
	#include <lbase/looplib_lorelinker.h>
	#include <lbase/looplib_lore.h>

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class LEDIT_GlobalScriptEditor : public LEDIT_ConsoleEditor
{	public:
	//- [Constructors] -
		LEDIT_GlobalScriptEditor();
		void Setup(LL_Painter* poPainter);
		MEMVAR_SETGET(SetLinker, Linker, LL_LOOPLib_LoreLinker*,	mypoLOOPLibLinker);
		MEMVAR_SETGET(SetLoreLib, LoreLib, LL_LOOPLib_Lore*, mypoLOOPLib);
	//- [Editting] -
		void EditGlobalScript(LL_Game* poGame, string sClassFile);
	
	protected:	
	//P- [Editting] -P
		void EditText(int iLine = -1);
		void CheckForErrors();
		
	//Vars
		LL_Game*				mypoGame;
		TE_Text 				myoText;
		TE_TextEditor 			myoTextEditor;
		LL_LOOPLib_LoreLinker*	mypoLOOPLibLinker;
		LL_LOOPLib_Lore* 		mypoLOOPLib;
		string					mysClassFile;
};

#endif
