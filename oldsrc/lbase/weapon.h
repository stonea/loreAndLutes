/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			weapon.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/19/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: A battle item that effects a creatures attacking ability in battle.
*/
#ifndef LL_WEAPON_H_
#define LL_WEAPON_H_
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Parent
	#include "battleitem.h"
//Dependencies
	#include <asfc/utils.h>

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Weapon
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_Weapon : public LL_BattleItem
{	public:
	//- [Constuctors] -
 		LL_Weapon();
	//- [File I/O] -
		void Save(ofstream &oFile);
		void Load(ifstream &oFile, string sGraphicsPath);
	//- [Callbacks] -
		void Run();
		void Talk();
		void Look();
		void Search();
		void Attack();
	//- [Attack Handeling] -
		MEMVAR_SETGET(SetAttackSkill, AttackSkill, int, myiAttackSkill);
 		MEMVAR_SETGET(SetRadius, Radius, int, myiRadius);
 		
 	private:
 	//Vars
 		int myiAttackSkill;
 		int myiRadius;
};

#endif
