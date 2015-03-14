/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			partymembertemplate.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
	Description: 
*/
#ifndef LL_PARTYMEMBERTEMPLATE_H_
#define LL_PARTYMEMBERTEMPLATE_H_
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Parent
	#include "partymember.h"
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//										LL_PartyMemberTemplate
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
class LL_PartyMemberTemplate
{	public:
	//Const
		const static int DEFAULT_VEHICLE = 0;

	//- [Constructor] -
		LL_PartyMemberTemplate();
	//- [File I/O] -
		void Save(ofstream &oFile);
		void Load(ifstream &oFile, string sGraphicsDir);
	//- [Object Maker] -
		void MakePartyMember(string sGraphicsPath, LL_PartyMember* poPlayer);
	//- [Attributes Handeling] -
		MEMVAR_SETGET(SetName,			Name,			string, mysName);
		MEMVAR_SETGET(SetImage,			Image,			string, mysImage);
		MEMVAR_SETGET(SetStrength, 		Strength, 		int, myiStrength);
		MEMVAR_SETGET(SetDexterity, 	Dexterity, 		int, myiDexterity);
		MEMVAR_SETGET(SetIntelligence, 	Intelligence, 	int, myiIntelligence);
		MEMVAR_SETGET(SetMP, 			MP, 			int, myiMP);
		MEMVAR_SETGET(SetMaxMP, 		MaxMP, 			int, myiMaxMP);
		MEMVAR_SETGET(SetHP, 			HP, 			int, myiHP);
		MEMVAR_SETGET(SetMaxHP, 		MaxHP, 			int, myiMaxHP);
		MEMVAR_SETGET(SetExperience,	Experience, 	int, myiExperience);

	protected:
		//Image
			string mysImage;
		//Attributes and Mobility
			string mysName;
			char mycGender;
			int myiStrength,
				myiDexterity,
				myiIntelligence,
				myiMP, myiMaxMP,
				myiHP, myiMaxHP,
				myiExperience;
};

//Now ending PartyMemberTemplate.h
	#endif
