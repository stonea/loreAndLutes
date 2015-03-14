/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			partymember.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: 
*/
#ifndef LL_PARTYMEMBER_H_
#define LL_PARTYMEMBER_H_
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Parent
	#include "creature.h"
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_PartyMember
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_PartyMember : public LL_Creature
{	public:
	//Const
		static const char STATE_GOOD		= 'G';
		static const char STATE_DEAD		= 'D';
		static const char STATE_HUNGRY		= 'H';
		static const char STATE_INTOXICATED	= 'I';
		static const char STATE_POISENED	= 'P';
		static const char STATE_CRAZY		= 'C';
		static const char STATE_BLIND		= 'B';
		static const char STATE_SLEEPING	= 'S';
	//- [Constuctors] -
 		LL_PartyMember();
 	//- [File I/O] -
		void SaveRecordingInfo(ofstream &oFile);
		void LoadRecordingInfo(ifstream &oFile, string sGraphicsDir);
	//- [Variables] -
		MEMVAR_SETGET(SetName, Name, string, sName);
		MEMVAR_SETGET(SetGender, Gender, char, cGender);
		MEMVAR_SETGET(SetState, State, char, cState);
 		
	protected:
	//Vars
		string sName;
		char cGender;
		char cState;
};

//Now ending partymember.h
	#endif
