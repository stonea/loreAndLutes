/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			monster.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/18/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: A monster is a creature with built in AI.
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Multiple inclusion protection:
	#ifndef MONSTER_H_
	#define MONSTER_H_

//Dependencies
	#include <asfc/utils.h>
//Parent
	#include "creature.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Monster
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_Monster : public LL_Creature
{	public:
	//- [Constuctors] -
 		LL_Monster();
	//- [Callbacks] -
		void Run();
		void Talk();
		void Look();
		void Search();
		void Attack();
	//- [Attributes Handeling] -
		MEMVAR_SETGET(SetRarity,	Rarity,		int, myiRarity);
		MEMVAR_SETGET(SetTemplate,	Template,	int, myiTemplate);
		MEMVAR_SETGET(SetChanceOfChest,	ChanceOfChest,	int, myiChanceOfChest);
		MEMVAR_SETGET(SetChanceOfFood,	ChanceOfFood,	int, myiChanceOfFood);
		MEMVAR_SETGET(SetMaxFood,		MaxFood,		int, myiMaxFood);
 	
 	private:
 	//Vars
 		//Attributes
	 		int myiRarity;
			int myiTemplate;
			int myiChanceOfChest;
			int myiChanceOfFood;
			int myiMaxFood;
};

//Now ending monster.h
	#endif
