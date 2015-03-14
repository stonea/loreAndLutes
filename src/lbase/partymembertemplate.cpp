/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			partymembertemplate.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "partymembertemplate.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_PartyMemberTemplate
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_PartyMemberTemplate::LL_PartyMemberTemplate()
	:	mysImage(""),
		mysName("Player"),
		mycGender('M'),
		myiStrength(50),
		myiDexterity(50),
		myiIntelligence(50),
		myiMP(0),
  		myiMaxMP(0),
		myiHP(30),
  		myiMaxHP(30),
		myiExperience(0)
{
}
//------------------------------------------------------------------------------------------- [File I/O] -
void LL_PartyMemberTemplate::Save(ofstream &oFile)
{	//"Image File"
		oFile << Qoute(mysImage) << endl;
	//"Name"
		oFile << Qoute(mysName) << endl;
	//'Gender'
		oFile << mycGender << " ";
	//%Strength% %Dexterity% %Intelligence%
		oFile << myiStrength << " " << myiDexterity << " " << myiIntelligence << " ";
	//%MP% %MaxMP% %HP$ %MaxHP%
		oFile << myiMP << " " << myiMaxMP << " " << myiHP << " " << myiMaxHP << " ";
	//%Experience%
		oFile << myiExperience << " ";
 	//<endl>
 		oFile << endl;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_PartyMemberTemplate::Load(ifstream &oFile, string sGraphicsDir)
{	//Vars
		string ts;

	//"Image File"
		ts = ReadString(oFile);
		mysImage = ts;
	//"Name"
		ts = ReadString(oFile);
		mysName = ts;
	//'Gender'
		oFile >> mycGender;
	//%Strength% %Dexterity% %Intelligence%
		oFile >> myiStrength >> myiDexterity >> myiIntelligence;
	//%MP% %MaxMP% %HP$ %MaxHP%
		oFile >> myiMP >> myiMaxMP >> myiHP >> myiMaxHP;
	//%Experience%
		oFile >> myiExperience;
}
//--------------------------------------------------------------------------------------- [Object Maker] -
void LL_PartyMemberTemplate::MakePartyMember(string sGraphicsPath, LL_PartyMember* poPlayer)
{	//Set attributes
		LL_Vehicle oVehicle;
		oVehicle.SetCode(DEFAULT_VEHICLE);
		poPlayer->SetName(mysName);
		poPlayer->SetGender(mycGender);
		poPlayer->SetStrength(Strength());
		poPlayer->SetDexterity(Dexterity());
		poPlayer->SetIntelligence(Intelligence());
		poPlayer->SetMP(MP());
		poPlayer->SetMaxMP(MaxMP());
		poPlayer->SetHP(HP());
		poPlayer->SetMaxHP(MaxHP());
		poPlayer->SetExperience(Experience());
		poPlayer->SetVehicle(oVehicle);
	//Load image
		poPlayer->LoadAnimation(Image(), sGraphicsPath);
}
