/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			legamovesmap.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/19/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "legalmovesmap.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_LegalMovesMap
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_LegalMovesMap::LL_LegalMovesMap()
{	//Construct an all legal environment
		for(int iY = 0; iY < LL_LegalMovesMap__HEIGHT; iY++)
			for(int iX = 0; iX < LL_LegalMovesMap__WIDTH; iX++)
				for(int iDir = 0; iDir < LL_LegalMovesMap__NUM_DIRS; iDir++)
				{	mylMap[iX][iY][iDir] = false;
				}
}
//---------------------------------------------------------------------------------------------- [Legal] -
bool LL_LegalMovesMap::LegalNorth(int iX, int iY)
{	if(iY - 1 < 0)
		return false;
	return(mylMap[iX][iY][0]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_LegalMovesMap::LegalSouth(int iX, int iY)
{	if(iY + 1 >= LL_LegalMovesMap__HEIGHT)
		return false;
	return(mylMap[iX][iY][1]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_LegalMovesMap::LegalWest(int iX, int iY)
{	if(iX - 1 < 0)
		return false;
	return(mylMap[iX][iY][2]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_LegalMovesMap::LegalEast(int iX, int iY)
{	if(iX + 1 >= LL_LegalMovesMap__WIDTH)
		return false;
	return(mylMap[iX][iY][3]);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_LegalMovesMap::SetLegalNorth(int iX, int iY, bool fTo)
{	mylMap[iX][iY][0] = fTo;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_LegalMovesMap::SetLegalSouth(int iX, int iY, bool fTo)
{	mylMap[iX][iY][1] = fTo;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_LegalMovesMap::SetLegalWest(int iX, int iY, bool fTo)
{	mylMap[iX][iY][2] = fTo;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_LegalMovesMap::SetLegalEast(int iX, int iY, bool fTo)
{	mylMap[iX][iY][3] = fTo;
}
