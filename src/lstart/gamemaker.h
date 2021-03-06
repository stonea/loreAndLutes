/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			gamemaker.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Starter
   | ----` |	Last Updated:	
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: 
*/
#ifndef LSTART_GAME_MAKER_H_
#define LSTART_GAME_MAKER_H_

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい�
//												Initlization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい�
#include <string>
#include <lbase/filemanager.h>
#include <asfc/console.h>
#include "gameslist.h"
using namespace std;

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい�
//												 Prototype
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい�
class LSTART_GameMaker
{	public:
	//- [Constructor] -
		LSTART_GameMaker();
	//- [Maker] -
		string AskForGameDescription(ASFC_Console& oCon);
	    string AskForGameTitle(ASFC_Console& oCon, LSTART_GamesList& oList);
		void MakeNewGame(string sDescription, string sGameName);
		string GrabString(ASFC_Console& oCon, string sText);
	
	protected:
};

#endif
