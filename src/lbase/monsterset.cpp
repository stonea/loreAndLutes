/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			monsterset.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/19/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "monsterset.h"

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_MonsterSet
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_MonsterSet::LL_MonsterSet()
{
}
//------------------------------------------------------------------------------------------- [File I/O] -
void LL_MonsterSet::Save(ofstream &oFile)
{	//Output the header info
		oFile << ".monsterset 0\n";
	//%Num Monsters%
		oFile << myloMonsters.Length() << endl;
	//<Loop for # of monster units>
		for(int i = 0; i < myloMonsters.Length(); i++)
		{	//Save this monster
				myloMonsters[i].Save(oFile);
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_MonsterSet::Load(ifstream &oFile, string sGraphicsDir)
{	//Vars
		string sType;
		string ts;
		int ti, ti2, ti3, ti4;
		int iVer;
		int iNumMonsters;
	//Input the header info
		oFile >> sType;
		oFile >> iVer;
	//%Num Monsters%
		oFile >> iNumMonsters;
		myloMonsters.Resize(iNumMonsters);
	//<Loop for # of monster units>
		for(int i = 0; i < myloMonsters.Length(); i++)
		{	//Load this moster
				myloMonsters[i].Load(oFile, sGraphicsDir);
		}
}
//-------------------------------------------------------------------------------------- [Monster Units] -
void LL_MonsterSet::AddMonster(LL_MonsterTemplate& Unit)
{	myloMonsters.Push(Unit);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
int	LL_MonsterSet::NumMonsters()
{	return(myloMonsters.Length());
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
LL_MonsterTemplate&	LL_MonsterSet::Monster(int iNum)
{	return(myloMonsters[iNum]);
}
