/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			classseteditor.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: <Please Enter Here>
*/
#ifndef LEDIT_CLASSSETEDITOR_H_
#define LEDIT_CLASSSETEDITOR_H_

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Parent
	#include "consoleeditor.h"
//Aggregates
	#include <textedit/text.h>
	#include <textedit/texteditor.h>
	#include "templatereader.h"
//Realizes
	#include "mapobjectremover.h"
	#include <lbase/looplib_lorelinker.h>
	#include <lbase/looplib_lore.h>

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class LEDIT_ClassSetEditor : public LEDIT_ConsoleEditor
{	public:
	//- [Constructors] -
		LEDIT_ClassSetEditor();
		MEMVAR_SETGET(SetMapObjectRemover, MapObjectRemover,LEDIT_MapObjectRemover*,mypoMapObjectRemover);
		MEMVAR_SETGET(SetLinker, Linker, LL_LOOPLib_LoreLinker*,	mypoLOOPLibLinker);
		MEMVAR_SETGET(SetLoreLib, LoreLib, LL_LOOPLib_Lore*, mypoLOOPLib);
	//- [Editting] -
		void 	EditClassSet(LL_Game* poGame, LL_ClassSet* poSet, string sClassFile, string sClassSetFile);
		string	GrabClass(LL_Game* poGame, LL_ClassSet* poSet);
	
	protected:
	//P- [Editting] -P
		void 	Setup(bool fNewOption);
		bool	EditOption(int iOpt, int iKey);
		void	HandleBoundries();
		void	MoveEntryTo(int iEntryNum, int iFirstLine);
		void	NewClass();
		void	DrawQuickKeys();
		void	DrawQuickKeysForClassEdit();
		void	CheckForErrors(int iClass);
		void	EditText(int iClass, int iLine = -1);

	//Const
		const static SDLKey KEY_DELETE = SDLK_DELETE;
		const static char   CLASS_TAG  = 'c';
		#define LEDIT_ClassSetEditor__CLASS_TEMPLATE "./data/templates/class.template"
	//Vars
		LL_Game*				mypoGame;
		LL_ClassSet*			mypoClassSet;
		LEDIT_MapObjectRemover*	mypoMapObjectRemover;
		TE_Text 				myoText;
		TE_TextEditor 			myoTextEditor;
		LEDIT_TemplateReader	myoTemplateReader;
		LL_LOOPLib_LoreLinker*	mypoLOOPLibLinker;
		LL_LOOPLib_Lore* 		mypoLOOPLib;
		string					mysClassFile;
		string					mysClassSetFile;
};

#endif
