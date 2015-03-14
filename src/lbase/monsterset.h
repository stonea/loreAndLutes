/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			monserset.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/19/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: A battle item that effects a creatures attacking ability in battle.
*/

#ifndef LL_MONSTERSET_H_
#define LL_MONSTERSET_H_
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Parent
	#include "set.h"
//Aggregates
	#include "monstertemplate.h"
	#include <asfc/linkedlist.h>
//Dependencies
	#include <asfc/utils.h>

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_MonsterSet
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_MonsterSet : public LL_Set
{	public:
	//- [Constuctors] -
 		LL_MonsterSet();
	//- [File I/O] -
		void 	Save(ofstream &oFile);
		void	Load(ifstream &oFile, string sGraphicsDir);
	//- [Monster Units] -
		void	AddMonster(LL_MonsterTemplate& Unit);
		int		NumMonsters();
		LL_MonsterTemplate&	Monster(int iNum);

	protected:
		ASFC_LinkedList<LL_MonsterTemplate>	myloMonsters;
};

#endif

