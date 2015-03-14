/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			looplib_lorelinker.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: The LOOP linker is responsible for mapping the Lore LOOP library information object
				 to every scripted unit and item in a game and also set the default values of
				 variables as stated by the editor.
*/
#ifndef LOOPLIB_LORELINKER_H_
#define LOOPLIB_LORELINKER_H_

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Dependencies
	#include "looplib_lore.h"
	#include "game.h"
	#include "looplib_loreinfo.h"

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Vehicle
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_LOOPLib_LoreLinker
{	public:
	//- [Constuctors] -
 		LL_LOOPLib_LoreLinker();
	//- [Linking] -
		void Link(LL_Game* poGame, LL_LOOPLib_Lore* LL_Lib);
	//- [Defaults] -
		int    DefaultInt(LL_Game* poGame, string sObjectIdentifier, string sVarIdentifier);
		double DefaultFloat(LL_Game* poGame, string sObjectIdentifier, string sVarIdentifier);
		string DefaultString(LL_Game* poGame, string sObjectIdentifier, string sVarIdentifier);

 	private:
	//P- [Defaults] -P
		void SetDefaults(LL_ScriptedUnit* poScriptedUnit, LOOP_Instance* LL_Instance);
};

#endif
