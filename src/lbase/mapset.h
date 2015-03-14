/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			mapset.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: A map set lists a table of descriptions to a table of map files. This set (table)
				 identifies each map numerically.
*/
#ifndef LL_MAPSET_H_
#define LL_MAPSET_H_
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Aggregates
	#include <string>
	#include <asfc/linkedlist.h>
//Dependencies
	#include <asfc/utils.h>
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_MapSet
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_MapSet
{	public:
	//Const
		const static int NO_MAP   = -1;
		const static int NEW_MAP  = -2;

	//- [Constuctors] -
 		LL_MapSet();
	//- [Set Editting] -
		void 	AddMap(C_s2(sMapFile, sMapDescription));
		string  Map(C_i(iMapNum));
		void 	RemoveMap(C_i(iMapNum));
		int  	NumMaps();
		string 	MapName(C_i(iMapNum));
		void 	SetMapName(C_i(iMapNum), C_s(sName));
	//- [File I/O] -
		void Save(ofstream &oFile);
		void Load(ifstream &oFile);

  protected:	
 	//P- [Debugging] -P
		bool ValidVersionNum(C_s(sErrorCode), C_s(sFileType), C_i(iVersionNum));
	//Const
		#define LL_MapSet__BATTLE_MAP	"battle.map"
 	//Vars
 		ASFC_LinkedList<string> mylsMapFiles;
 		ASFC_LinkedList<string> mylsMapDescriptions;
};

//Now ending mapset.h
	#endif
