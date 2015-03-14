/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			partymember.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "partymember.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_PartyMember
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_PartyMember::LL_PartyMember()
{	myiWeapon1 = NO_EQUIP;
	myiWeapon2 = NO_EQUIP;
	myiWeapon3 = NO_EQUIP;
	myiArmor1 = NO_EQUIP;
	myiArmor2 = NO_EQUIP;
	myiArmor3 = NO_EQUIP;
	myfTorsoEquip = false;
	myfArmEquip = false;
	myfHand1Equip = false;
	myfHand2Equip = false;
	myfHeadEquip = false;
}
//------------------------------------------------------------------------------------------- [File I/O] -
void LL_PartyMember::SaveRecordingInfo(ofstream &oFile)
{	//"Name" 'Gender' 'State'
		oFile << Qoute(sName) << " " << cGender << " " << cState << " ";
	//%Weapon1% %Weapon2% %Weapon3% %Armor1% %Armor2% %Armor3%
		oFile << myiWeapon1 << " " << myiWeapon2  << " " <<	myiWeapon3  << " "
  			  << myiArmor1  << " " << myiArmor2   << " " << myiArmor3   << " ";
	//?TorsoEquip? ?ArmEquip? ?HandEquip1? ?HandEquip2? ?HeadEquip?
		oFile << myfTorsoEquip << " " << myfArmEquip << " " << myfHand1Equip << " "
			  << myfHand2Equip << " " << myfHeadEquip << " ";
	//<Creature info>
		Save(oFile);
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_PartyMember::LoadRecordingInfo(ifstream &oFile, string sGraphicsDir)
{	//"Name" 'Gender' 'State'
		sName = ReadString(oFile);
  		oFile >> cGender >> cState;
	//%Weapon1% %Weapon2% %Weapon3% %Armor1% %Armor2% %Armor3%
		oFile >> myiWeapon1 >> myiWeapon2 >> myiWeapon3
  			  >> myiArmor1  >> myiArmor2  >> myiArmor3;
	//?TorsoEquip? ?ArmEquip? ?HandEquip1? ?HandEquip2? ?HeadEquip?
		oFile >> myfTorsoEquip >> myfArmEquip >> myfHand1Equip 
  			  >> myfHand2Equip >> myfHeadEquip;
	//<Creature info>
		Load(oFile);
}
