/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			battleitem.cpp
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/19/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "battleitem.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_BattleItem
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_BattleItem::LL_BattleItem()
	: myiEquipsHands(0),
	  myfEquipsArms(0),
   	  myfEquipsTorso(0),
   	  myfEquipsHead(0)
{
}
//------------------------------------------------------------------------------------------ [Callbacks] -
void LL_BattleItem::Run()
{	cout << "ERR cBattleItem::Run() 000, not overloaded\n";
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_BattleItem::Talk()
{	cout << "ERR cBattleItem::Run() 000, not overloaded\n";
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_BattleItem::Look()
{	cout << "ERR cBattleItem::Run() 000, not overloaded\n";
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_BattleItem::Search()
{	cout << "ERR cBattleItem::Run() 000, not overloaded\n";
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_BattleItem::Attack()
{	cout << "ERR cBattleItem::Run() 000, not overloaded\n";
}
