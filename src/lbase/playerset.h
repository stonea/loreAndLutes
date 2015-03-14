/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			playerset.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/19/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description:
*/

#ifndef LL_PLAYERSET_H_
#define LL_PLAYERSET_H_
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Parent
	#include "set.h"
//Aggregates
	#include "partymembertemplate.h"
	#include <asfc/linkedlist.h>
//Dependencies
	#include <asfc/utils.h>

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_PlayerSet
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_PlayerSet : public LL_Set
{	public:
	//- [Constuctors] -
 		LL_PlayerSet();
	//- [File I/O] -
		void Save(ofstream &oFile);
		void Load(ifstream &oFile, string sGraphicsDir);
	//- [Player Units] -
		void AddPlayer(LL_PartyMemberTemplate &oMember);
		int	 NumPlayers();
		LL_PartyMemberTemplate&	Player(int iNum);

	protected:
		ASFC_LinkedList<LL_PartyMemberTemplate> myloPartyMembers;
};

#endif

