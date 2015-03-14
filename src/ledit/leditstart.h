/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			leditstart.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Editor
   | ----` |	Last Updated:	MM/DD/YY
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: <Please Enter Here>
*/
#ifndef LEDIT_LEDITSTART_H_
#define LEDIT_LEDITSTART_H_

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												Initlization
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//Uses
	#include <asfc/screen.h>
	#include <asfc/input.h>
	#include <lbase/painter.h>
	#include <lbase/game.h>
	#include <lbase/map.h>
	#include <lbase/terrainset.h>
	#include <lbase/terrainmap.h>
	#include <lbase/player.h>
	#include <lbase/painter.h>
	#include "lrun/loreandlutes.h"
	#include "consoleeditor.h"
	#include "mapeditor.h"
	#include "tilematrixeditor.h"
	#include "terrainseteditor.h"
	#include "mobilityeditor.h"
	#include "mapinfoeditor.h"
	#include "mapseteditor.h"
	#include "vehicleseteditor.h"
	#include "help.h"
	#include "classseteditor.h"
	#include "mapobjecteditor.h"
	#include "filechooser.h"
	#include "scripteduniteditor.h"
	#include "monsterseteditor.h"
	#include "playerseteditor.h"
	#include "playereditor.h"
	#include "routeeditor.h"
	#include "dailyroutineeditor.h"
	#include "locationpicker.h"
	#include "itemseteditor.h"
	#include "armoreditor.h"
	#include "weaponeditor.h"
	#include "itemseteditor.h"
	#include "chesteditor.h"
	#include "vehiclebattlekeyeditor.h"
	#include "friendeditor.h"
	#include "vehicleobjecteditor.h"
	#include "vehicleobjectseteditor.h"
	#include "buttonsstrip.h"
	#include "globalinfoeditor.h"
	#include "spawnereditor.h"
	#include "graphicslist.h"
	#include <lbase/help.h>

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//												 Prototype
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
class LEDIT_LEditStart
{	public:
	//- [Editting] -
		LEDIT_MapEditor::LEDIT_TestInformation StartEditor(ASFC_Screen* poScreen, string sGame, int iMap = -1, int iX = -1, int iY = -1);
		
	protected:
	//Vars
		ASFC_Screen* mypoScreen;
};

#endif
