/* Protected under the GNU General Public License read and see copying.txt for details
   ,-------.------------------------------------------- -------- ---- -- --- - - -   -     -       -
   | ``    |	File:			weapon.h
   | ||    |	By:				Andy Stone
   | ||__. |	Module:			Lore And Lutes Base
   | ----` |	Last Updated:	09/19/02
   `_______,------------------------------------------- -------- ---- -- --- - - -   -     -       -
*/
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												Initilization
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//Associated Header:
	#include "weapon.h"
	
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//												LL_Weapon
//いいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいいい
//---------------------------------------------------------------------------------------- [Constuctors] -
LL_Weapon::LL_Weapon()
	: myiAttackSkill(0),
 	  myiRadius(0)
{
}
//------------------------------------------------------------------------------------------- [File I/O] -
void LL_Weapon::Save(ofstream &oFile)
{	//"Image file path"  %Custom image%
 		oFile << Qoute(ImageFile()) << " ";	
		oFile << myfCustomImage << " ";
	//"Description"
		oFile << Qoute(Identifier()) << " ";
	//%Weight% %Attack% %Radius%
		oFile << Val(Weight()) << " ";
		oFile << Val(AttackSkill()) << " ";
		oFile << Val(Radius()) << " ";
	//%Equip Hands%
 		oFile << Val(EquipsHands()) << " ";
   	//?Equip Arms? ?Equip Torso? ?Equips Head?
		oFile << Val(EquipsArms()) << " ";
		oFile << Val(EquipsTorso()) << " ";
		oFile << Val(EquipsHead()) << " ";
	//<endl>
		oFile << endl;
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Weapon::Load(ifstream &oFile, string sGraphicsPath)
{	//Vars
		string sImageFile, sDescription;
		int iWeight, iAttack, iRaduis, iEquipHands;
		bool fEquipArms, fEquipTorso, fEquipHead;

	//"Image file path" %Custom image%
 		sImageFile = ReadString(oFile);
		oFile >> myfCustomImage;
		LoadAnimation(sImageFile, sGraphicsPath, TILE_WIDTH, TILE_HEIGHT, COLOR_BLUE);
	//"Description"
		sDescription = ReadString(oFile);
		SetIdentifier(sDescription);
	//%Weight% %AttackSkill%
		oFile >> iWeight >> iAttack >> iRaduis;
  		SetWeight(iWeight);
		SetAttackSkill(iAttack);
		SetRadius(iRaduis);
	//%Equip Hands%
 		oFile >> iEquipHands;
 		SetEquipsHands(iEquipHands);
   	//?Equip Arms? ?Equip Torso? ?Equip Head?
		oFile >> fEquipArms >> fEquipTorso >> fEquipHead;
		SetEquipsArms(fEquipArms);
		SetEquipsTorso(fEquipTorso);
		SetEquipsHead(fEquipHead);
}
//----------------------------------------------------------------------------------------- [Callbacks] -
void LL_Weapon::Run()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Weapon::Talk()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Weapon::Look()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Weapon::Search()
{
}
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
void LL_Weapon::Attack()
{
}
