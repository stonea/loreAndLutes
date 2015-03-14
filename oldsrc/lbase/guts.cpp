/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			guts.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "guts.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Guts
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_Guts::LL_Guts()
{
}
//------------------------------------------------------------------------------------------ [Callbacks] -
void LL_Guts::Talk()
{	mypoConsole->Writeln("Can\'t talk there", 0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Guts::Look()
{	mypoConsole->Writeln("Guts", 0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
bool LL_Guts::Push()
{	mypoConsole->Writeln("Can\'t push there", 0);
	return(false);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Guts::Search()
{	//Vars
		double dRand; int iRand;

	//Determine whether or not this lucky player get's food
  		dRand = ((double)rand() / (double)(RAND_MAX+1));
		iRand = dRand * 100;
		if(iRand >= myiChanceOfFood)
		{	mypoConsole->Writeln("Nothing", 1);
			RemoveFromMap();
			return;
		}
	//Determine how much food
  		dRand = ((double)rand() / (double)(RAND_MAX+1));
		iRand = dRand * myiMaxFood;
		if(iRand == 0)
		{	mypoConsole->Writeln("Nothing", 1);
			RemoveFromMap();
			return;
		}
		string ts;
		ts =  "Food: ";
		ts += Val(iRand);
		mypoInventory->GiveFood(iRand);
		mypoConsole->Writeln(ts, 1);
		RemoveFromMap();
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Guts::Attack()
{	mypoConsole->Writeln("Can\'t attack there", 0);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Guts::RemoveFromMap()
{	//Remove the unit
		mypoUnitMap->SetUnitOn(myiX, myiY, myiLayer, NULL_SEG, NULL_OFF);
	//Update this units coods
		myiX = 0xFF;
		myiY = 0xFF;
}
