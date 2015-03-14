/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			spawner.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "spawner.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//											LL_Spawner
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_Spawner::LL_Spawner()
{
}
//------------------------------------------------------------------------------------------- [File I/O] -
void LL_Spawner::Save(ofstream &oFile)
{	//%iX% %iY%
		oFile << myiX << " " << myiY << " ";
	//%Num Monsters%
		oFile << myliMonsters.Length() << " ";
	//<Loop for # of spawners>
		for(int i = 0; i < myliMonsters.Length(); i++)
		{	oFile << myliMonsters[i] << " ";
		}
 
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Spawner::Load(ifstream &oFile, string sGraphicsPath)
{	//Vars
		int iNumMonsters;
		int ti;
	
	//%X% %Y%
		oFile >> myiX >> myiY;
	//%iNumMonsters%
		oFile >> iNumMonsters;
		myliMonsters.Resize(iNumMonsters);
	//<Num Monsters>
		for(int i = 0; i < iNumMonsters; i++)
		{	oFile >> ti;
			myliMonsters[i] = ti;
		}
}
//-------------------------------------------------------------------------------------------- [Picker] -
int LL_Spawner::PickMonster()
{	//Vars
		double dRand;
		int iRand;
	
	//Pick a random monsta'
		iRand = PollRandom(myliMonsters.Length());
	//Return it
		return(myliMonsters[iRand]);
}
