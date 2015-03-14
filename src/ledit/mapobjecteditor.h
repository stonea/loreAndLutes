/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			mapobjecteditor.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: <Please Enter Here>
*/
#ifndef LEDIT_MAPOBJECTEDITOR_H_
#define LEDIT_MAPOBJECTEDITOR_H_

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Parent
	#include "editor.h"
//Realizes
	#include <lbase/game.h>
	#include "classseteditor.h"
	#include "filechooser.h"
	
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class LEDIT_MapObjectEditor : public LEDIT_Editor
{	public:
	//- [Construction] -
		LEDIT_MapObjectEditor();
		MEMVAR_SETGET(SetFileChooser, FileChooser, LEDIT_FileChooser*, mypoFileChooser);
	//- [Plotting] -
		void PlotNewInstance(LL_Game* poGame, LEDIT_ClassSetEditor* poClassSetEditor, int iX, int iY,
  							 int iLayer);
		void PlotCopyInstance(LL_Game* poGame, LEDIT_ClassSetEditor* poClassSetEditor, int iCX, int iCY,
							  int iX, int iY, int iL);
		void PlotTemplateInstance(LL_Game* poGame, LEDIT_ClassSetEditor* poClassSetEditor, int iX, int iY,
  							 	  int iLayer, string sTemplateClass, string sBaseName, string sImageFile);
		void PlotArmor(LL_Game* poGame, int iNum, int iX, int iY, int iL);
		void PlotWeapon(LL_Game* poGame, int iNum, int iX, int iY, int iL);
		void PlotScriptedItem(LL_Game* poGame, int iNum, int iX, int iY, int iL);
		void PlotMonster(LL_Game* poGame, int iNum, int iX, int iY, int iL);
		void PlotChest(LL_Game* poGame, int iX, int iY, int iL, bool fTemplate = false);
		void PlotTransport(LL_Game* poGame, int iX, int iY, int iL, bool fTemplate = false);
		void PlotVehicleObject(LL_Game* poGame, int iNum, int iX, int iY, int iL);

	protected:
	//Vars
		LL_Game* 				mypoGame;
		LEDIT_ClassSetEditor*	mypoClassSetEditor;
		LEDIT_FileChooser*		mypoFileChooser;
};

#endif
