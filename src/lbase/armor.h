/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			armor.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/19/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: A battle item that somehow effects defence.
*/
#ifndef LL_ARMOR_H_
#define LL_ARMOR_H_
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Parent
	#include "battleitem.h"

//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Armor
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_Armor : public LL_BattleItem
{	public:
	//- [Constuctors] -
 		LL_Armor();
	//- [File I/O] -
		void Save(ofstream &oFile);
		void Load(ifstream &oFile, string sGraphicsPath);
	//- [Callbacks] -
		void Run();
		void Talk();
		void Look();
		void Search();
		void Attack(); 		
	//- [Defense Handeling] -
		MEMVAR_SETGET(SetDefense, Defense, int, myiDefense);
 	
 	private:
 	//Vars
 		int myiDefense;
};

//Now ending armor.h
	#endif
