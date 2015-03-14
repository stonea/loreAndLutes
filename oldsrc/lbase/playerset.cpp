/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			playerset.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/19/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "playerset.h"

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_PlayerSet
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_PlayerSet::LL_PlayerSet()
{
}
//------------------------------------------------------------------------------------------- [File I/O] -
void LL_PlayerSet::Save(ofstream &oFile)
{	//Output the header info
		oFile << ".playerset 0\n";
	//%Num Players%
		oFile << myloPartyMembers.Length() << endl;
	//<Loop for # of player units>
		for(int i = 0; i < myloPartyMembers.Length(); i++)
		{	//Save this playa'
				myloPartyMembers[i].Save(oFile);
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_PlayerSet::Load(ifstream &oFile, string sGraphicsDir)
{	//Vars
		string sType;
		string ts;
		int iVer;
		int iNumPlayers;
	//Input the header info
		oFile >> sType;
		oFile >> iVer;
	//%Num Playerss%
		oFile >> iNumPlayers;
		myloPartyMembers.Resize(iNumPlayers);
	//<Loop for # of player units>
		for(int i = 0; i < myloPartyMembers.Length(); i++)
		{	//Load this moster
				myloPartyMembers[i].Load(oFile, sGraphicsDir);
		}
}
//--------------------------------------------------------------------------------------- [Player Units] -
void LL_PlayerSet::AddPlayer(LL_PartyMemberTemplate &oMember)
{	myloPartyMembers.Push(oMember);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int LL_PlayerSet::NumPlayers()
{	return(myloPartyMembers.Length());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_PartyMemberTemplate& LL_PlayerSet::Player(int iNum)
{	return(myloPartyMembers[iNum]);
}
