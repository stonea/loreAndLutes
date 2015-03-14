/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			cllist.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "cllist.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_CLList
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_CLList::LL_CLList()
{
}
//--------------------------------------------------------------------------------------- [Entry Adding] -
void LL_CLList::AddCollision(int iSourceX, int iSourceY, int iDestinationX, int iDestinationY,
							 int iLayer, int iSeg, int iOff)
{	//If the CLList has 100 entries purge everything
		if(mylCollisions.Length() > 100)
		{	mylCollisions.Resize(0);
		}
	//Add in a new collision
		mylCollisions.Resize(mylCollisions.Length() + 1);
		int iCol = mylCollisions.Length() - 1;
	//Delete any existing entries for the seg\off
		for(int i = 0; i < mylCollisions.Length(); i++)
		{	if(mylCollisions[i].iSeg == iSeg && mylCollisions[i].iOff == iOff)
			{	mylCollisions.Delete(i);
				i--;
			}
		}
	//Set the attributes
		iCol = mylCollisions.Length() - 1;
		mylCollisions[iCol].iSourceX = iSourceX;
		mylCollisions[iCol].iSourceY = iSourceY;
		mylCollisions[iCol].iDestinationX = iDestinationX;
		mylCollisions[iCol].iDestinationY = iDestinationY;
		mylCollisions[iCol].iLayer = iLayer;
		mylCollisions[iCol].iSeg   = iSeg;
		mylCollisions[iCol].iOff   = iOff;
		
//list all entries
/*		for(int i = 0; i < mylCollisions.Length(); i++)
		{	cerr << i << ": " << mylCollisions[i].iSourceX << " "
					 << mylCollisions[i].iSourceY << " "
          				  << mylCollisions[i].iDestinationX << " "
          				   << mylCollisions[i].iDestinationY << endl;
		}*/
}
//-------------------------------------------------------------------------------------- [Entry Cheking] -
void LL_CLList::CheckEntries()
{	//Vars
		bool fBreak;

	//Loop through all entries
		for(int i = 0; i < mylCollisions.Length(); i++)
		{	//Check entry i with all collisions below it
				fBreak = false;
				for(int j = i; j < mylCollisions.Length() && !fBreak; j++)
				{	//Is the layer the same?
						if(mylCollisions[i].iLayer == mylCollisions[j].iLayer && i != j)
						{	//Is the destination equal to the source or both destinations =
								if( (mylCollisions[i].iDestinationX ==
									 mylCollisions[j].iSourceX &&
									 mylCollisions[i].iDestinationY ==
									 mylCollisions[j].iSourceY) ||
					                 (	mylCollisions[i].iDestinationX ==
										mylCollisions[j].iDestinationX &&
										mylCollisions[i].iDestinationY ==
										mylCollisions[j].iDestinationY
					                 )
								  )
								{	//Switch these two sillly units
										mypoEventQueue->SwitchUnits
          								(	mylCollisions[i].iSeg, mylCollisions[i].iOff,
          									mylCollisions[j].iSeg, mylCollisions[j].iOff
  										);
  									//Delete them too
  										mylCollisions.Delete(j);
  										mylCollisions.Delete(i);
  										i--;
  										fBreak = true;
								}
						}
				}
		}
}
