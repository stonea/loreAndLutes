/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			monster.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "monster.h"	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Monster
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_Monster::LL_Monster()
{
}
//------------------------------------------------------------------------------------------ [Callbacks] -
void LL_Monster::Run()
{	//If the player is right next to this sucker attack him like none other
		if((abs(UnitMap()->KnownPlayerY() - Y()) <= 1 && abs(UnitMap()->KnownPlayerX() - X()) == 0) ||
           (abs(UnitMap()->KnownPlayerY() - Y()) == 0 && abs(UnitMap()->KnownPlayerX() - X()) <= 1))
		{	Attack();
		}

	//If the player is more than ten units away in any direction no need to search
		if(abs(UnitMap()->KnownPlayerY() - Y()) > 10 || abs(UnitMap()->KnownPlayerX() - X()) > 10)
			return;

	//If the player is N
		if(UnitMap()->KnownPlayerY() < Y())
		{	Move(DIR_NORTH);
		}
	//South
		else if(UnitMap()->KnownPlayerY() > Y())
		{	Move(DIR_SOUTH);
		}
	//West
		else if(UnitMap()->KnownPlayerX() < X())
		{	Move(DIR_WEST);
		}
	//East
		else if(UnitMap()->KnownPlayerX() > X())
		{	Move(DIR_EAST);
		}
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Monster::Talk()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Monster::Look()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Monster::Search()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Monster::Attack()
{	//Attack!!! w00t!
		EventQueue()->Attack(Seg(), Off(), X(), Y(), myiTemplate);
}
