/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			looplib_loreinfo.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: A loop info lib holds the X,Y,Layer position of the latest scripted unit that wishes
				 to run its script. The lib info object is used to allow scripts to pass information
				 to the scripting library with out having to actually recognize the library. This
				 resolves a chicken-and-egg type problem as if the scripted unit was directly linked
				 to the Lore Lib and the Lore Lib linked to the scripted unit (through a link to
				 LORE_GAME) chaos would ensue.
*/
#ifndef LOOPLIB_LOREINRO_H_
#define LOOPLIB_LOREINRO_H_

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Dependencies
	#include <asfc/utils.h>

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Vehicle
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_LOOPLib_LoreInfo
{	public:
		LL_LOOPLib_LoreInfo();
		MEMVAR_SETGET(SetX, 			X,			int,	myiObjX);
		MEMVAR_SETGET(SetY,				Y,			int,	myiObjY);
		MEMVAR_SETGET(SetIdentifier,	Identifier,	string,	mysObjIdentifier);
		MEMVAR_SETGET(SetSeg,			Seg,		int,	myiSeg);
		MEMVAR_SETGET(SetOff,			Off,		int,	myiOff);
		MEMVAR_SETGET(SetTurnEnded,		TurnEnded,	bool,	myfTurnEnded);
		MEMVAR_SETGET(SetTalking,		Talking,	bool,	myfTalking);
    	
 	private:
 		int 	myiObjX, myiObjY;
 		string	mysObjIdentifier;
 		int		myiSeg, myiOff;
 		bool	myfTurnEnded;
 		bool	myfTalking;
};

#endif
