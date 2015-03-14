/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			scripteduniteditor.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: <Please Enter Here> 
*/
#ifndef LEDIT_SCRIPTEDUNITEDITOR_H_
#define LEDIT_SCRIPTEDUNITEDITOR_H_

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Parent
	#include "consoleeditor.h"
//Aggregates
	#include <textedit/texteditor.h>
	#include <textedit/text.h>
//Realizes
	#include <lbase/scriptedunit.h>
	#include "filechooser.h"
	#include "classseteditor.h"
	#include <lbase/looplib_lorelinker.h>
	#include <lbase/looplib_lore.h>
	#include "dailyroutineeditor.h"

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class LEDIT_ScriptedUnitEditor : public LEDIT_ConsoleEditor
{	public:
	//- [Construction] -
		LEDIT_ScriptedUnitEditor();
		MEMVAR_SETGET(SetFileChooser, FileChooser, LEDIT_FileChooser*, mypoFileChooser);
		MEMVAR_SETGET(SetClassSetEditor, ClassSetEditor, LEDIT_ClassSetEditor*, mypoClassSetEditor);
		MEMVAR_SETGET(SetLinker, Linker, LL_LOOPLib_LoreLinker*,	mypoLOOPLibLinker);
		MEMVAR_SETGET(SetLoreLib, LoreLib, LL_LOOPLib_Lore*, mypoLOOPLib);
		MEMVAR_SETGET(SetDailyRoutineEditor, DailyRoutineEditor, LEDIT_DailyRoutineEditor*, mypoDailyRoutineEditor);
	//- [Editting] -
		void EditScriptedUnit(LL_ScriptedUnit* poUnit, LL_Game* poGame);
		
	protected:
	//Type
		enum LEDIT_SCRIPT_EDIT_OPTION
		{	LEDIT_SCRIPT_EDIT_OPTION_IDENTIFIER = 0,
			LEDIT_SCRIPT_EDIT_OPTION_IMAGE,
			LEDIT_SCRIPT_EDIT_OPTION_CUSTOM_IMAGE,
			LEDIT_SCRIPT_EDIT_OPTION_EDIT_IMAGE,
			LEDIT_SCRIPT_EDIT_OPTION_EDIT_ROUTE,
			LEDIT_SCRIPT_EDIT_OPTION_VAR
		};
	//P- [Editting] -P
		void 	Setup();
		bool	EditOption(int iOpt);
		void	PromptForVar(string sIdentifier, double dValue);
		void	EditIdentifier();
		
	//Vars
		LL_ScriptedUnit* 	mypoScriptedUnit;
		LL_Game*		 	mypoGame;
		LEDIT_DailyRoutineEditor* mypoDailyRoutineEditor;
		LL_ClassSet*	 	mypoClassSet;
		LL_ClassSet*		mypoClassSet2;
		LOOP_Class*		 	mypoClass;
		LEDIT_FileChooser*	mypoFileChooser;
		LEDIT_ClassSetEditor*	mypoClassSetEditor;
		LL_LOOPLib_LoreLinker*	mypoLOOPLibLinker;
		LL_LOOPLib_Lore* 		mypoLOOPLib;
		int				 	myiLocalInClassSet;
		TE_Text 			myoText;
		TE_TextEditor 		myoTextEditor;
		bool				myfLocalClass;
};

#endif
